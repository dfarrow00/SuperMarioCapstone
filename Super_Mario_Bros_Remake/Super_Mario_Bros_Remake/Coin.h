#pragma once
#include "GameObject.h"
#include "Animation.h"
#include <SFML/Audio.hpp>

class Coin : public GameObject
{
public:
	Coin(sf::Vector2f pos);
	~Coin();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();
private:
	float lifetime = 0.25;

	sf::SoundBuffer soundBuffer;
	sf::Sound sound;

	Animation anim;
};