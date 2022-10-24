#include "Enemy.h"
#include "Map.h"
#include "Animation.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::move(float deltaTime)
{
	if (position.y + (velocity.y * deltaTime) >= 670)
	{
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		hit();
		return;
	}

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
		velocity.y += GRAVITY * deltaTime;
	}

	/*if (map->isColliding(position, sf::Vector2f(velocity.x * deltaTime, 0), spriteHeight))
	{
		velocity.x = -velocity.x;
		facingLeft = !facingLeft;
	}

	velocity.y += GRAVITY * deltaTime;

	if (map->isColliding(position, sf::Vector2f(0, velocity.y * deltaTime), spriteHeight))
	{
		velocity.y = 0.0f;
	}*/

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