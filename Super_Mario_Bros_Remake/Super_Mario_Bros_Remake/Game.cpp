#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Super Mario Bros Remake")
{
	srand(time(nullptr));
	clock.restart();
}

Game::~Game()
{
}

void Game::update()
{
	float deltaTime = clock.getElapsedTime().asSeconds();

	mario.update(deltaTime, map.getCurrentLevel());

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
	clock.restart();
}

void Game::render()
{
	window.clear(sf::Color::Cyan);
	map.draw(&window);
	mario.draw(&window);
	window.display();
}

sf::RenderWindow* Game::getWindow()
{
	return &window;
}