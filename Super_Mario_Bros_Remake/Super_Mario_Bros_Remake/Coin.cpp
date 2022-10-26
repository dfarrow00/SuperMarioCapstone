#include "Coin.h"

Coin::Coin(sf::Vector2f pos) : anim("Resources/Coin_SpriteSheet.png", 0, 2, 0.1)
{
	objectType = ObjectType::Coin;
	position = pos;
	checkCollisions = false;
	sprite = anim.getCurrentSprite();
}

Coin::~Coin()
{
}

void Coin::update(float deltaTime)
{
	lifetime -= deltaTime;
	if (lifetime <= 0.0f)
	{
		alive = false;
		return;
	}

	position.y -= speed * deltaTime;

	anim.update(deltaTime);
	sprite = anim.getCurrentSprite();
	sprite.setPosition(position);
}

void Coin::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Coin::hit()
{
}