#pragma once
#include "GameObject.h"

class GameState;

class CoinBrick : public GameObject
{
public:
	CoinBrick(sf::Vector2f pos, GameState* gameState);
	~CoinBrick();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();

private:
	GameState* game;
	sf::Clock clock;
	bool timerStarted = false;
	bool activated = false;
	float activeDuration = 3.5;
};