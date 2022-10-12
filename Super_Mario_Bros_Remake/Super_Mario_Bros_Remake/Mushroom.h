#pragma once
#include "GameObject.h"

class Map;

class Mushroom : public GameObject
{
public:
	Mushroom(Map* gameMap, sf::Vector2f pos);
	~Mushroom();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();

private:
	Map* map;
	bool spawning;
};