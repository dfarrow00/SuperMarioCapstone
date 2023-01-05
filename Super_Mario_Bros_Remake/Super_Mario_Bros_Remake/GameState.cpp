#include "GameState.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Coin.h"
#include "Particle.h"
#include "KoopaTroopa.h"
#include "Star.h"
#include "CoinBrick.h"
#include "CoinPickup.h"
#include <iostream>

GameState::GameState(StateManager* stateMgr, sf::RenderWindow* win) : State(stateMgr), window(win), map(this), hud(window), collisionHandler(&map, this)
{
	isTransparent = false;

	Mario* player = new Mario();
	mario = player;
	gameObjects.push_back(player);
	
	loadSounds();
	loadLevel(levelNumber);
	stopMusic();
	mario->resetLives();
	hud.setLives(mario->getLives());

	marioStarPowerTime = mario->getStarPowerTime();
	marioPipeAnimTime = mario->getPipeAnimTime();
}

GameState::~GameState()
{
	for (GameObject* object : gameObjects)
	{
		delete object;
	}
	gameObjects.clear();
}

void GameState::activate()
{
	hud.activate();
	playMusic();
}

void GameState::deactivate()
{
	hud.deactivate();
	stopMusic();
}

void GameState::loadSounds()
{
	overgroundMusic.openFromFile("Resources/Audio/Mario_Soundtrack.wav");
	overgroundMusic.setLoop(true);
	undergroundMusic.openFromFile("Resources/Audio/Mario_Underground_Music.wav");
	undergroundMusic.setLoop(true);
	brickBreakSoundBuffer.loadFromFile("Resources/Audio/Brick_Break.wav");
	brickBreakSound.setBuffer(brickBreakSoundBuffer);
}

void GameState::update(const float deltaTime)
{
	if (paused) return;

	if (mario->getStarPower() && starPowerTimer.getElapsedTime().asSeconds() >= marioStarPowerTime)
	{
		playMusic();
	}

	if (mario->getPlayingPipeAnim() && pipeAnimTimer.getElapsedTime().asSeconds() > marioPipeAnimTime)
	{
		loadLevel(levelToLoad);
	}

	if (!mario->isAlive())
	{
		if (mario->getLives() > 0)
		{
			respawning = true;
			resetLevel();
		}
		else
		{
			endGame();
		}
	}
	else if (mario->getFinishReached())
	{
		loadLevel(levelToLoad);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		endGame();
	}

	updateGameObjects(deltaTime);
	collisionHandler.checkMapCollisions(gameObjects);
	collisionHandler.checkObjectCollisions(gameObjects);
	updateGameView();
	updateTimer(deltaTime);
}

void GameState::updateGameObjects(const float deltaTime)
{
	for (int x = 0; x < gameObjects.size(); x++)
	{
		if (gameObjects[x]->isAlive() && gameObjects[x]->getDistance(mario) <= 768)
		{
			gameObjects[x]->update(deltaTime);
		}
		else if (!gameObjects[x]->isAlive())
		{
			delete gameObjects[x];
			gameObjects.erase(gameObjects.begin() + x);
		}
	}
}

void GameState::updateGameView()
{
	if (mario->getPosition().x > view.getCenter().x)//Camera only follows mario when moving fowards, stays still when mario is moving backwards.
	{
		view.setCenter(mario->getPosition().x, window->getDefaultView().getCenter().y);
		window->setView(view);
	}
}

void GameState::updateTimer(const float deltaTime)
{
	currentTimeInterval += deltaTime;
	if (currentTimeInterval >= timerInterval)
	{
		timer--;
		currentTimeInterval = 0.0f;
		if (timer < 0)
		{
			endGame();
		}
	}
	hud.update(timer);
}

void GameState::draw(sf::RenderWindow* window)
{
	//All game objects are drawn other than first in array. This is because mario is always the first object and should be drawn above the map for the death animaton to be visible
	for (int x = 1; x < gameObjects.size(); x++)
	{
		gameObjects[x]->draw(window);
	}
	if (mario->getPlayingPipeAnim())
	{
		mario->draw(window);
		map.draw(window, &view);
	}
	else
	{
		map.draw(window, &view);
		mario->draw(window);
	}
	hud.draw(window);
}

void GameState::enterPipe(int levelNumber, bool isGoingDown)
{
	mario->playPipeAnimation(isGoingDown);
	pipeAnimTimer.restart();
	levelToLoad = levelNumber;
}

void GameState::loadLevel(int newLevelNumber)
{
	stopMusic();
	gameObjects.clear();
	gameObjects.push_back(mario);
	int prevLevelNumber = levelNumber;
	levelNumber = newLevelNumber;
	map.loadMap(levelNumber);
	mario->reset();
	//If level is a secret coin room...
	if (levelNumber > 100)
	{
		mario->setPosition(96.0f, 100.0f);
		mario->setFurthestXPos(mario->getPosition().x - (view.getSize().x / 2));
	}
	else if (prevLevelNumber > 100 && levelNumber < 100 && respawning == false)
	{
		//TODO
		mario->setPosition(map.getPipeExitPos().x, map.getPipeExitPos().y);
		mario->setFurthestXPos(mario->getPosition().x - (view.getSize().x / 2));
		hud.setLevel(levelNumber);
	}
	else
	{
		hud.setLevel(levelNumber);
		respawning = false;
	}
	view = window->getDefaultView();
	window->setView(view);
	playMusic();
}

