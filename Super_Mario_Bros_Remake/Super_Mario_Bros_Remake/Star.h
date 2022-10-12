#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Animation.h"

class Star : public GameObject
{
public:
	Star(Map* gameMap, sf::Vector2f pos);
	~Star();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();

private:
	bool spawning = true;
	Animation anim;
};