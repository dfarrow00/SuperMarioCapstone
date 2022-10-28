#include "KoopaTroopa.h"
#include "Map.h"

KoopaTroopa::KoopaTroopa(sf::Vector2f pos) : walkingAnim("Resources/Sprites/Koopa_Troopa_Spritesheet.png", 0, 2, 0.2, 72), shellAnim("Resources/Sprites/Koopa_Troopa_Spritesheet.png", 2, 1, 0.2, 48)
{
	objectType = ObjectType::KoopaTroopa;
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

void KoopaTroopa::update(float deltaTime)
{
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
	currentState = KoopaState::Shell;
	isBig = false;
	spriteHeight = 48;
}

void KoopaTroopa::kick(bool direction)
{
	if (velocity.x == 0.0f)
	{
		if (direction)
		{
			velocity.x = 550.0f;
		}
		else
		{
			velocity.x = -550.0f;
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

KoopaState KoopaTroopa::getCurrentState()
{
	return currentState;
}