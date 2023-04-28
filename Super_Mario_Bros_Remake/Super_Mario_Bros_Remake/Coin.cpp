#include "Coin.h"

Coin::Coin(sf::Vector2f pos) : anim("Resources/Sprites/Coin_SpriteSheet.png", 0, 2, 0.1)
{
	objectType = ObjectType::Coin;
	position = pos;
	checkCollisions = false;
	sprite = anim.getCurrentSprite();
	soundBuffer.loadFromFile("Resources/Audio/Coin_Pickup.wav");
	sound.setBuffer(soundBuffer);
	sound.play();
	velocity.y = 300.0f;
}

Coin::~Coin()
{
}

void Coin::update(const float deltaTime)
{
	lifetime -= deltaTime;
	if (lifetime <= 0.0f && sound.getStatus() == sf::Sound::Status::Stopped)
	{
		alive = false;
		return;
	}

	position.y -= velocity.y * deltaTime;

	anim.update(deltaTime);
	sprite = anim.getCurrentSprite();
	sprite.setPosition(position);
}

void Coin::draw(sf::RenderWindow* window)
{
	if (lifetime > 0)
	{
		window->draw(sprite);
	}
}

void Coin::hit()
{
}