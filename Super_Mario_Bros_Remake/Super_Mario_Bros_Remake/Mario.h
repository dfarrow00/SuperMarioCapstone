#pragma once
#include "GameObject.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class MarioState
{
	Idle, Running_Right, Running_Left, Jumping, Grabbing_Flag, Dead
};

class Mario : public GameObject
{
public:
	Mario();
	Mario(sf::Vector2f& pos);
	~Mario();

	void setup();
	void reset();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void hit();
	void powerUp();
	void starPowerUp();
	void playLevelCompleteAnim(sf::Vector2f flagPolePos);

	void addVelocity(sf::Vector2f vel);
	void setVelocityY(float value);
	void setBig(bool value);
	void resetLives();

	int getLives();
	float getStarPowerTime();
	bool getInvinsible();
	bool getFinishReached();
	bool getStarPower();
private:
	void loadSounds();

	void handleInput(float deltaTime);
	void checkCollisionStates(float deltaTime);
	void updateState(float deltaTime);
	void handleInvincibility(float deltaTime);

	void playDeathAnim();
	void playPowerUpAnim();
	void updatePowerUpAnim();
	void updateDeathAnim(float deltaTime);
	void updateLevelCompleteAnim(float deltaTime);
	void updateStarPower(const float deltaTime);

	int lives = 3;

	float jumpTime = 0.0f;
	float jumpVelocity = 400.0f;
	float speed = 800.0f;
	float drag = 400.0f;
	float furthestXPosition = 0.0f;

	float invinsibilityTime = 2.0f;
	float currentInvTime = 0.0f;
	float flashingTimer = 0.0f;
	float flashingRate = 0.1f;

	float levelCompleteDelay = 1.0f;
	float currentLevelCompleteTime = 0.0f;

	float deathAnimTime = 3.5f;
	float currentDeathAnimTime = 0.0f;

	float powerUpAnimTime = 1.0f;
	float powerUpAnimRate = 0.1f;
	sf::Clock powerUpAnimTimeClock;
	sf::Clock powerUpAnimRateClock;

	float starPowerTime = 7.0f;
	float currentStarPowerTime = 0.0f;
	float colorChangeTimer = 0.1f;
	float currentColorChangeTime = 0.0f;
	std::vector<sf::Color> starPowerColors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue };
	int currentColor = 0;

	bool isBig;
	bool invinsible;
	bool isVisible = true;
	bool playingLevelCompleteAnim = false;
	bool playingDeathAnim = false;
	bool playingPowerUpAnim = false;
	bool finishReached = false;
	bool starPower = false;

	Animation idleAnim;
	Animation runningAnim;
	Animation jumpingAnim;
	Animation flagGrabAnim;
	Animation deathAnim;

	Animation bigIdleAnim;
	Animation bigRunningAnim;
	Animation bigJumpingAnim;
	Animation bigFlagGrabAnim;

	MarioState currentState;

	sf::SoundBuffer jumpSoundBuffer;
	sf::Sound jumpSound;
	sf::SoundBuffer deathSoundBuffer;
	sf::Sound deathSound;
	sf::SoundBuffer flagSoundBuffer;
	sf::Sound flagSound;
	sf::SoundBuffer marioHitSoundBuffer;
	sf::Sound marioHitSound;
	sf::SoundBuffer marioPowerUpSoundBuffer;
	sf::Sound marioPowerUpSound;
	sf::SoundBuffer marioStarPowerSoundBuffer;
	sf::Sound marioStarPowerSound;
};