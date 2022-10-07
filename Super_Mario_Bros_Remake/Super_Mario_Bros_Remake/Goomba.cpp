#include "Goomba.h"
#include <iostream>

Goomba::Goomba(Map* gameMap, sf::Vector2f pos) : map(gameMap), walkingAnim("Resources/Goomba_SpriteSheet.png", 0, 2, 0.3), deadAnim("Resources/Goomba_SpriteSheet.png", 1, 1, 0.1)
{
	position = pos;
	currentAnim = &walkingAnim;
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);
	velocity = sf::Vector2f(-75, 0);
	deadTimer = 2.0f;
}

Goomba::~Goomba()
{
}

void Goomba::update(float deltaTime)
{
	if (currentAnim == &deadAnim)
	{
		deadTimer -= deltaTime;
		if (deadTimer <= 0)
		{
			alive = false;
		}
		return;
	}

	if (!active)
	{
		return;
	}

	//Not tested
	if (position.y + (velocity.y * deltaTime) >= 670)
	{
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		hit();
		return;
	}

	if (position.x + velocity.x < 0)
	{
		velocity.x = -velocity.x;
	}

	if (map->isColliding(position, sf::Vector2f(velocity.x * deltaTime, 0)))
	{
		velocity.x = -velocity.x;
	}

	velocity.y += 800 * deltaTime;

	if (map->isColliding(position, sf::Vector2f(0, velocity.y * deltaTime)))
	{
		velocity.y = 0.0f;
	}

	position += velocity * deltaTime;

	currentAnim->update(deltaTime);
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);
}

void Goomba::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Goomba::hit()
{
	currentAnim = &deadAnim;
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);
	active = false;
}

void Goomba::activate()
{
	active = true;
}