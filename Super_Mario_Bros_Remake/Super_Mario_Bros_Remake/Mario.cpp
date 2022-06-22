#include "Mario.h"
#include <iostream>

Mario::Mario() : GameObject()
{
	texture.loadFromFile("Resources/Mario.png");
	sprite.setTexture(texture);
	sprite.scale(3, 3);
	position = sf::Vector2f(0.0f, 0.0f);
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

void Mario::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		position.y -= (200 * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		position.y += (200 * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		position.x -= (200 * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		position.x += (200 * deltaTime);
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

void Mario::handleCollision(Tile& tile)
{
	std::cout << "Collision detected!" << std::endl;
}