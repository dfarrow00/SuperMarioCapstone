#include "GameState.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Coin.h"
#include "Particle.h"
#include "KoopaTroopa.h"
#include "Star.h"
#include "CoinBrick.h"
#include <iostream>

GameState::GameState(StateManager* stateMgr, sf::RenderWindow* win) : State(stateMgr), window(win), map(this), hud(window), collisionHandler(&map, this)
{
	isTransparent = false;
	view = window->getDefaultView();
	window->setView(view);

	Mario* player = new Mario();
	mario = player;
	gameObjects.push_back(player);
	
	map.loadMap(levelNumber);
	mario->resetLives();
	hud.setLives(mario->getLives());
	hud.setLevel(1);

	marioStarPowerTime = mario->getStarPowerTime();

	loadSounds();
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
	music.play();
}

void GameState::deactivate()
{
	hud.deactivate();
	music.stop();
}

void GameState::loadSounds()
{
	music.openFromFile("Resources/Audio/Mario_Soundtrack.wav");
	music.setLoop(true);
	brickBreakSoundBuffer.loadFromFile("Resources/Audio/Brick_Break.wav");
	brickBreakSound.setBuffer(brickBreakSoundBuffer);
}

void GameState::update(float deltaTime)
{
	if (paused) return;

	if (music.getStatus() == sf::Music::Status::Paused)
	{
		if (starPowerTimer.getElapsedTime().asSeconds() >= marioStarPowerTime)
		{
			music.play();
		}
	}

	if (!mario->isAlive())
	{
		if (mario->getLives() > 0)
		{
			resetLevel();
		}
		else
		{
			endGame();
		}
	}
	else if (mario->getFinishReached())
	{
		//next level
		endGame();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		endGame();
	}

	updateGameObjects(deltaTime);
	collisionHandler.checkMapCollisions(gameObjects);
	checkObjectCollisions();
	updateGameView();
	updateTimer(deltaTime);
}

void GameState::updateGameObjects(float deltaTime)
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

