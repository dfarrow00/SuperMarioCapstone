#include "Mario.h"
#include <iostream>

Mario::Mario() : GameObject(), idleAnim("Resources/Mario_SpriteSheet.png", 0, 1), runningAnim("Resources/Mario_SpriteSheet.png", 1, 3, 0.2), JumpingAnim("Resources/Mario_SpriteSheet.png", 2, 1)
{
	setup();
}

Mario::Mario(sf::Vector2f& pos) : GameObject(), idleAnim("Resources/Mario_SpriteSheet.png", 0, 1, 10), runningAnim("Resources/Mario_SpriteSheet.png", 1, 3, 0.5), JumpingAnim("Resources/Mario_SpriteSheet.png", 2, 1, 0.5)
{
	setup();
	position = pos;
}

Mario::~Mario()
{
}

void Mario::setup()
{
	currentAnim = &idleAnim;
	sprite = currentAnim->getCurrentSprite();
	position = sf::Vector2f(96.0f, 575.5f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	sprite.setPosition(position);
	maxVelocity = 400.0f;
	onGround = false;
	currentState = MarioState::Idle;
	currentAnim = nullptr;
	facingLeft = false;
}

void Mario::reset()
{
	setup();
}

void Mario::update(float deltaTime, Level level)
{
	currentState = MarioState::Idle;

	handleInput(deltaTime);
	checkCollisions(deltaTime, level);
	updateState(deltaTime);

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

void Mario::handleInput(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= 800 * deltaTime;
		if (velocity.x < -maxVelocity)
		{
			velocity.x = -maxVelocity;
		}
		currentState = MarioState::Running_Left;
		facingLeft = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += 800 * deltaTime;
		if (velocity.x > maxVelocity)
		{
			velocity.x = maxVelocity;
		}
		currentState = MarioState::Running_Right;
		facingLeft = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround)
	{
		velocity.y = -600; //Not multiplied by dt as it is an impulse force and will be the same for all framerates
		currentState = MarioState::Jumping;
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

	velocity.y += 800 * deltaTime;
}

void Mario::checkCollisions(float deltaTime, Level level)
{
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
		currentState = MarioState::Jumping;
	}
}

void Mario::updateState(float deltaTime)
{
	if (currentState == MarioState::Idle && currentAnim != &idleAnim)
	{
		currentAnim = &idleAnim;
		currentAnim->reset();
	}
	else if ((currentState == MarioState::Running_Right || currentState == MarioState::Running_Left) && currentAnim != &runningAnim)
	{
		currentAnim = &runningAnim;
		currentAnim->reset();
	}
	else if (currentState == MarioState::Jumping && currentAnim != &JumpingAnim)
	{
		currentAnim = &JumpingAnim;
		currentAnim->reset();
	}

	currentAnim->update(deltaTime);
	sprite = currentAnim->getCurrentSprite();
	if (facingLeft)
	{
		sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
		sprite.scale(-1, 1);
	}
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