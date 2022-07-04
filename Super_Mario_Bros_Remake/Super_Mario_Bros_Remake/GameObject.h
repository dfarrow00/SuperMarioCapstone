#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow* window) = 0;

	virtual void hit() = 0;

	sf::FloatRect getAABB()
	{
		return sprite.getGlobalBounds();
	}

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

	const bool isAlive() const
	{
		return alive;
	}

protected:
	bool alive;

	sf::Vector2f position;
	sf::Vector2f velocity;
	float maxVelocity;

	sf::Texture texture;
	sf::Sprite sprite;
};