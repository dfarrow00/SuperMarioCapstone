#pragma once
#include <SFML/Graphics.hpp>
#include "StateManager.h"

class Game
{
public:
	Game();
	~Game();

	void update();
	void render();

	sf::RenderWindow* getWindow();

private:
	sf::Clock clock;
	sf::RenderWindow window;
	sf::View view;

	StateManager stateManager;
};