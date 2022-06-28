#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Map.h"
#include "Animation.h"

enum class State
{
	Idle, Running_Right, Running_Left, Jumping
};

class Mario : public GameObject
{
public:
	Mario();
	Mario(sf::Vector2f& pos);
	~Mario();

	void update(float deltaTime, Level level);
	void draw(sf::RenderWindow* window);

	bool colliding(sf::Vector2f currentPos, Level level);

	sf::FloatRect getAABB();

private:
	void handleInput(float deltaTime);
	void checkCollisions(float deltaTime, Level level);
	void updateState(float deltaTime);

	float speed = 100.0f;
	bool onGround;
	bool facingLeft;
	Animation* currentAnim;
	Animation idleAnim;
	Animation runningAnim;
	Animation JumpingAnim;

	State currentState;
};