#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <string>

class Particle : public GameObject
{
public:
	Particle(std::string spriteSheetPath, sf::Vector2f pos, sf::Vector2f vel, bool isFacingLeft);
	~Particle();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();

private:
	float maxLifetime = 1.0f;
	float currentLifetime = 0.0f;

	bool facingLeft;
};