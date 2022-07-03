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

	bool colliding(sf::Vector2f currentPos);

	sf::FloatRect getAABB();

private:
	void handleInput(float deltaTime);
	void checkCollisions(float deltaTime);
	void updateState(float deltaTime);

	float speed = 100.0f;
	bool onGround;
	bool facingLeft;
	Animation* currentAnim;
	Animation idleAnim;
	Animation runningAnim;
	Animation JumpingAnim;

	MarioState currentState;

	Map* map;
};