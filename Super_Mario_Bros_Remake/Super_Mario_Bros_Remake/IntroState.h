#pragma once
#include "StateManager.h"

class IntroState : public State
{	
public:
	IntroState(StateManager* stateMgr);
	~IntroState();

	void activate();
	void deactivate();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void close();

private:
	sf::Font introFont;
	sf::Text introTitle;
	sf::Text introName;

	float timePassed;
	float fadeInEndTime;
	float fadeOutStartTime;
	float fadeOutEndTime;
};