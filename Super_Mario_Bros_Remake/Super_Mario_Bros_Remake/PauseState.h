#pragma once
#include "StateManager.h"

class PauseState : public State
{
public:
	PauseState(StateManager* stateMgr);
	~PauseState();

	void activate();
	void deactivate();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

private:
	sf::RenderWindow* window;

	sf::RectangleShape background;
	sf::Font pauseFont;
	sf::Text pauseText;
};