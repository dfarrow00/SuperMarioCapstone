#include "Star.h"
#include "Map.h"

Star::Star(Map* gameMap, sf::Vector2f pos) : anim("Resources/Star_Power_SpriteSheet.png", 0, 2, 0.2)
{
	map = gameMap;
	position = pos;
	spriteHeight = 48;
	velocity.y = -50;
	anim.reset();
	sprite = anim.getCurrentSprite();
}

Star::~Star()
{
}

void Star::update(const float deltaTime)
{
	if (spawning)
	{
		if (!map->isColliding(position, velocity * deltaTime, spriteHeight))
		{
			spawning = false;
			velocity.x = 300;
			velocity.y = 0;
			position.y -= 1;
		}
	}
	else
	{
		anim.update(deltaTime);
		sprite = anim.getCurrentSprite();

		if (position.y + (velocity.y * deltaTime) >= 670)
		{
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			hit();
			return;
		}

		if (position.x + velocity.x < 0.0f)
		{
			velocity.x = -velocity.x;
		}

		if (map->isColliding(position, sf::Vector2f(velocity.x * deltaTime, 0), spriteHeight))
		{
			velocity.x = -velocity.x;
		}

		if (map->isColliding(position, sf::Vector2f(0, 1), spriteHeight))//Ground check
		{
			velocity.y = -700.0f;
		}
		else
		{
			velocity.y += GRAVITY * deltaTime;
		}

		if (map->isColliding(position, sf::Vector2f(0, velocity.y * deltaTime), spriteHeight))
		{
			velocity.y = 0.0f;
		}
	}

	position += velocity * deltaTime;
	sprite.setPosition(position);
}

void Star::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Star::hit()
{
	alive = false;
}