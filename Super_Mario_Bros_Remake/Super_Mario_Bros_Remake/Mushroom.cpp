#include "Mushroom.h"
#include "Map.h"

Mushroom::Mushroom(Map* gameMap, sf::Vector2f pos) : map(gameMap), spawning(true)
{
	texture.loadFromFile("Resources/Mushroom.png");
	sprite.setTexture(texture);
	position = pos;
	velocity = sf::Vector2f(0, -50);
	alive = true;
	spriteHeight = 48;
}

Mushroom::~Mushroom()
{
}

void Mushroom::update(float deltaTime)
{
	if (spawning)
	{
		if (!map->isColliding(position, velocity * deltaTime, spriteHeight))
		{
			spawning = false;
			velocity.x = 100;
			velocity.y = 0;
			position.y -= 1;
		}
	}
	else
	{
		if (position.y + (velocity.y * deltaTime) >= 670)
		{
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			hit();
			return;
		}

		if (map->isColliding(position, sf::Vector2f(velocity.x * deltaTime, 0), spriteHeight))
		{
			velocity.x = -velocity.x;
		}

		velocity.y += GRAVITY * deltaTime;

		if (map->isColliding(position, sf::Vector2f(0, velocity.y * deltaTime), spriteHeight))
		{
			velocity.y = 0.0f;
		}
	}

	position += velocity * deltaTime;
	sprite.setPosition(position);
}

void Mushroom::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Mushroom::hit()
{
	alive = false;
}