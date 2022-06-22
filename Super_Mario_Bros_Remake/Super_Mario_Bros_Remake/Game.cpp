#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Super Mario Bros Remake")
{
	texture.loadFromFile("Resources/Mario.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.scale(2, 2);
	sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	srand(time(nullptr));
	deltaTime = timer.restart();
}

Game::~Game()
{
}

void Game::update()
{
	movement.x = movement.x * deltaTime.asSeconds();
	movement.y = movement.y * deltaTime.asSeconds();
	sprite.setPosition(sprite.getPosition() + movement);

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}

	deltaTime = timer.restart();
}

void Game::render()
{
	window.clear(sf::Color::Black);
	window.draw(sprite);
	window.display();
}

void Game::handleInput()
{
	movement = sf::Vector2f(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		movement.y -= 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		movement.y += 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movement.x -= 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movement.x += 100;
	}
}

sf::RenderWindow* Game::getWindow()
{
	return &window;
}