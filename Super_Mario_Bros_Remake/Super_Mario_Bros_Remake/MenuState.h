#pragma once
#include "StateManager.h"

class MenuState : public State
{
public:
	MenuState(StateManager* stateMgr);
	~MenuState();

	void activate();
	void deactivate();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

private:
	sf::Texture titleTexture;
	sf::Sprite titleSprite;
	sf::Text menuTitle;
	sf::Text menuText;
	sf::Font menuFont;
};