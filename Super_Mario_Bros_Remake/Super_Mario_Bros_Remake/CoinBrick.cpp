#include "CoinBrick.h"
#include "GameState.h"

CoinBrick::CoinBrick(sf::Vector2f pos, GameState* gameState) : game(gameState)
{
	position = pos;
	texture.loadFromFile("Resources/Tile_Sheet.png", sf::IntRect(48, 0, 48, 48));
	sprite.setTexture(texture);
	sprite.setPosition(position);
	checkCollisions = false;
}

CoinBrick::~CoinBrick()
{
}

void CoinBrick::update(const float deltaTime)
{

}

void CoinBrick::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void CoinBrick::hit()
{
	if (!timerStarted)
	{
		clock.restart();
		timerStarted = true;
		game->addCoin(position);
		activated = true;
	}
	else if (clock.getElapsedTime().asSeconds() < 3.5)
	{
		game->addCoin(position);
	}
	else if (activated)
	{
		game->addCoin(position);
		texture.loadFromFile("Resources/Tile_Sheet.png", sf::IntRect(48, 96, 48, 48));
		sprite.setTexture(texture);
		activated = false;
	}
}