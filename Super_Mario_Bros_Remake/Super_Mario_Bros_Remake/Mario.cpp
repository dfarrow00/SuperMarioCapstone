#include "Mario.h"
#include <iostream>

Mario::Mario() : GameObject()
{
	texture.loadFromFile("Resources/Mario.png");
	sprite.setTexture(texture);
	position = sf::Vector2f(48.0f, 48.0f);
}

Mario::Mario(sf::Vector2f& pos)
{
	texture.loadFromFile("Resources/Mario.png");
	sprite.setTexture(texture);
	position = pos;
}

Mario::~Mario()
{
}

void Mario::update(float deltaTime, Level level)
{
	sf::Vector2f oldPosition = getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		position.y -= (400 * deltaTime);
		if (colliding(level))
		{
			position.y = oldPosition.y;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		position.y += (400 * deltaTime);
		if (colliding(level))
		{
			position.y = oldPosition.y;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		position.x -= (400 * deltaTime);
		if (colliding(level))
		{
			position.x = oldPosition.x;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		position.x += (400 * deltaTime);
		if (colliding(level))
		{
			position.x = oldPosition.x;
		}
	}

	sprite.setPosition(position);
}

void Mario::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

sf::FloatRect Mario::getAABB()
{
	return sprite.getGlobalBounds();
}


bool Mario::colliding(Level level)
{
	sf::Vector2f topLeft = getPosition();
	sf::Vector2f topRight = topLeft; topRight.x += 48;
	sf::Vector2f bottomLeft = topLeft; bottomLeft.y += 48;
	sf::Vector2f bottomRight = topRight; bottomRight.y += 48;

	if (level[topLeft.y / 48][topLeft.x / 48] == 0)
	{
		return true;
	}

	if (level[topRight.y / 48][topRight.x / 48] == 0)
	{
		return true;
	}

	if (level[bottomLeft.y / 48][bottomLeft.x / 48] == 0)
	{
		return true;
	}

	if (level[bottomRight.y / 48][bottomRight.x / 48] == 0)
	{
		return true;
	}

	return false;
}