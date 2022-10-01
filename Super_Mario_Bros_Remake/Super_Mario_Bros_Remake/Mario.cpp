#include "Mario.h"
#include <iostream>

Mario::Mario(Map* gameMap) : GameObject(), idleAnim("Resources/Mario_SpriteSheet.png", 0, 1), runningAnim("Resources/Mario_SpriteSheet.png", 1, 3, 0.2),
JumpingAnim("Resources/Mario_SpriteSheet.png", 2, 1), flagGrabAnim("Resources/Mario_SpriteSheet.png", 3, 1), deathAnim("Resources/Mario_SpriteSheet.png", 4, 1), 
bigIdleAnim("Resources/Big_Mario_SpriteSheet.png", 0, 1, 100.0f, true), bigRunningAnim("Resources/Big_Mario_SpriteSheet.png", 1, 3, 0.2, true), 
bigJumpingAnim("Resources/Big_Mario_SpriteSheet.png", 2, 1, 100.0f, true), bigFlagGrabAnim("Resources/Big_Mario_SpriteSheet.png", 3, 2, 0.2, true), map(gameMap)
{
	setup();
}

Mario::Mario(Map* gameMap, sf::Vector2f& pos) : GameObject(), idleAnim("Resources/Mario_SpriteSheet.png", 0, 1), runningAnim("Resources/Mario_SpriteSheet.png", 1, 3, 0.2),
JumpingAnim("Resources/Mario_SpriteSheet.png", 2, 1), flagGrabAnim("Resources/Mario_SpriteSheet.png", 3, 1), deathAnim("Resources/Mario_SpriteSheet.png", 4, 1),
bigIdleAnim("Resources/Big_Mario_SpriteSheet.png", 0, 1, 100.0f, true), bigRunningAnim("Resources/Big_Mario_SpriteSheet.png", 1, 3, 0.2, true),
bigJumpingAnim("Resources/Big_Mario_SpriteSheet.png", 2, 1, 100.0f, true), bigFlagGrabAnim("Resources/Big_Mario_SpriteSheet.png", 3, 2, 0.2, true), map(gameMap)
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
	isBig = false;
	invinsible = false;
	playingLevelCompleteAnim = false;
	finishReached = false;
}

void Mario::reset()
{
	setup();
}

void Mario::update(float deltaTime)
{
	currentState = MarioState::Idle;
	if (playingLevelCompleteAnim)
	{
		updateLevelCompleteAnim(deltaTime);
	}
	else
	{
		handleInput(deltaTime);
		checkCollisions(deltaTime);
		updateState(deltaTime);
	}

	position = position + (velocity * deltaTime);
	sprite.setPosition(position);

	if (invinsible)
	{
		handleInvincibility(deltaTime);
	}
}

void Mario::draw(sf::RenderWindow* window)
{
	if (isVisible)
	{
		window->draw(sprite);
	}
}

void Mario::handleInput(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= speed * deltaTime;
		if (velocity.x < -maxVelocity)
		{
			velocity.x = -maxVelocity;
		}
		currentState = MarioState::Running_Left;
		facingLeft = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += speed * deltaTime;
		if (velocity.x > maxVelocity)
		{
			velocity.x = maxVelocity;
		}
		currentState = MarioState::Running_Right;
		facingLeft = false;
	}

	//Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround)
	{
		velocity.y = -jumpVelocity; //Not multiplied by dt as it is an impulse force and will be the same for all framerates
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

	//Applying drag
	if (velocity.x > 0)
	{
		velocity.x -= drag * deltaTime;
		if (velocity.x < 0.0f)
		{
			velocity.x = 0.0f;
		}
	}
	else if (velocity.x < 0)
	{
		velocity.x += drag * deltaTime;
		if (velocity.x > 0.0f)
		{
			velocity.x = 0.0f;
		}
	}

	//If jump time limit reached, start pulling player downwards
	if (jumpTime <= 0.0f)
	{
		velocity.y += gravity * deltaTime;
	}
}

