#include "CoinBrick.h"
#include "GameState.h"

CoinBrick::CoinBrick(sf::Vector2f pos, GameState* gameState) : game(gameState)
{
	objectType = ObjectType::CoinBrick;
	position = pos;
	//If overground, load regular sprite. Else, load blue sprite.
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
	//Coin block can only be hit for 3.5 seconds after first hit, then becomes inactive.
	if (!timerStarted)
	{
		clock.restart();
		timerStarted = true;
		game->addCoinEffect(position);
		activated = true;
	}
	else if (clock.getElapsedTime().asSeconds() < activeDuration)
	{
		game->addCoinEffect(position);
	}
	//After active duration has expired, change to inactive block sprite and deactivate.
	else if (activated)
	{
		game->addCoinEffect(position);
		texture.loadFromFile("Resources/Sprites/Tile_Sheet.png", sf::IntRect(96, 48, 48, 48));
		sprite.setTexture(texture);
		activated = false;
	}
}