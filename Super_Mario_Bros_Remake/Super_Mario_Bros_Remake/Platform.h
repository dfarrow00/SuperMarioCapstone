#pragma once
#include "GameObject.h"

class Platform : public GameObject
{
public:
	Platform(sf::Vector2f pos, bool travellingUp);
	~Platform();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();
};