#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include "Animation.h"

class Star : public GameObject
{
public:
	Star(sf::Vector2f pos);
	~Star();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();

private:
	bool spawning = true;
	sf::Vector2f targetSpawnPos;
	Animation anim;

	sf::SoundBuffer spawnSoundBuffer;
	sf::Sound spawnSound;
};