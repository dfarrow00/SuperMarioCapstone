#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(768, 720), "Super Mario Bros Remake")
{
	srand(time(nullptr));
	clock.restart();

	//window.setFramerateLimit(60);

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
	mario.update(deltaTime, map.getCurrentLevel());

	if (mario.getPosition().x > view.getCenter().x)//Camera only follows mario when moving fowards, stays still when mario is moving backwards.
	{
		view.setCenter(mario.getPosition().x, window.getDefaultView().getCenter().y);
		window.setView(view);
	}

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
	map.draw(&window, &view);
	mario.draw(&window);
	window.display();
}

sf::RenderWindow* Game::getWindow()
{
	return &window;
}