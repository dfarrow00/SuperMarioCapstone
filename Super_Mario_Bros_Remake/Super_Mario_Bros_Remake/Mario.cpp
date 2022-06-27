#include "Mario.h"
#include <iostream>

Mario::Mario() : GameObject()
{
	texture.loadFromFile("Resources/Mario.png");
	sprite.setTexture(texture);
	position = sf::Vector2f(96.0f, 96.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	maxVelocity = 400.0f;
	onGround = false;
}

Mario::Mario(sf::Vector2f& pos)
{
	texture.loadFromFile("Resources/Mario.png");
	sprite.setTexture(texture);
	position = pos;
	velocity = sf::Vector2f(0.0f, 0.0f);
	maxVelocity = 400.0f;
	onGround = false;
}

Mario::~Mario()
{
}

void Mario::update(float deltaTime, Level level)
{
	sf::Vector2f oldPosition = getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= 800 * deltaTime;
		if (velocity.x < -maxVelocity)
		{
			velocity.x = -maxVelocity;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += 800 * deltaTime;
		if (velocity.x > maxVelocity)
		{
			velocity.x = maxVelocity;
		}
	}

	if (velocity.x > 0)
	{
		velocity.x -= 400 * deltaTime; //DRAG
		if (velocity.x < 0.0f)
		{
			velocity.x = 0.0f;
		}
	}
	else if (velocity.x < 0)
	{
		velocity.x += 400 * deltaTime;
		if (velocity.x > 0.0f)
		{
			velocity.x = 0.0f;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround)
	{
		velocity.y = -600; //Not multiplied by dt as it is an impulse force and will be the same for all framerates
	}

	velocity.y += 800 * deltaTime;

	if (colliding(position + sf::Vector2f(velocity.x * deltaTime, 0), level))
	{
		velocity.x = 0.0f;
	}

	if (colliding(position + sf::Vector2f(0, velocity.y * deltaTime), level))//Causes mario to stop briefly before hitting floor on low fps. Needs fix
	{
		velocity.y = 0.0f;
	}
	
	if (colliding(position + sf::Vector2f(0, 1), level))
	{
		onGround = true;
	}
	else
	{
		onGround = false;
	}

	position = position + (velocity * deltaTime);
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


bool Mario::colliding(sf::Vector2f currentPos, Level level)
{
	sf::Vector2f topLeft = currentPos;
	sf::Vector2f topRight = topLeft; topRight.x += 48;
	sf::Vector2f bottomLeft = topLeft; bottomLeft.y += 48;
	sf::Vector2f bottomRight = topRight; bottomRight.y += 48;

	if (topLeft.x < 0)
	{
		return true;
	}

	unsigned int tile = level[topLeft.y / 48][topLeft.x / 48];
	if (tile > 0)
	{
		return true;
	}

	tile = level[topRight.y / 48][topRight.x / 48];
	if (tile > 0)
	{
		return true;
	}

	tile = level[bottomLeft.y / 48][bottomLeft.x / 48];
	if (tile > 0)
	{
		return true;
	}

	tile = level[bottomRight.y / 48][bottomRight.x / 48];
	if (tile > 0)
	{
		return true;
	}

	return false;
}