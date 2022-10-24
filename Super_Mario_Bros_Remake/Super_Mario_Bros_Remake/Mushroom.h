#pragma once
#include "GameObject.h"

class Map;

class Mushroom : public GameObject
{
public:
	Mushroom(sf::Vector2f pos);
	~Mushroom();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();

private:
	sf::Vector2f targetSpawnPos;
	bool spawning;
};