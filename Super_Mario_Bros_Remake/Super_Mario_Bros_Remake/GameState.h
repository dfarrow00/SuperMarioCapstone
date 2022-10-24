#pragma once
#include "StateManager.h"
#include "Map.h"
#include "HUD.h"
#include "CollisionHandler.h"

class Mario;
class GameObject;

class GameState : public State
{
public:
	GameState(StateManager* stateMgr, sf::RenderWindow* win);
	~GameState();

	void activate();
	void deactivate();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void updateGameObjects(float deltaTime);
	void updateGameView();
	void updateTimer(float deltaTime);
	void checkObjectCollisions();

	void addMushroom(sf::Vector2f pos);
	void addGoomba(sf::Vector2f pos);
	void addKoopaTroopa(sf::Vector2f pos);
	void addCoin(sf::Vector2f pos);
	void addStar(sf::Vector2f pos);
	void addParticles(sf::Vector2f pos);
	void addScore(int addedScore);

	void levelComplete(int flagScore, sf::Vector2f flagPolePos);
private:
	void resetLevel();
	void endGame();

	int timer = 400;
	float timerInterval = 0.4;
	float currentTimeInterval = 0.0f;

	int score = 0;
	int coins = 0;
	int levelNumber = 1;

	bool paused = false;

	Mario* mario;
	Map map;
	sf::RenderWindow* window;
	sf::View view;
	HUD hud;

	CollisionHandler collisionHandler;

	std::vector<GameObject*> gameObjects;
};