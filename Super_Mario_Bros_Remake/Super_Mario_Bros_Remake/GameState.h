#pragma once
#include "StateManager.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Coin.h"

class GameState : public State
{
public:
	GameState(StateManager* stateMgr, sf::RenderWindow* win);
	~GameState();

	void activate();
	void deactivate();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void checkObjectCollisions();

	void addMushroom(sf::Vector2f pos);
	void addGoomba(sf::Vector2f pos);
	void addCoin(sf::Vector2f pos);
private:
	Mario* mario;
	Map map;
	sf::RenderWindow* window;
	sf::View view;

	std::vector<GameObject*> gameObjects;
};