#pragma once
#include "Enemy.h"
#include "Animation.h"

class Map;

class Goomba : public Enemy
{
public:
	Goomba(sf::Vector2f pos, bool underground);
	~Goomba();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();
	void activate();

private:
	Animation walkingAnim;
	Animation deadAnim;

	float deadTimer;//Amount of time goomba is in dead state before being removed.
};