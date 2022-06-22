#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameObject.h"

struct Tile
{
	Tile(sf::Texture tex) : texture(tex)
	{
		sprite.setTexture(texture);
		sprite.setScale(3, 3);
	}
	~Tile() {}

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
		sprite.setPosition(position);
	}

	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;
};

class Map
{
public:
	Map();
	~Map();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	std::vector<Tile>* getCurrentLevel();

private:
	std::vector<std::vector<unsigned int>> level;
	std::unordered_map<unsigned int, Tile*> tiles;
	
	std::vector<Tile> currentLevel;
	unsigned int tileSize;
};