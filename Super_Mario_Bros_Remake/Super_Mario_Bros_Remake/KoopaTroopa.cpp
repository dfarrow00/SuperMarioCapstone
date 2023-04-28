#include "KoopaTroopa.h"
#include "Map.h"

KoopaTroopa::KoopaTroopa(sf::Vector2f pos, bool red) : walkingAnim((red ? "Resources/Sprites/Red_Koopa_Troopa_Spritesheet.png" : "Resources/Sprites/Koopa_Troopa_Spritesheet.png"), 0, 2, 0.2, 72), 
shellAnim((red ? "Resources/Sprites/Red_Koopa_Troopa_Spritesheet.png": "Resources/Sprites/Koopa_Troopa_Spritesheet.png"), 2, 1, 0.2, 48)
{
	if (red)
	{
		objectType = ObjectType::RedKoopaTroopa;
	}
	else
	{
		objectType = ObjectType::KoopaTroopa;
	}
	position = pos;

	currentState = KoopaState::Walking;
	currentAnim = &walkingAnim;
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);

	velocity = sf::Vector2f(-75, 0);
	facingLeft = true;
	isBig = true;

	spriteHeight = 72;
	stationaryTimeLimit = 5.0f;
}

KoopaTroopa::~KoopaTroopa()
{
}

void KoopaTroopa::update(const float deltaTime)
{
	if (playingDeathAnim)
	{
		updateDeathAnim(deltaTime);
	}

	if (currentState == KoopaState::Shell && currentAnim != &shellAnim)
	{
		currentAnim = &shellAnim;
		currentAnim->reset();
		velocity.x = 0.0f;
		position.y += 24.0f;
	}

	if (currentState == KoopaState::Shell && velocity.x == 0.0f)
	{
		stationaryShellTimer += deltaTime;
		//If max amount of stationary time has passed, return to walking state.
		if (stationaryShellTimer >= stationaryTimeLimit)
		{
			currentState = KoopaState::Walking;
			currentAnim = &walkingAnim;
			position.y -= 24.0f;
			spriteHeight = 72;
			if (facingLeft)
			{
				velocity.x = -75.0f;
			}
			else
			{
				velocity.x = 75.0f;
			}
			stationaryShellTimer = 0.0f;
		}
	}

	move(deltaTime);
}

void KoopaTroopa::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void KoopaTroopa::hit()
{
	Enemy::hit();
	if (currentState == KoopaState::Shell && !playingDeathAnim)
	{
		playDeathAnim();
	}
	else
	{
		currentState = KoopaState::Shell;
		isBig = false;
		spriteHeight = 48;
	}
}

void KoopaTroopa::kick(bool direction)
{
	if (velocity.x == 0.0f)
	{
		//Direction = true, move to the right
		if (direction)
		{
			velocity.x = 700.0f;
		}
		else
		{
			velocity.x = -700.0f;
		}
	}
	else
	{
		velocity.x = 0.0f;
	}
}

void KoopaTroopa::activate()
{
	active = true;
}

void KoopaTroopa::playDeathAnim()
{
	playingDeathAnim = true;
	active = false;
	velocity = sf::Vector2f(0, -750);
}

void KoopaTroopa::updateDeathAnim(const float deltaTime)
{
	currentDeathAnimTime += deltaTime;
	if (currentDeathAnimTime >= deathAnimTime)
	{
		alive = false;
		playingDeathAnim = false;
		return;
	}
	velocity.y += Globals::GRAVITY * deltaTime;
}

KoopaState KoopaTroopa::getCurrentState()
{
	return currentState;
}