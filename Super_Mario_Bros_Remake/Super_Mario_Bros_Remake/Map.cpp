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

	texture.loadFromFile("Resources/Q.png");
	Tile* tile3 = new Tile(texture);
	tiles.emplace(3, tile3);

	texture.loadFromFile("Resources/Left_Pipe.png");
	Tile* tile4 = new Tile(texture);
	tiles.emplace(4, tile4);

	texture.loadFromFile("Resources/Right_Pipe.png");
	Tile* tile5 = new Tile(texture);
	tiles.emplace(5, tile5);

	texture.loadFromFile("Resources/Top_Left_Pipe.png");
	Tile* tile6 = new Tile(texture);
	tiles.emplace(6, tile6);

	texture.loadFromFile("Resources/Top_Right_Pipe.png");
	Tile* tile7 = new Tile(texture);
	tiles.emplace(7, tile7);

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

void Map::draw(sf::RenderWindow* window, sf::View* view)
{
	float viewWidth = view->getSize().x;
	float viewHeight = view->getSize().y;
	float viewLeft = view->getCenter().x - (viewWidth / 2);
	float viewRight = viewLeft + viewWidth;

	for (int x = 0; x < level.size(); x++)
	{
		for (int y = 0; y < level[x].size(); y++)
		{
			if ((y * tileSize) + tileSize < viewLeft || y * tileSize > viewRight)//If the tile is outside of the camera's view, dont draw it.
			{
				continue;
			}
			else if (level[x][y] == 1)
			{
				tiles[1]->setPosition(y * tileSize, x * tileSize);
				window->draw(tiles[1]->sprite);
			}

			else if (level[x][y] == 2)
			{
				tiles[2]->setPosition(y * tileSize, x * tileSize);
				window->draw(tiles[2]->sprite);
			}

			else if (level[x][y] == 3)
			{
				tiles[3]->setPosition(y * tileSize, x * tileSize);
				window->draw(tiles[3]->sprite);
			}

			else if (level[x][y] == 4)
			{
				tiles[4]->setPosition(y * tileSize, x * tileSize);
				window->draw(tiles[4]->sprite);
			}

			else if (level[x][y] == 5)
			{
				tiles[5]->setPosition(y * tileSize, x * tileSize);
				window->draw(tiles[5]->sprite);
			}

			else if (level[x][y] == 6)
			{
				tiles[6]->setPosition(y * tileSize, x * tileSize);
				window->draw(tiles[6]->sprite);
			}

			else if (level[x][y] == 7)
			{
				tiles[7]->setPosition(y * tileSize, x * tileSize);
				window->draw(tiles[7]->sprite);
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