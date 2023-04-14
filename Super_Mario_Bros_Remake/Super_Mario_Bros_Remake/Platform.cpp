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
	//If moving upwards and top of view has been reached, reset position to bottom of view.
	if (velocity.y < 0 && position.y <= -50)
	{
		position.y = 800;
	}
	//If moving downwards and bottom of view has been reached, reset position to top of view.
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