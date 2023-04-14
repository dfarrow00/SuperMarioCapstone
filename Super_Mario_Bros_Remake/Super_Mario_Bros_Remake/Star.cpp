#include "Star.h"
#include "Map.h"

Star::Star(sf::Vector2f pos) : anim("Resources/Sprites/Star_Power_SpriteSheet.png", 0, 2, 0.2)
{
	objectType = ObjectType::Star;
	position = pos;
	targetSpawnPos = position + sf::Vector2f(0, -48);
	spriteHeight = 48;
	velocity.y = -65;
	checkCollisions = false;
	anim.reset();
	sprite = anim.getCurrentSprite();
	spawnSoundBuffer.loadFromFile("Resources/Audio/Powerup_Spawn.wav");
	spawnSound.setBuffer(spawnSoundBuffer);
	spawnSound.play();
}

Star::~Star()
{
}

void Star::update(const float deltaTime)
{
	//If playing spawning animation, check if target y co-ordinate has been reached.
	if (spawning)
	{
		//If target co-ordinate reached, stop animation and activate functionality.
		if (position.y <= targetSpawnPos.y)
		{
			spawning = false;
			checkCollisions = true;
			velocity.x = 300;
			velocity.y = -700;
		}
	}
	else
	{
		anim.update(deltaTime);
		sprite = anim.getCurrentSprite();

		if (position.x + velocity.x * deltaTime < 0.0f)
		{
			velocity.x = -velocity.x;
		}

		if (collidingX)
		{
			velocity.x = -velocity.x;
			collidingX = false;
		}

		//If collides with ground, bounce.
		if (onGround)
		{
			velocity.y = -700.0f;
		}
		else
		{
			velocity.y += Globals::GRAVITY * deltaTime;
		}

		onGround = false;
		collidingY = false;
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