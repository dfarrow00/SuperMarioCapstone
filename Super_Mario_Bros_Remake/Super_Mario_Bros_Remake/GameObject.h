#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Map;
class Animation;

enum class ObjectType
{
	Mario, Coin, CoinBrick, Goomba, KoopaTroopa, RedKoopaTroopa, Mushroom, Particle, Star, CoinPickup, PiranhaPlant, Platform
};

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void update(const float deltaTime) = 0;
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

	void setPosition(float x, float y)
	{
		position = sf::Vector2f(x, y);
		sprite.setPosition(position);
	}

	void setActive(bool act)
	{
		active = act;
	}

	void setFacingLeft(const bool val)
	{
		facingLeft = val;
	}

	float getDistance(GameObject* obj)
	{
		return std::abs(position.x - obj->getPosition().x);
	}

	void setCollidingX(bool val)
	{
		collidingX = val;
	}

	void setCollidingY(bool val)
	{
		collidingY = val;
	}

	void setOnGround(bool val)
	{
		onGround = val;
	}

	bool getCheckCollision()
	{
		return checkCollisions;
	}

	int getSpriteHeight()
	{
		return spriteHeight;
	}

	ObjectType getObjectType()
	{
		return objectType;
	}

protected:
	bool alive = true;
	bool active = true;
	bool facingLeft = false;
	bool isBig;
	bool onGround = false;

	bool checkCollisions = true;
	bool collidingX = false;
	bool collidingY = false;

	float maxVelocity;

	int spriteHeight;

	Animation* currentAnim;

	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::Texture texture;
	sf::Sprite sprite;

	ObjectType objectType;
};