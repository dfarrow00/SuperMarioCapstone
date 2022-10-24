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
	KoopaTroopa(sf::Vector2f pos);
	~KoopaTroopa();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();
	void kick(bool direction);
	void activate();

	KoopaState getCurrentState();
private:
	KoopaState currentState;

	Animation walkingAnim;
	Animation shellAnim;

	float stationaryShellTimer = 0.0f;
	float stationaryTimeLimit;
};
