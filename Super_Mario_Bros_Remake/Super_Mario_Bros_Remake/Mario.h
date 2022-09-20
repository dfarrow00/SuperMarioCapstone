#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Map.h"
#include "Animation.h"

enum class MarioState
{
	Idle, Running_Right, Running_Left, Jumping
};

class Mario : public GameObject
{
public:
	Mario(Map* gameMap);
	Mario(Map* gameMap, sf::Vector2f& pos);
	~Mario();

	void setup();
	void reset();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();
	void powerUp();

	void addVelocity(sf::Vector2f vel);
	void setVelocityY(float value);

private:
	void handleInput(float deltaTime);
	void checkCollisions(float deltaTime);
	void updateState(float deltaTime);

	float jumpTime = 0.0f;
	float jumpVelocity = 450.0f;
	float speed = 800.0f;
	float drag = 400.0f;
	float gravity = 1600.0f;

	bool onGround;
	bool facingLeft;

	Animation* currentAnim;
	Animation idleAnim;
	Animation runningAnim;
	Animation JumpingAnim;

	MarioState currentState;

	Map* map;
};