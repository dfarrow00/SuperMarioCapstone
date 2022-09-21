#pragma once
#include "StateManager.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Coin.h"
#include "HUD.h"

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

	void addScore(int addedScore);
private:
	void loseLife();
	void resetLevel();
	void endGame();

	int timer = 400;
	float timerInterval = 0.4;
	float currentTimeInterval = 0.0f;

	int score = 0;
	int coins = 0;
	int lives = 3;
	int levelNumber = 1;

	Mario* mario;
	Map map;
	sf::RenderWindow* window;
	sf::View view;
	HUD hud;

	std::vector<GameObject*> gameObjects;
};