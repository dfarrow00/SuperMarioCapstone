#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Map.h"

class Mario : public GameObject
{
public:
	Mario();
	Mario(sf::Vector2f& pos);
	~Mario();

	void update(float deltaTime, Level level);
	void draw(sf::RenderWindow* window);

	bool colliding(Level level);

	sf::FloatRect getAABB();

private:
	float speed = 100.0f;
};