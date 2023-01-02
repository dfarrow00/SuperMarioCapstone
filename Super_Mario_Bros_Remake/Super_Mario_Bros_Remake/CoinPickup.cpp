#include "CoinPickup.h"

CoinPickup::CoinPickup(sf::Vector2f pos) : anim("Resources/Sprites/Coin_Pickup_Spritesheet.png", 0, 3, 0.3)
{
	objectType = ObjectType::CoinPickup;
	position = pos;
	currentAnim = &anim;
	coinSoundBuffer.loadFromFile("Resources/Audio/Coin_Pickup.wav");
	coinSound.setBuffer(coinSoundBuffer);
}

CoinPickup::~CoinPickup()
{
}

void CoinPickup::update(const float deltaTime)
{
	if (!active && coinSound.getStatus() != sf::Sound::Status::Playing)
	{
		alive = false;
		return;
	}
	currentAnim->update(deltaTime);
	sprite = currentAnim->getCurrentSprite();
	sprite.setPosition(position);
}

void CoinPickup::draw(sf::RenderWindow* window)
{
	if (active)
	{
		window->draw(sprite);
	}
}

void CoinPickup::hit()
{
	if (active)
	{
		coinSound.play();
		active = false;
	}
}