void GameState::addMushroom(sf::Vector2f pos)
{
	Mushroom* mushroom = new Mushroom(pos);
	gameObjects.push_back(mushroom);
}

void GameState::addGoomba(sf::Vector2f pos)
{
	Goomba* goomba = new Goomba(pos);
	gameObjects.push_back(goomba);
}

void GameState::addKoopaTroopa(sf::Vector2f pos)
{
	KoopaTroopa* koopaTroopa = new KoopaTroopa(pos);
	gameObjects.push_back(koopaTroopa);
}

void GameState::addCoinEffect(sf::Vector2f pos)
{
	Coin* coin = new Coin(pos);
	gameObjects.push_back(coin);
	coins++;
	hud.setCoins(coins);
	addScore(100);
}

void GameState::addCoinPickup(sf::Vector2f pos)
{
	CoinPickup* coin = new CoinPickup(pos);
	gameObjects.push_back(coin);
}

void GameState::addStar(sf::Vector2f pos)
{
	Star* star = new Star(pos);
	gameObjects.push_back(star);
}

void GameState::addParticles(sf::Vector2f pos)
{
	Particle* particle1 = new Particle("Resources/Sprites/Brick_Particle.png", sf::Vector2f(pos.x, pos.y + 10), sf::Vector2f(-100, -300), true);
	Particle* particle2 = new Particle("Resources/Sprites/Brick_Particle.png", sf::Vector2f(pos.x, pos.y + 10), sf::Vector2f(100, -300), false);
	Particle* particle3 = new Particle("Resources/Sprites/Brick_Particle.png", sf::Vector2f(pos.x, pos.y - 10), sf::Vector2f(-100, -300), true);
	Particle* particle4 = new Particle("Resources/Sprites/Brick_Particle.png", sf::Vector2f(pos.x, pos.y - 10), sf::Vector2f(100, -300), false);
	gameObjects.push_back(particle1);
	gameObjects.push_back(particle2);
	gameObjects.push_back(particle3);
	gameObjects.push_back(particle4);
	brickBreakSound.play();
	addScore(50);
}

void GameState::addCoinBrick(sf::Vector2f pos)
{
	CoinBrick* coinBrick = new CoinBrick(pos, this);
	gameObjects.push_back(coinBrick);
}

void GameState::addScore(int addedScore)
{
	score += addedScore;
	hud.setScore(score);
}

void GameState::addCoins(int amount)
{
	coins += amount;
	hud.setCoins(coins);
}

void GameState::clearGameObjects()
{
	for (int x = 0; x < gameObjects.size(); x++)
	{
		if (gameObjects[x]->getObjectType() != ObjectType::Mario)
		{
			delete gameObjects[x];
			gameObjects.erase(gameObjects.begin() + x);
		}
	}
}

sf::View* GameState::getView()
{
	return &view;
}

HUD* GameState::getHUD()
{
	return &hud;
}

sf::Clock* GameState::getStarPowerTimer()
{
	return &starPowerTimer;
}

int GameState::getLevelNumber()
{
	return levelNumber;
}

void GameState::resetLevel()
{
	stopMusic();
	overgroundMusic.setPlayingOffset(sf::Time::Zero);
	undergroundMusic.setPlayingOffset(sf::Time::Zero);
	if (levelNumber > 100)
	{
		int returnLevelNumber = levelNumber;
		while (returnLevelNumber >= 10)
		{
			returnLevelNumber /= 10;
		}
		loadLevel(returnLevelNumber);
	}
	else
	{
		loadLevel(levelNumber);
	}
	playMusic();
	timer = 400;
	coins = 0;
	score = 0;
	hud.setLives(mario->getLives());
	hud.setScore(score);
	hud.setCoins(coins);
	view = window->getDefaultView();
	window->setView(view);
}

void GameState::endGame()
{
	mario->resetLives();
	resetLevel();
	stateManager->changeState(StateType::Menu);
}

void GameState::levelComplete(int flagScore, sf::Vector2f flagPolePos)
{
	stopMusic();
	addScore(flagScore);
	addScore(timer * 50);
	hud.setScore(score);
	mario->playLevelCompleteAnim(flagPolePos);
	levelToLoad = levelNumber + 1;
}

void GameState::playMusic()
{
	if (levelNumber < 100)
	{
		overgroundMusic.play();
	}
	else
	{
		undergroundMusic.play();
	}
}

void GameState::stopMusic()
{
	if (overgroundMusic.getStatus() == sf::Music::Playing)
	{
		overgroundMusic.stop();
	}
	else
	{
		undergroundMusic.stop();
	}
}

void GameState::pauseMusic()
{
	if (overgroundMusic.getStatus() == sf::Music::Playing)
	{
		overgroundMusic.pause();
	}
	else
	{
		undergroundMusic.pause();
	}
}

void GameState::setSkyColor(sf::Color color)
{
	stateManager->setSkyColor(color);
}