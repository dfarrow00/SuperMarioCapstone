#pragma once
#include "Enemy.h"
#include "Animation.h"

class PiranhaPlant : public Enemy
{
public:
	PiranhaPlant(sf::Vector2f pos);
	~PiranhaPlant();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();
	void activate();

private:
	Animation movementAnimation;
	sf::Vector2f targetPos;
};