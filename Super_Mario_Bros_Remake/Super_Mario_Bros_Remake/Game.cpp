#include "Game.h"

Game::Game() : window(sf::VideoMode(768, 720), "Super Mario Bros Remake"), stateManager(&window)
{
	srand(time(nullptr));
	clock.restart();//Clocked used to calculate delta time

	window.setFramerateLimit(60);

	//Sets executable window icon to mario image.
	sf::Image icon;
	icon.loadFromFile("Resources/Sprites/Mario.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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
		//Enter and Esc keys used for menu functionality.
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				stateManager.escapePressed();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				stateManager.enterPressed();
			}
		}
	}
}

void Game::render()
{
	window.clear();
	stateManager.draw(&window);
	window.display();
}

sf::RenderWindow* Game::getWindow()
{
	return &window;
}