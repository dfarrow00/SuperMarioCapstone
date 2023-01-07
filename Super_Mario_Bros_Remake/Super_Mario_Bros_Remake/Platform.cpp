#include "Platform.h"

Platform::Platform(sf::Vector2f pos, bool travellingUp)
{
	objectType = ObjectType::Platform;
	texture.loadFromFile("Resources/Sprites/Platform.png");
	sprite.setTexture(texture);
	position = pos;
	sprite.setPosition(pos);
	velocity = sf::Vector2f(0, (travellingUp ? -75 : 75));
	alive = true;
	spriteHeight = 24;
	checkCollisions = false;
}

Platform::~Platform()
{
}

void Platform::update(const float deltaTime)
{
	if (velocity.y < 0 && position.y <= -50)
	{
		position.y = 800;
	}
	else if (velocity.y > 0 && position.y >= 800)
	{
		position.y = -50;
	}
	position += velocity * deltaTime;
	sprite.setPosition(position);
}

void Platform::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Platform::hit()
{
}