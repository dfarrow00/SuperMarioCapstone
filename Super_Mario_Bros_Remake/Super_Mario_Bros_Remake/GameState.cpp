#include "GameState.h"
#include "Particle.h"
#include <iostream>

GameState::GameState(StateManager* stateMgr, sf::RenderWindow* win) : State(stateMgr), window(win), map(this), hud(window)
{
	isTransparent = false;
	view = window->getDefaultView();
	window->setView(view);

	Mario* player = new Mario(&map);
	mario = player;
	gameObjects.push_back(player);
	
	map.loadMap(levelNumber);
	mario->resetLives();
	hud.setLives(mario->getLives());
	hud.setLevel(1);
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
}

void GameState::deactivate()
{
	hud.deactivate();
}

void GameState::update(float deltaTime)
{
	if (paused)
	{
		return;
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

	checkObjectCollisions();

	if (mario->getPosition().x > view.getCenter().x)//Camera only follows mario when moving fowards, stays still when mario is moving backwards.
	{
		view.setCenter(mario->getPosition().x, window->getDefaultView().getCenter().y);
		window->setView(view);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		endGame();
	}

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
	std::vector<GameObject*>::iterator itr;
	for (itr = gameObjects.begin(); itr != gameObjects.end(); itr++)
	{
		GameObject* current = *itr;
		std::vector<GameObject*>::iterator itr2;
		for (itr2 = itr + 1; itr2 != gameObjects.end(); itr2++)
		{
			GameObject* other = *itr2;
			sf::FloatRect intersection;
			if (current->isActive() && other->isActive() && current->getAABB().intersects(other->getAABB(), intersection))
			{
				if (Mario* newCurrent = dynamic_cast<Mario*>(current))
				{
					if (Mushroom* newOther = dynamic_cast<Mushroom*>(other))
					{
						other->hit();
						newCurrent->powerUp();
						addScore(200);
					}
					else if (Goomba* newOther = dynamic_cast<Goomba*>(other))
					{
						if (intersection.top == newOther->getAABB().top && intersection.width > intersection.height)
						{
							if (other->isActive())
							{
								newCurrent->setVelocityY(-300);
								addScore(100);
							}
							other->hit();
						}
						else if (newOther->isActive() && !newCurrent->getInvinsible())
						{
							newCurrent->hit();
							hud.setLives(mario->getLives());
						}
					}
				}

				else if (Mushroom* newCurrent = dynamic_cast<Mushroom*>(current))
				{
					if (Mario* newOther = dynamic_cast<Mario*>(other))
					{
						newCurrent->hit();
						newOther->powerUp();
					}
				}

				else if (Goomba* newCurrent = dynamic_cast<Goomba*>(current))
				{
					if (Mario* newOther = dynamic_cast<Mario*>(other))
					{
						if (intersection.top == newCurrent->getAABB().top && intersection.width > intersection.height)
						{
							if (newCurrent->isActive())
							{
								newOther->setVelocityY(-300);
							}
							newCurrent->hit();
							addScore(100);
						}
						else if (newCurrent->isActive() && !newOther->getInvinsible())
						{
							newOther->hit();
							hud.setLives(mario->getLives());
						}
					}

					else if (Goomba* newOther = dynamic_cast<Goomba*>(other))
					{
						if (newCurrent->isActive() && newOther->isActive())
						{
							newCurrent->setVelocity(-newCurrent->getVelocity());
							newOther->setVelocity(-newOther->getVelocity());
						}
					}
				}
			}
		}
	}
}

void GameState::addMushroom(sf::Vector2f pos)
{
	Mushroom* mushroom = new Mushroom(&map, pos);
	gameObjects.push_back(mushroom);
}

void GameState::addGoomba(sf::Vector2f pos)
{
	Goomba* goomba = new Goomba(&map, pos);
	gameObjects.push_back(goomba);
}

void GameState::addCoin(sf::Vector2f pos)
{
	Coin* coin = new Coin(pos);
	gameObjects.push_back(coin);
	coins++;
	hud.setCoins(coins);
	addScore(100);
}

void GameState::addParticles(sf::Vector2f pos)
{
	Particle* particle1 = new Particle("Resources/Brick_Particle.png", sf::Vector2f(pos.x, pos.y + 10), sf::Vector2f(-100, -300), true);
	Particle* particle2 = new Particle("Resources/Brick_Particle.png", sf::Vector2f(pos.x, pos.y + 10), sf::Vector2f(100, -300), false);
	Particle* particle3 = new Particle("Resources/Brick_Particle.png", sf::Vector2f(pos.x, pos.y - 10), sf::Vector2f(-100, -300), true);
	Particle* particle4 = new Particle("Resources/Brick_Particle.png", sf::Vector2f(pos.x, pos.y - 10), sf::Vector2f(100, -300), false);
	gameObjects.push_back(particle1);
	gameObjects.push_back(particle2);
	gameObjects.push_back(particle3);
	gameObjects.push_back(particle4);
}

void GameState::addScore(int addedScore)
{
	score += addedScore;
	hud.setScore(score);
}

void GameState::resetLevel()
{
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

void GameState::levelComplete(int flagScore)
{
	score += flagScore;
	hud.setScore(score);
	mario->playLevelCompleteAnim();
}