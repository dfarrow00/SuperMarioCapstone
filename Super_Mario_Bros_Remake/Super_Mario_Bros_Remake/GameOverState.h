#pragma once
#include "StateManager.h"

class GameOverState : public State
{
public:
	GameOverState(StateManager* stateMgr);
	~GameOverState();

	void activate();
	void deactivate();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void enterPressed();

private:
	void moveUp();
	void moveDown();
	void updateSelectionIcon();

	sf::RectangleShape background;

	sf::Font menuFont;

	sf::Text gameOverTitle;
	sf::Text menuItems[2];
	sf::Text selectionIcon;
	int selectedItem = 0;
};