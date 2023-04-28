#include "StateManager.h"
#include "IntroState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"

StateManager::StateManager(sf::RenderWindow* window)
{
	//Add state objects to state vector.
	std::pair<StateType, State*> gameOverState(StateType::GameOver, new GameOverState(this));
	std::pair<StateType, State*> pauseState(StateType::Paused, new PauseState(this));
	std::pair<StateType, State*> gameState(StateType::Game, new GameState(this, window));
	std::pair<StateType, State*> menuState(StateType::Menu, new MenuState(this));
	std::pair<StateType, State*> introState(StateType::Intro, new IntroState(this));
	states.push_back(gameOverState);
	states.push_back(pauseState);
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

void StateManager::escapePressed()
{
	if (states.back().first == StateType::Game)
	{
		changeState(StateType::Paused);
	}
	else
	{
		changeState(StateType::Game);
	}
}

void StateManager::enterPressed()
{
	//If current state is 'Menu' or 'GameOver', call 'enterPressed' function.
	if (states.back().first == StateType::Menu)
	{
		State* state = states.back().second;
		MenuState* menuState = dynamic_cast<MenuState*>(state);
		menuState->enterPressed();
	}
	else if (states.back().first == StateType::GameOver)
	{
		State* state = states.back().second;
		GameOverState* gameOverState = dynamic_cast<GameOverState*>(state);
		gameOverState->enterPressed();
	}
}

void StateManager::changeState(StateType state)
{
	for (auto itr = states.begin(); itr != states.end(); itr++)
	{
		//If state type to change to found, move new state to top of stack.
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
	//If current state is transparent, draw state behind it too.
	if (states.back().second->transparent())
	{
		//Iterates backwards through vector until state that is not transparent found.
		auto itr = states.end();
		while (itr != states.begin())
		{
			if (itr != states.end() && !itr->second->transparent())
			{
				break;
			}
			itr--;
		}
		//Iterates forwards from last transparent state and draws each.
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
