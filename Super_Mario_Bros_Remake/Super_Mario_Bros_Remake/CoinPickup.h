#pragma once
#include "GameObject.h"
#include "Animation.h"
#include <SFML/Audio.hpp>

class CoinPickup : public GameObject
{
public:
	CoinPickup(sf::Vector2f pos);
	~CoinPickup();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();

private:
	Animation anim;
	sf::SoundBuffer coinSoundBuffer;
	sf::Sound coinSound;
};