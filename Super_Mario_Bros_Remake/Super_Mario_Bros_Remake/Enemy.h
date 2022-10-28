#pragma once
#include "GameObject.h"
#include <SFML/Audio.hpp>

class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

	void hit();

protected:
	void move(float deltaTime);

	sf::SoundBuffer hitSoundBuffer;
	sf::Sound hitSound;
};