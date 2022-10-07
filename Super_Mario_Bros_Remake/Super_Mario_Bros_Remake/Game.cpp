#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(768, 720), "Super Mario Bros Remake"), stateManager(&window)
{
	srand(time(nullptr));
	clock.restart();

	//window.setFramerateLimit(30);

	view = window.getDefaultView();
	window.setView(view);
}

Game::~Game()
{
}

void Game::update()
{
	float deltaTime = clock.restart().asSeconds();
	//std::cout << 1 / deltaTime << std::endl;
	stateManager.update(deltaTime);

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void Game::render()
{
	window.clear(sf::Color::Cyan);
	stateManager.draw(&window);
	window.display();
}

sf::RenderWindow* Game::getWindow()
{
	return &window;
}