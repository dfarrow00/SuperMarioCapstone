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

class Map
{
public:
	Map();
	~Map();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window, sf::View* view);

	void loadMap(int mapNumber);
	void updateTile(int x, int y, int tile);

	Level getCurrentLevel();

private:
	Level level;
	sf::Texture tileSheet;
	std::unordered_map<unsigned int, Tile*> tiles;
	
	unsigned int tileSize;
};