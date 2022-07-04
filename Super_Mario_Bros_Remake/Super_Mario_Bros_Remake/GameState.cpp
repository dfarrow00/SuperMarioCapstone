#include "GameState.h"
#include <iostream>

GameState::GameState(StateManager* stateMgr, sf::RenderWindow* win) : State(stateMgr), window(win), map(this)
{
	isTransparent = false;
	view = window->getDefaultView();
	window->setView(view);

	Mario* player = new Mario(&map);
	mario = player;
	gameObjects.push_back(player);
}

GameState::~GameState()
{
}

void GameState::activate()
{
}

void GameState::deactivate()
{
}

void GameState::update(float deltaTime)
{
	for (int x = 0; x < gameObjects.size(); x++)
	{
		if (gameObjects[x]->isAlive())
		{
			gameObjects[x]->update(deltaTime);
		}
		else
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
		mario->reset();
		view = window->getDefaultView();
		window->setView(view);
		stateManager->changeState(StateType::Menu);
	}
}

void GameState::draw(sf::RenderWindow* window)
{
	for (GameObject* object : gameObjects)
	{
		object->draw(window);
	}
	map.draw(window, &view);
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
			if (current->getAABB().intersects(other->getAABB()))
			{
				if (Mario* newCurrent = dynamic_cast<Mario*>(current))
				{
					if (Mushroom* newOther = dynamic_cast<Mushroom*>(other))
					{
						other->hit();
						newCurrent->powerUp();
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