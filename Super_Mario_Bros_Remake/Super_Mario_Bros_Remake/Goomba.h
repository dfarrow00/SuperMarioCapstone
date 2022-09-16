#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Map.h"

class Goomba : public GameObject
{
public:
	Goomba(Map* gameMap, sf::Vector2f pos);
	~Goomba();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();

private:
	Map* map;
	Animation* currentAnim;
	Animation walkingAnim;
	Animation deadAnim;

	float deadTimer;
};