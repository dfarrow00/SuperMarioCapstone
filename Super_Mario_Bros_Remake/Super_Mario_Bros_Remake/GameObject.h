#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Map;
class Animation;

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

	const bool getFacingLeft() const
	{
		return facingLeft;
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

	void setFacingLeft(const bool val)
	{
		isBig = val;
	}

	float getDistance(GameObject* obj)
	{
		return std::abs(position.x - obj->getPosition().x);
	}

protected:
	bool alive = true;
	bool active = true;
	bool facingLeft = false;
	bool isBig;

	float maxVelocity;
	const float GRAVITY = 1600.0f;

	int spriteHeight;

	Animation* currentAnim;

	Map* map;

	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::Texture texture;
	sf::Sprite sprite;
};