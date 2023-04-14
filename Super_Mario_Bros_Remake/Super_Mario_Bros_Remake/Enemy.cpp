#include "Enemy.h"
#include "Map.h"
#include "Animation.h"

Enemy::Enemy()
{
	hitSoundBuffer.loadFromFile("Resources/Audio/Enemy_Hit.wav");
	hitSound.setBuffer(hitSoundBuffer);
}

Enemy::~Enemy()
{
}

void Enemy::move(const float deltaTime)
{
	if (position.x + velocity.x < 0.0f || collidingX)
	{
		velocity.x = -velocity.x;
		facingLeft = !facingLeft;
		collidingX = false;
	}

	if (collidingY)
	{
		velocity.y = 0;
		collidingY = false;
	}
	else
	{
		velocity.y += Globals::GRAVITY * deltaTime;
	}

	position += velocity * deltaTime;

	currentAnim->update(deltaTime);
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);

	if (facingLeft)
	{
		sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
		sprite.scale(-1, 1);
	}
}

void Enemy::hit()
{
	hitSound.play();
}