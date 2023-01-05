#include "CoinBrick.h"
#include "GameState.h"

CoinBrick::CoinBrick(sf::Vector2f pos, GameState* gameState) : game(gameState)
{
	objectType = ObjectType::CoinBrick;
	position = pos;
	if (game->getLevelNumber() == 1)
	{
		texture.loadFromFile("Resources/Sprites/Tile_Sheet.png", sf::IntRect(48, 0, 48, 48));
	}
	else
	{
		texture.loadFromFile("Resources/Sprites/Tile_Sheet.png", sf::IntRect(96, 96, 48, 48));
	}
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
		game->addCoinEffect(position);
		activated = true;
	}
	else if (clock.getElapsedTime().asSeconds() < 3.5)
	{
		game->addCoinEffect(position);
	}
	else if (activated)
	{
		game->addCoinEffect(position);
		texture.loadFromFile("Resources/Sprites/Tile_Sheet.png", sf::IntRect(96, 48, 48, 48));
		sprite.setTexture(texture);
		activated = false;
	}
}