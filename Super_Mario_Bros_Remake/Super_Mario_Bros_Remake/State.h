#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class State
{
public:
	State(StateManager* stateMgr) : stateManager(stateMgr) { isTransparent = false; };
	virtual ~State() {};

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderWindow* window) = 0;

	bool transparent()
	{
		return isTransparent;
	}

protected:
	StateManager* stateManager;
	bool isTransparent;
};