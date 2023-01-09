#include "StateManager.h"
#include "IntroState.h"
#include "MenuState.h"
#include "GameState.h"

StateManager::StateManager(sf::RenderWindow* window)
{
	std::pair<StateType, State*> gameState(StateType::Game, new GameState(this, window));
	std::pair<StateType, State*> menuState(StateType::Menu, new MenuState(this));
	std::pair<StateType, State*> introState(StateType::Intro, new IntroState(this));
	states.push_back(gameState);
	states.push_back(menuState);
	states.push_back(introState);
	states.back().second->activate();
}

StateManager::~StateManager()
{
	for (auto itr : states)
	{
		delete itr.second;
	}
}

void StateManager::changeState(StateType state)
{
	for (auto itr = states.begin(); itr != states.end(); itr++)
	{
		if (itr->first == state)
		{
			states.back().second->deactivate();
			StateType newType = itr->first;
			State* newState = itr->second;
			states.erase(itr);
			states.emplace_back(newType, newState);
			states.back().second->activate();
			return;
		}
	}
}

void StateManager::deleteState(StateType state)
{
	for (auto itr = states.begin(); itr != states.end(); itr++)
	{
		if (itr->first == state)
		{
			delete itr->second;
			states.erase(itr);
			return;
		}
	}
}

void StateManager::update(const float deltaTime)
{
	states.back().second->update(deltaTime);
}

void StateManager::draw(sf::RenderWindow* window)
{
	if (states.back().second->transparent())
	{
		auto itr = states.end();
		while (itr != states.begin())
		{
			if (itr != states.end() && !itr->second->transparent())
			{
				break;
			}
			itr--;
		}
		for (; itr != states.end(); itr++)
		{
			itr->second->draw(window);
		}
	}
	else
	{
		states.back().second->draw(window);
	}
}

void StateManager::setBackgroundColor(sf::Color color)
{
	skyColor = color;
}

sf::Color StateManager::getSkyColor()
{
	return skyColor;
}
