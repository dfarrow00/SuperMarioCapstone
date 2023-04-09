#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Animation.h"

enum class KoopaState 
{
	Walking, Shell
};

class Map;

class KoopaTroopa : public Enemy
{
public:
	KoopaTroopa(sf::Vector2f pos, bool red);
	~KoopaTroopa();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();
	void kick(bool direction);
	void activate();

	void playDeathAnim();
	void updateDeathAnim(const float deltaTime);

	KoopaState getCurrentState();
private:
	KoopaState currentState;

	Animation walkingAnim;
	Animation shellAnim;

	bool playingDeathAnim = false;
	float deathAnimTime = 3.5f;
	float currentDeathAnimTime = 0.0f;

	float stationaryShellTimer = 0.0f;
	float stationaryTimeLimit;
};
