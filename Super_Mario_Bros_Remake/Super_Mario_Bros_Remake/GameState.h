#pragma once
#include "StateManager.h"
#include "Mario.h"

class GameState : public State
{
public:
	GameState(StateManager* stateMgr, sf::RenderWindow* win);
	~GameState();

	void activate();
	void deactivate();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
private:
	Mario mario;
	Map map;
	sf::RenderWindow* window;
	sf::View view;
	std::vector<GameObject*> gameObjects;
};