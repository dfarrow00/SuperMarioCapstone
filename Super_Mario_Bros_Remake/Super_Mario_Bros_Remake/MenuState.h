#pragma once
#include "StateManager.h"

class MenuState : public State
{
public:
	MenuState(StateManager* stateMgr);
	~MenuState();

	void activate();
	void deactivate();

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

private:
	void moveUp();
	void moveDown();
	void updateSelectionIcon();

	sf::RenderWindow* window;

	sf::Texture titleTexture;
	sf::Sprite titleSprite;

	sf::Font menuFont;

	sf::Text menuItems[2];
	sf::Text selectionIcon;
	int selectedItem = 0;
};