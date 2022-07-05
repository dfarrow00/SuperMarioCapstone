#include "Mario.h"
#include <iostream>

Mario::Mario(Map* gameMap) : GameObject(), idleAnim("Resources/Mario_SpriteSheet.png", 0, 1), runningAnim("Resources/Mario_SpriteSheet.png", 1, 3, 0.2), JumpingAnim("Resources/Mario_SpriteSheet.png", 2, 1), map(gameMap)
{
	setup();
}

Mario::Mario(Map* gameMap, sf::Vector2f& pos) : GameObject(), idleAnim("Resources/Mario_SpriteSheet.png", 0, 1, 10), runningAnim("Resources/Mario_SpriteSheet.png", 1, 3, 0.5), JumpingAnim("Resources/Mario_SpriteSheet.png", 2, 1, 0.5), map(gameMap)
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
	alive = true;
}

void Mario::reset()
{
	setup();
}

void Mario::update(float deltaTime)
{
	currentState = MarioState::Idle;

	handleInput(deltaTime);
	checkCollisions(deltaTime);
	updateState(deltaTime);

	position = position + (velocity * deltaTime);
	sprite.setPosition(position);
}

void Mario::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
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
		velocity.y = -350; //Not multiplied by dt as it is an impulse force and will be the same for all framerates
		currentState = MarioState::Jumping;
		jumpTime = 0.4f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !onGround)
	{
		jumpTime -= deltaTime;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		jumpTime = 0.0f;
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

	if (jumpTime <= 0.0f)
	{
		velocity.y += 800 * deltaTime;
	}
}

void Mario::checkCollisions(float deltaTime)
{
	if (position.x + (velocity.x * deltaTime) < 0 || position.y + (velocity.y * deltaTime) >= 670)
	{
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		alive = false;
		return;
	}

	if (map->isColliding(position, sf::Vector2f(velocity.x * deltaTime, 0)))
	{
		velocity.x = 0.0f;
	}

	if (map->isColliding(position, sf::Vector2f(0, velocity.y * deltaTime)))//Causes mario to stop briefly before hitting floor on low fps. Needs fix
	{
		velocity.y = 0.0f;
	}

	if (map->isColliding(position, sf::Vector2f(0, 1)))
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

void Mario::hit()
{
	alive = false;
	std::cout << "Hit" << std::endl;
}

void Mario::powerUp()
{
	std::cout << "Power Up" << std::endl;
}

void Mario::addVelocity(sf::Vector2f vel)
{
	velocity += vel;
}