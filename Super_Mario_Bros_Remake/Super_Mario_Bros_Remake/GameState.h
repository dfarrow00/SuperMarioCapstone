#pragma once
#include "StateManager.h"
#include "Map.h"
#include "HUD.h"
#include "CollisionHandler.h"
#include <SFML/Audio.hpp>

class Mario;
class GameObject;

class GameState : public State
{
public:
	GameState(StateManager* stateMgr, sf::RenderWindow* win);
	~GameState();

	void activate();
	void deactivate();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void updateGameObjects(const float deltaTime);
	void updateGameView();
	void updateTimer(const float deltaTime);

	void enterPipe(int levelNumber, bool isGoingDown);
	void loadLevel(int levelNumber);

	void addMushroom(sf::Vector2f pos);
	void addGoomba(sf::Vector2f pos);
	void addKoopaTroopa(sf::Vector2f pos);
	void addPiranhaPlant(sf::Vector2f pos);
	void addPlatform(sf::Vector2f pos, int direction);
	void addCoinEffect(sf::Vector2f pos);
	void addCoinPickup(sf::Vector2f pos);
	void addStar(sf::Vector2f pos);
	void addParticles(sf::Vector2f pos);
	void addCoinBrick(sf::Vector2f pos);
	void addScore(int addedScore);
	void addCoins(int amount);

	void clearGameObjects();

	//Add play music function which plays which music is needed for current level.
	void playMusic();
	void stopMusic();
	void pauseMusic();

	void setSkyColor(sf::Color color);

	sf::View* getView();
	HUD* getHUD();
	sf::Clock* getStarPowerTimer();
	int getLevelNumber();

	void levelComplete(int flagScore, sf::Vector2f flagPolePos);
private:
	void loadSounds();
	void resetLevel();
	void endGame();

	int timer = 400;
	float timerInterval = 0.4;
	float currentTimeInterval = 0.0f;
	float marioStarPowerTime;
	float marioPipeAnimTime;

	int score = 0;
	int coins = 0;
	int levelNumber = 2;
	int levelToLoad;

	bool paused = false;
	bool respawning = false;

	Mario* mario;
	Map map;
	sf::RenderWindow* window;
	sf::View view;
	HUD hud;

	sf::Music overgroundMusic;
	sf::Music undergroundMusic;
	sf::SoundBuffer brickBreakSoundBuffer;
	sf::Sound brickBreakSound;

	sf::Clock starPowerTimer;
	sf::Clock pipeAnimTimer;

	CollisionHandler collisionHandler;

	std::vector<GameObject*> gameObjects;
};