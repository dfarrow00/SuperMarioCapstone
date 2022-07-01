#include "GameState.h"
#include <iostream>

GameState::GameState(StateManager* stateMgr, sf::RenderWindow* win) : State(stateMgr), window(win)
{
	isTransparent = false;
	view = window->getDefaultView();
	window->setView(view);
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
	mario.update(deltaTime, map.getCurrentLevel());
	if (mario.getPosition().x > view.getCenter().x)//Camera only follows mario when moving fowards, stays still when mario is moving backwards.
	{
		view.setCenter(mario.getPosition().x, window->getDefaultView().getCenter().y);
		window->setView(view);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mario.reset();
		view = window->getDefaultView();
		window->setView(view);
		stateManager->changeState(StateType::Menu);
	}
}

void GameState::draw(sf::RenderWindow* window)
{
	map.draw(window, &view);
	mario.draw(window);
}
