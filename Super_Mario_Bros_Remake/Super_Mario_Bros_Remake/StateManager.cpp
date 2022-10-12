#include "StateManager.h"

StateManager::StateManager(sf::RenderWindow* window)
{
	std::pair<StateType, State*> gameState(StateType::Game, new GameState(this, window));
	std::pair<StateType, State*> menuState(StateType::Menu, new MenuState(this));
	states.push_back(gameState);
	states.push_back(menuState);
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
			StateType tempType = itr->first;
			State* tempState = itr->second;
			states.erase(itr);
			states.emplace_back(tempType, tempState);
			states.back().second->activate();
			return;
		}
	}
}

void StateManager::update(float deltaTime)
{
	states.back().second->update(deltaTime);
}

void StateManager::draw(sf::RenderWindow* window)
{
	if (states.back().second->transparent())
	{
		states.end()[-2].second->draw(window);
	}
	states.back().second->draw(window);
}