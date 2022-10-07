#pragma once
#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "Mario.h"
#include "Map.h"

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
	std::vector<GameObject*> gameObjects;
};