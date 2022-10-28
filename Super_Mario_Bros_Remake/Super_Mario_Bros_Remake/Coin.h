#pragma once
#include "GameObject.h"
#include "Animation.h"
#include <SFML/Audio.hpp>

class Coin : public GameObject
{
public:
	Coin(sf::Vector2f pos);
	~Coin();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();
private:
	float speed = 300.0f;
	float lifetime = 0.25;

	sf::SoundBuffer soundBuffer;
	sf::Sound sound;

	Animation anim;
};