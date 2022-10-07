#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
public:
	HUD(sf::RenderWindow* window);
	~HUD();

	void activate();
	void deactivate();

	void update(int newTime);
	void draw(sf::RenderWindow* window);

	void setLevel(int levelNumber);
	void setCoins(int newCoins);
	void setLives(int lives);
	void setScore(int newScore);

private:
	void setupText(sf::Text* text);

	int score = 0;
	int level = 1;
	int time = 400;
	int coins = 0;
	int lives = 3;
	bool active = false;

	sf::Font font;

	sf::Text scoreLabelText;
	sf::Text scoreValueText;

	sf::Text timeLabelText;
	sf::Text timeValueText;

	sf::Text worldLabelText;
	sf::Text worldValueText;

	sf::Text coinsLabelText;
	sf::Text coinsValueText;

	sf::Text livesLabelText;
	sf::Text livesValueText;

	sf::RenderWindow* window;
};