#include "Map.h"
#include <iostream>

Map::Map()
{
	tileSize = 48;
	sf::Texture texture;
	texture.loadFromFile("Resources/Floor.png");
	Tile* tile = new Tile(texture);
	tiles.emplace(1, tile);

	texture.loadFromFile("Resources/Brick.png");
	Tile* tile2 = new Tile(texture);
	tiles.emplace(2, tile2);

	loadMap(1);
}

Map::~Map()
{
	for (auto& itr : tiles)
	{
		delete itr.second;
	}
}

void Map::update(float deltaTime)
{

}

void Map::draw(sf::RenderWindow* window)
{
	for (int x = 0; x < level.size(); x++)
	{
		for (int y = 0; y < level[x].size(); y++)
		{
			if (level[x][y] == 1)
			{
				tiles[1]->setPosition(y * tileSize, x * tileSize);
				window->draw(tiles[1]->sprite);
			}

			if (level[x][y] == 2)
			{
				tiles[2]->setPosition(y * tileSize, x * tileSize);
				window->draw(tiles[2]->sprite);
			}
		}
	}
}

std::vector<std::vector<int>> Map::getCurrentLevel()
{
	return level;
}

void Map::loadMap(int mapNumber)
{
	std::ifstream file;
	std::string fileName("Resources/Level");
	fileName.append(std::to_string(mapNumber));
	fileName.append(".txt");
	std::cout << fileName << std::endl;
	file.open(fileName);

	if (!file.is_open())
	{
		std::cout << "Failed to load map file!" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::vector<int> row;
		std::stringstream stream(line);
		int number;
		for (int x = 0; x < line.length(); x++)
		{
			stream >> number;
			row.push_back(number);
		}

		level.push_back(row);
	}

	file.close();

}