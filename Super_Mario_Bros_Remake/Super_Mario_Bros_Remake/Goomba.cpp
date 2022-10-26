#include "Goomba.h"
#include "Map.h"
#include <iostream>

Goomba::Goomba(sf::Vector2f pos) : walkingAnim("Resources/Goomba_SpriteSheet.png", 0, 2, 0.3), deadAnim("Resources/Goomba_SpriteSheet.png", 1, 1, 0.1)
{
	objectType = ObjectType::Goomba;
	position = pos;
	currentAnim = &walkingAnim;
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);
	velocity = sf::Vector2f(-75, 0);
	deadTimer = 2.0f;
	isBig = false;
	facingLeft = true;
	spriteHeight = 48;
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
	move(deltaTime);
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