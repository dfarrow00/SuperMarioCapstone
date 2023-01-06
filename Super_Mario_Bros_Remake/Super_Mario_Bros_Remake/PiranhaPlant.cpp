#include "PiranhaPlant.h"

PiranhaPlant::PiranhaPlant(sf::Vector2f pos) : movementAnimation("Resources/Sprites/Blue_Piranha_SpriteSheet.png", 0, 2, 0.2, 72)
{
	objectType = ObjectType::PiranhaPlant;
	spriteHeight = 72;
	position = (pos + sf::Vector2f(0, spriteHeight));
	currentAnim = &movementAnimation;
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);
	velocity = sf::Vector2f(0, 50);
	checkCollisions = false;
	targetPos = pos + sf::Vector2f(0, spriteHeight * 2);
}

PiranhaPlant::~PiranhaPlant()
{
}

void PiranhaPlant::update(const float deltaTime)
{
	if (velocity.y > 0 && position.y > targetPos.y)
	{
		velocity.y = velocity.y * -1;
		targetPos.y = targetPos.y - (spriteHeight * 2);
	}
	else if (velocity.y < 0 && position.y < targetPos.y)
	{
		velocity.y = velocity.y * -1;
		targetPos.y = targetPos.y + (spriteHeight * 2);
	}
	position += velocity * deltaTime;
	currentAnim->update(deltaTime);
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);
}

void PiranhaPlant::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void PiranhaPlant::hit()
{
	
}

void PiranhaPlant::activate()
{
	active = true;
}