#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void update();
	void render();
	void handleInput();

	sf::RenderWindow* getWindow();

private:
	sf::Vector2f movement;
	sf::Clock timer;
	sf::Time deltaTime;
	sf::RenderWindow window;
	sf::Texture texture;
	sf::Sprite sprite;
};