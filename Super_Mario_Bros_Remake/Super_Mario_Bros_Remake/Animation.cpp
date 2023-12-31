#include "Animation.h"
#include <iostream>

Animation::Animation(std::string filePath, int rowNumber, int frames, float animSpeed, int spriteHeight) : animationSpeed(animSpeed)
{
	//Load each frame of animation
	spriteSheet.loadFromFile(filePath);
	for (int x = 0; x < frames * 48; x += 48)
	{
		sf::Sprite frame(spriteSheet, sf::IntRect(x, rowNumber * spriteHeight, 48, spriteHeight));
		sprites.push_back(frame);
	}

	std::reverse(sprites.begin(), sprites.end());
	currentFrame = 0;
	currentSprite = sprites[0];
	elapsedTime = 0.0f;
}

Animation::~Animation()
{
}

void Animation::reset()
{
	elapsedTime = 0.0f;
	currentSprite = sprites[0];
	currentFrame = 0;
}

void Animation::update(const float deltaTime)
{
	elapsedTime += deltaTime;
	//Progress to next frame if enough time has passed
	if (elapsedTime >= animationSpeed)
	{
		currentFrame++;
		if (currentFrame > sprites.size() - 1)
		{
			currentFrame = 0;
		}
		currentSprite = sprites[currentFrame];
		elapsedTime = 0.0f;
	}
}

sf::Sprite Animation::getCurrentSprite()
{
	return currentSprite;
}