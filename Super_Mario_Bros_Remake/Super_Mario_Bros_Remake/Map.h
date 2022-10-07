#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "GameObject.h"

struct Tile
{
	Tile(sf::Sprite spr) : sprite(spr)
	{
	}
	~Tile() {}

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
		sprite.setPosition(position);
	}

	sf::FloatRect getAABB()
	{
		return sprite.getGlobalBounds();
	}

	sf::Vector2f position;
	sf::Sprite sprite;
};

using Level = std::vector<std::vector<int>>;

class GameState;

class Map
{
public:
	Map(GameState* gameState);
	~Map();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window, sf::View* view);

	void loadMap(int mapNumber);
	void updateTile(int x, int y, int tile);

	bool isColliding(sf::Vector2f pos, sf::Vector2f velocity, bool isBig = false);

	Level getCurrentLevel();
	sf::Vector2f getFlagPolePos();

private:
	bool checkPoint(unsigned int tile, sf::Vector2f point, sf::Vector2f pos, bool isBig);

	GameState* game;

	Level level;
	sf::Texture tileSheet;
	std::unordered_map<unsigned int, Tile*> tiles;
	std::unordered_map<unsigned int, unsigned int> flagPoleScores;
	sf::Vector2f flagPolePos;

	unsigned int tileSize;
};