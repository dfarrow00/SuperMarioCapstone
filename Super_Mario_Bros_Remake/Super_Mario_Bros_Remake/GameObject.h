#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

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

	const bool isActive() const
	{
		return active;
	}

	void setVelocity(sf::Vector2f vel)
	{
		velocity = vel;
	}

	void setActive(bool act)
	{
		active = act;
	}

	float getDistance(GameObject* obj)
	{
		return std::abs(position.x - obj->getPosition().x);
	}

protected:
	bool alive = true;
	bool active = true;

	sf::Vector2f position;
	sf::Vector2f velocity;
	float maxVelocity;

	sf::Texture texture;
	sf::Sprite sprite;
};