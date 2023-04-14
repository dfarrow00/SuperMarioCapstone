#include "PiranhaPlant.h"

PiranhaPlant::PiranhaPlant(sf::Vector2f pos, bool underground) : movementAnimation((underground ? "Resources/Sprites/Blue_Piranha_SpriteSheet.png" : "Resources/Sprites/Piranha_SpriteSheet.png"), 0, 2, 0.2, 72)
{
	objectType = ObjectType::PiranhaPlant;
	spriteHeight = 72;
	position = (pos + sf::Vector2f(0, spriteHeight));
	currentAnim = &movementAnimation;
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);
	velocity = sf::Vector2f(0, 50);
	checkCollisions = false;
	targetPos = pos + sf::Vector2f(0, spriteHeight * 2);//Y co-ordinate to reach before changing movement direction.
}

PiranhaPlant::~PiranhaPlant()
{
}

void PiranhaPlant::update(const float deltaTime)
{
	//If moving downwards and target position reached, changed direction.
	if (velocity.y > 0 && position.y > targetPos.y)
	{
		velocity.y = velocity.y * -1;
		targetPos.y = targetPos.y - (spriteHeight * 2);
	}
	//If moving upwards and target position reached, changed direction.
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