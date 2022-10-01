#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Map.h"
#include "Animation.h"

enum class MarioState
{
	Idle, Running_Right, Running_Left, Jumping, Grabbing_Flag
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
	void playLevelCompleteAnim();

	void addVelocity(sf::Vector2f vel);
	void setVelocityY(float value);
	void setBig(bool value);

	bool getInvinsible();
	bool getFinishReached();

private:
	void handleInput(float deltaTime);
	void checkCollisions(float deltaTime);
	void updateState(float deltaTime);
	void handleInvincibility(float deltaTime);

	void updateLevelCompleteAnim(float deltaTime);

	float jumpTime = 0.0f;
	float jumpVelocity = 450.0f;
	float speed = 800.0f;
	float drag = 400.0f;
	float gravity = 1600.0f;

	float invinsibilityTime = 2.0f;
	float currentInvTime = 0.0f;
	float flashingTimer = 0.0f;
	float flashingRate = 0.1f;
	float levelCompleteDelay = 1.0f;
	float currentLevelCompleteTime = 0.0f;

	bool onGround;
	bool facingLeft;
	bool isBig;
	bool invinsible;
	bool isVisible = true;
	bool playingLevelCompleteAnim = false;
	bool finishReached = false;

	Animation* currentAnim;

	Animation idleAnim;
	Animation runningAnim;
	Animation JumpingAnim;
	Animation flagGrabAnim;
	Animation deathAnim;

	Animation bigIdleAnim;
	Animation bigRunningAnim;
	Animation bigJumpingAnim;
	Animation bigFlagGrabAnim;

	MarioState currentState;

	Map* map;
};