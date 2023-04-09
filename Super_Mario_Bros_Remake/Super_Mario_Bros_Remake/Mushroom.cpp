#include "Mushroom.h"
#include "Map.h"

Mushroom::Mushroom(sf::Vector2f pos) : spawning(true)
{
	objectType = ObjectType::Mushroom;
	texture.loadFromFile("Resources/Sprites/Mushroom.png");
	sprite.setTexture(texture);
	position = pos;
	targetSpawnPos = position + sf::Vector2f(0, -48);
	velocity = sf::Vector2f(0, -65);
	alive = true;
	spriteHeight = 48;
	checkCollisions = false;
	spawnSoundBuffer.loadFromFile("Resources/Audio/Powerup_Spawn.wav");
	spawnSound.setBuffer(spawnSoundBuffer);
	spawnSound.play();
}

Mushroom::~Mushroom()
{
}

void Mushroom::update(const float deltaTime)
{
	if (spawning)
	{
		if (position.y <= targetSpawnPos.y)
		{
			spawning = false;
			checkCollisions = true;
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

		if (collidingX)
		{
			velocity.x = -velocity.x;
			collidingX = false;
		}

		//Prob move to gameobject class
		if (collidingY)
		{
			velocity.y = 0;
			collidingY = false;
		}
		else
		{
			velocity.y += Globals::GRAVITY * deltaTime;
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