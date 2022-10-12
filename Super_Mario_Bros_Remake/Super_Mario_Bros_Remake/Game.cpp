#include "Game.h"

Game::Game() : window(sf::VideoMode(768, 720), "Super Mario Bros Remake"), stateManager(&window)
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