void Mario::checkCollisions(float deltaTime)
{
	if (position.x + (velocity.x * deltaTime) < 0 || position.y + (velocity.y * deltaTime) >= 670)//Out of bounds check.
	{
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		alive = false;
		return;
	}

	if (map->isColliding(position, sf::Vector2f(velocity.x * deltaTime, 0), isBig))//Checking collision along the x axis
	{
		velocity.x = 0.0f;
	}

	if (map->isColliding(position, sf::Vector2f(0, velocity.y * deltaTime), isBig))//Checking collision along the y axis. Causes mario to stop briefly before hitting floor on low fps. Needs fix
	{
		velocity.y = 0.0f;
	}

	if (map->isColliding(position, sf::Vector2f(0, 1), isBig))//Ground check
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
	if (!isBig)
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
		else if (currentState == MarioState::Grabbing_Flag && currentAnim != &flagGrabAnim)
		{
			currentAnim = &flagGrabAnim;
			currentAnim->reset();
		}
	}
	else
	{
		if (currentState == MarioState::Idle && currentAnim != &bigIdleAnim)
		{
			currentAnim = &bigIdleAnim;
			currentAnim->reset();
		}
		else if ((currentState == MarioState::Running_Right || currentState == MarioState::Running_Left) && currentAnim != &bigRunningAnim)
		{
			currentAnim = &bigRunningAnim;
			currentAnim->reset();
		}
		else if (currentState == MarioState::Jumping && currentAnim != &bigJumpingAnim)
		{
			currentAnim = &bigJumpingAnim;
			currentAnim->reset();
		}
		else if (currentState == MarioState::Grabbing_Flag && currentAnim != &bigFlagGrabAnim)
		{
			currentAnim = &bigFlagGrabAnim;
			currentAnim->reset();
		}
	}

	currentAnim->update(deltaTime);
	sprite = currentAnim->getCurrentSprite();
	if (facingLeft)
	{
		sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
		sprite.scale(-1, 1);
	}
}

void Mario::handleInvincibility(float deltaTime)
{
	currentInvTime += deltaTime;
	flashingTimer += deltaTime;
	if (flashingTimer >= flashingRate)
	{
		isVisible = !isVisible;
		flashingTimer = 0.0f;
	}
	if (currentInvTime > invinsibilityTime)
	{
		invinsible = false;
		isVisible = true;
		currentInvTime = 0.0f;
	}
}

void Mario::hit()
{
	if (isBig)
	{
		setBig(false);
		invinsible = true;
	}
	else
	{
		alive = false;
	}
}

void Mario::powerUp()
{
	setBig(true);
}

void Mario::addVelocity(sf::Vector2f vel)
{
	velocity += vel;
}

void Mario::setVelocityY(float value)
{
	velocity.y = value;
}

void Mario::setBig(bool value)
{
	if (!isBig && value)
	{
		isBig = value;
		position.y -= 48;
	}
	else if (isBig && !value)
	{
		isBig = value;
		position.y += 48;
	}
}

bool Mario::getInvinsible()
{
	return invinsible;
}

void Mario::playLevelCompleteAnim()
{
	playingLevelCompleteAnim = true;
	currentState = MarioState::Grabbing_Flag;

	sf::Vector2f flagPolePos = map->getFlagPolePos();
	position.x = flagPolePos.x;
	if (facingLeft)
	{
		position.x += 24;
	}
	else
	{
		position.x -= 24;
	}

	if (position.y < flagPolePos.y)
	{
		position.y = flagPolePos.y;
	}
	else if (!isBig && position.y > 528)
	{
		position.y = 528;
	}
	else if (isBig && position.y > 480)
	{
		position.y = 480;
	}
	velocity = sf::Vector2f(0, 200);
}

void Mario::updateLevelCompleteAnim(float deltaTime)
{
	if (velocity.x == 0)
	{
		currentState = MarioState::Grabbing_Flag;
	}
	updateState(deltaTime);

	if ((!isBig && position.y >= 528 && !velocity.y == 0.0f) || (isBig && position.y >= 480 && !velocity.y == 0.0f))
	{
		velocity.y = 0.0f;
	}
	else if (velocity.y == 0.0f)
	{
		currentLevelCompleteTime += deltaTime;
		if (currentLevelCompleteTime >= levelCompleteDelay)
		{
			finishReached = true;
		}
	}
}

bool Mario::getFinishReached()
{
	return finishReached;
}
