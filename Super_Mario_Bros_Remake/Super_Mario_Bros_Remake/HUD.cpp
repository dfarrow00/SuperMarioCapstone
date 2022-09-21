#include "HUD.h"

HUD::HUD(sf::RenderWindow* window) : window(window)
{
	font.loadFromFile("Resources/PressStart2P-Regular.ttf");

	scoreLabelText.setString("SCORE");
	scoreValueText.setString(std::to_string(score));
	timeLabelText.setString("TIME");
	timeValueText.setString(std::to_string(time));
	worldLabelText.setString("WORLD");
	worldValueText.setString(std::to_string(level));
	coinsLabelText.setString("COINS");
	coinsValueText.setString(std::to_string(coins));
	livesLabelText.setString("LIVES");
	livesValueText.setString(std::to_string(lives));

	setupText(&scoreLabelText);
	setupText(&scoreValueText);
	setupText(&timeLabelText);
	setupText(&timeValueText);
	setupText(&worldLabelText);
	setupText(&worldValueText);
	setupText(&coinsLabelText);
	setupText(&coinsValueText);
	setupText(&livesLabelText);
	setupText(&livesValueText);
}

HUD::~HUD()
{
}

void HUD::update(int newTime)
{
	time = newTime;

	scoreValueText.setString(std::to_string(score));
	timeValueText.setString(std::to_string(time));

	scoreValueText.setOrigin(scoreValueText.getLocalBounds().width / 2, scoreValueText.getLocalBounds().height / 2);
	timeValueText.setOrigin(timeValueText.getLocalBounds().width / 2, timeValueText.getLocalBounds().height / 2);

	sf::Vector2f center = window->getView().getCenter();

	scoreLabelText.setPosition(center.x - 300, center.y - 340);
	scoreValueText.setPosition(center.x - 300, center.y - 310);

	coinsLabelText.setPosition(center.x - 150, center.y - 340);
	coinsValueText.setPosition(center.x - 150, center.y - 310);

	worldLabelText.setPosition(center.x, center.y - 340);
	worldValueText.setPosition(center.x, center.y - 310);

	timeLabelText.setPosition(center.x + 150, center.y - 340);
	timeValueText.setPosition(center.x + 150, center.y - 310);

	livesLabelText.setPosition(center.x + 300, center.y - 340);
	livesValueText.setPosition(center.x + 300, center.y - 310);
}

void HUD::draw(sf::RenderWindow* window)
{
	if (active)
	{
		window->draw(scoreLabelText);
		window->draw(scoreValueText);
		window->draw(timeLabelText);
		window->draw(timeValueText);
		window->draw(worldLabelText);
		window->draw(worldValueText);
		window->draw(coinsLabelText);
		window->draw(coinsValueText);
		window->draw(livesLabelText);
		window->draw(livesValueText);
	}
}

void HUD::activate()
{
	active = true;
}

void HUD::deactivate()
{
	active = false;
}

void HUD::setLevel(int levelNumber)
{
	level = levelNumber;
	worldValueText.setString(std::to_string(level));
}

void HUD::setupText(sf::Text* text)
{
	text->setFont(font);
	text->setCharacterSize(24);
	text->setFillColor(sf::Color::White);
	text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
}

void HUD::setCoins(int newCoins)
{
	coins = newCoins;
	coinsValueText.setString(std::to_string(coins));
}

void HUD::setLives(int newLives)
{
	lives = newLives;
	livesValueText.setString(std::to_string(lives));
}

void HUD::setScore(int newScore)
{
	score = newScore;
	scoreValueText.setString(std::to_string(score));
}