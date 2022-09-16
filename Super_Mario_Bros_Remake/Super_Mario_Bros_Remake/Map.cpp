#include "Map.h"
#include "GameState.h"
#include <iostream>

Map::Map(GameState* gameState) : game(gameState)
{
	tileSize = 48;

	tileSheet.loadFromFile("Resources/Tile_Sheet.png");
	int tileCount = 1;
	for (int y = 0; y < tileSize * 3; y += tileSize)
	{
		for (int x = 0; x < tileSize * 3; x += tileSize)
		{
			sf::Sprite sprite(tileSheet, sf::IntRect(x, y, tileSize, tileSize));
			Tile* tile = new Tile(sprite);
			tiles.emplace(tileCount, tile);
			tileCount++;
		}
	}
	loadMap(1);
}

Map::~Map()
{
	for (auto& itr : tiles)
	{
		delete itr.second;
	}
	tiles.clear();
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

	for (int y = 0; y < level.size(); y++)
	{
		for (int x = 0; x < level[y].size(); x++)
		{
			if ((x * tileSize) + tileSize < viewLeft || x * tileSize > viewRight)//If the tile is outside of the camera's view, dont draw it.
			{
				continue;
			}
			else if (level[y][x] == 0)
			{
				continue;
			}
			else
			{
				int tileNumber = level[y][x];
				tiles[tileNumber]->setPosition(x * tileSize, y * tileSize);
				window->draw(tiles[tileNumber]->sprite);
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
			number = 0;
		}
		level.push_back(row);
	}

	file.close();
}

void Map::updateTile(int x, int y, int tile)
{
	level[y][x] = tile;
}

bool Map::isColliding(sf::Vector2f pos, sf::Vector2f velocity)
{
	bool colliding = false;

	sf::Vector2f topLeft = pos + velocity;
	sf::Vector2f topRight = topLeft; topRight.x += tileSize;
	sf::Vector2f bottomLeft = topLeft; bottomLeft.y += tileSize;
	sf::Vector2f bottomRight = topRight; bottomRight.y += tileSize;

	unsigned int tile = level[topLeft.y / tileSize][topLeft.x / tileSize];
	if (tile > 0)
	{
		if (tile == 3 && pos.y > topLeft.y)
		{
			sf::Vector2f mushroomPos((int)(topLeft.x / tileSize) * tileSize, (int)(topLeft.y / tileSize) * tileSize - 1);
			game->addMushroom(sf::Vector2f(mushroomPos));
			updateTile(topLeft.x / tileSize, topLeft.y / tileSize, 8);
		}
		colliding = true;
	}

	tile = level[topRight.y / tileSize][topRight.x / tileSize];
	if (tile > 0)
	{
		if (tile == 3 && pos.y > topRight.y)
		{
			sf::Vector2f mushroomPos((int)(topRight.x / tileSize) * tileSize, (int)(topRight.y / tileSize) * tileSize - 1);
			game->addMushroom(sf::Vector2f(mushroomPos));
			updateTile(topRight.x / tileSize, topRight.y / tileSize, 8);
		}
		colliding = true;
	}

	tile = level[bottomLeft.y / tileSize][bottomLeft.x / tileSize];
	if (tile > 0)
	{
		colliding = true;
	}

	tile = level[bottomRight.y / tileSize][bottomRight.x / tileSize];
	if (tile > 0)
	{
		colliding = true;
	}

	return colliding;
}