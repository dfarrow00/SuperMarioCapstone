#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(std::string filePath, int rowNumber, int frames, float animSpeed = 100, int spriteHeight = 48);
	~Animation();

	void reset();

	void update(const float deltaTime);

	sf::Sprite getCurrentSprite();

private:
	sf::Texture spriteSheet;
	std::vector<sf::Sprite> sprites;
	sf::Sprite currentSprite;
	int currentFrame;

	float animationSpeed;
	float elapsedTime;
};