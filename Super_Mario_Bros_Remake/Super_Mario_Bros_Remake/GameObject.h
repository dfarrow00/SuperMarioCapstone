#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual sf::FloatRect getAABB() = 0;

	const sf::Vector2f getPosition() const
	{
		return position;
	}

	const sf::Vector2f getVelocity() const
	{
		return velocity;
	}

	const sf::Texture getTexture() const
	{
		return texture;
	}

	const sf::Sprite getSprite() const
	{
		return sprite;
	}

protected:
	sf::Vector2f position;
	sf::Vector2f velocity;
	float maxVelocity;
	sf::Texture texture;
	sf::Sprite sprite;
};