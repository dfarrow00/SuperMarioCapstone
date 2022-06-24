#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(768, 720), "Super Mario Bros Remake")
{
	srand(time(nullptr));
	clock.restart();

	view = window.getDefaultView();
	window.setView(view);
}

Game::~Game()
{
}

void Game::update()
{
	float deltaTime = clock.restart().asSeconds();
	mario.update(deltaTime, map.getCurrentLevel());

	view.setCenter(mario.getPosition().x, window.getDefaultView().getCenter().y);
	window.setView(view);


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
	map.draw(&window);
	mario.draw(&window);
	window.display();
}

sf::RenderWindow* Game::getWindow()
{
	return &window;
}