void GameState::updateTimer(float deltaTime)
{
	currentTimeInterval += deltaTime;
	if (currentTimeInterval >= timerInterval)
	{
		timer--;
		currentTimeInterval = 0.0f;
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
	map.draw(window, &view);
	mario->draw(window);
	hud.draw(window);
}

void GameState::checkObjectCollisions()
{
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); itr++)
	{
		GameObject* current = *itr;
		for (auto itr2 = itr + 1; itr2 != gameObjects.end(); itr2++)
		{
			GameObject* other = *itr2;
			sf::FloatRect intersection;
			if (current->isActive() && other->isActive() && current->getAABB().intersects(other->getAABB(), intersection))
			{
				if (Mario* marioObject = dynamic_cast<Mario*>(current))
				{
					if (marioObject->getStarPower())
					{
						if (other->getObjectType() == ObjectType::KoopaTroopa)
						{
							KoopaTroopa* koopaObject = dynamic_cast<KoopaTroopa*>(other);
							if (koopaObject->getCurrentState() == KoopaState::Walking)
							{
								other->hit();
							}
							else
							{
								koopaObject->kick(marioObject->getPosition().x < koopaObject->getPosition().x);
							}
						}
						other->hit();
						break;
					}
					if (other->getObjectType() == ObjectType::Mushroom)
					{
						other->hit();
						marioObject->powerUp();
						addScore(200);
					}
					else if (other->getObjectType() == ObjectType::Goomba)
					{
						if (intersection.top == other->getAABB().top && intersection.width > intersection.height)
						{
							if (other->isActive())
							{
								marioObject->setVelocityY(-300);
								addScore(100);
							}
							other->hit();
						}
						else if (other->isActive() && !marioObject->getInvinsible())
						{
							if (marioObject->getSpriteHeight() == 48)
							{
								music.stop();
							}
							marioObject->hit();
							hud.setLives(mario->getLives());
						}
					}
					else if (KoopaTroopa* koopaObject = dynamic_cast<KoopaTroopa*>(other))
					{
						if (intersection.top == koopaObject->getAABB().top && intersection.width > intersection.height)
						{
							if (koopaObject->getCurrentState() == KoopaState::Walking)
							{
								marioObject->setVelocityY(-300);
								addScore(100);
								koopaObject->hit();
							}
							else
							{
								marioObject->setVelocityY(-200);
								koopaObject->kick(marioObject->getPosition().x < koopaObject->getPosition().x);
							}
						}
						else if (koopaObject->isActive() && !marioObject->getInvinsible())
						{
							if (koopaObject->getCurrentState() == KoopaState::Shell && koopaObject->getVelocity().x == 0)
							{
								koopaObject->kick(marioObject->getPosition().x < koopaObject->getPosition().x);
							}
							else
							{
								if (marioObject->getSpriteHeight() == 48)
								{
									music.stop();
								}
								marioObject->hit();
								hud.setLives(mario->getLives());
							}
						}
					}
					else if (other->getObjectType() == ObjectType::Star)
					{
						marioObject->starPowerUp();
						music.pause();
						starPowerTimer.restart();
						other->hit();
					}
					else if (other->getObjectType() == ObjectType::CoinBrick)
					{
						collisionHandler.resolveCollision(other, marioObject, intersection);
						if (intersection.width > intersection.height && marioObject->getPosition().y > other->getPosition().y)
						{
							other->hit();
						}
					}
				}

				else if (current->getObjectType() == ObjectType::Goomba)
				{
					if (other->getObjectType() == ObjectType::Goomba)
					{
						if (current->isActive() && other->isActive())
						{
							current->setVelocity(-current->getVelocity());
							current->setFacingLeft(!current->getFacingLeft());
							other->setVelocity(-other->getVelocity());
							other->setFacingLeft(!other->getFacingLeft());
						}
					}
					else if (KoopaTroopa* koopaObject = dynamic_cast<KoopaTroopa*>(other))
					{
						if (current->isActive() && koopaObject->isActive())
						{
							if (koopaObject->getCurrentState() != KoopaState::Shell)
							{
								current->setVelocity(-current->getVelocity());
								current->setFacingLeft(!current->getFacingLeft());
								koopaObject->setVelocity(-koopaObject->getVelocity());
								koopaObject->setFacingLeft(!koopaObject->getFacingLeft());
							}
							else
							{
								current->hit();
								addScore(100);
							}
						}
					}
				}

				else if (KoopaTroopa* koopaObject = dynamic_cast<KoopaTroopa*>(current))
				{
					if (Enemy* enemyObject = dynamic_cast<Enemy*>(other))
					{
						if (koopaObject->isActive() && enemyObject->isActive())
						{
							if (koopaObject->getCurrentState() != KoopaState::Shell)
							{
								koopaObject->setVelocity(-koopaObject->getVelocity());
								koopaObject->setFacingLeft(!koopaObject->getFacingLeft());
								enemyObject->setVelocity(-enemyObject->getVelocity());
								enemyObject->setFacingLeft(!enemyObject->getFacingLeft());
							}
							else
							{
								enemyObject->hit();
								addScore(100);
							}
						}
					}
				}

				else if (current->getObjectType() == ObjectType::CoinBrick)
				{
					collisionHandler.resolveCollision(current, other, intersection);
				}
			}
		}
	}
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

void GameState::addCoin(sf::Vector2f pos)
{
	Coin* coin = new Coin(pos);
	gameObjects.push_back(coin);
	coins++;
	hud.setCoins(coins);
	addScore(100);
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

sf::View* GameState::getView()
{
	return &view;
}

void GameState::resetLevel()
{
	music.stop();
	music.setPlayingOffset(sf::Time::Zero);
	music.play();
	gameObjects.clear();
	mario->reset();
	gameObjects.push_back(mario);
	map.loadMap(1);
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
	music.stop();
	score += flagScore;
	hud.setScore(score);
	mario->playLevelCompleteAnim(flagPolePos);
}