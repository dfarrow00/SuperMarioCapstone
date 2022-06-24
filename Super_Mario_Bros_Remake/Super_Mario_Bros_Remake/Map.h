#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameObject.h"

struct Tile
{
	Tile(sf::Texture tex) : texture(tex)
	{
		sprite.setTexture(texture);
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
	sf::Texture texture;
	sf::Sprite sprite;
};

using Level = std::vector<std::vector<int>>;

class Map
{
public:
	Map();
	~Map();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	Level getCurrentLevel();

private:
	Level level;
	std::unordered_map<unsigned int, Tile*> tiles;
	
	unsigned int tileSize;
};