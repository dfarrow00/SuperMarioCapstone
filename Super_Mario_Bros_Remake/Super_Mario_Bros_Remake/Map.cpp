#include "Map.h"

Map::Map()
{
	tileSize = 48;
	sf::Texture texture;
	texture.loadFromFile("Resources/Floor.png");
	Tile* tile = new Tile(texture);
	tiles.emplace(0, tile);

	texture.loadFromFile("Resources/Brick.png");
	Tile* tile2 = new Tile(texture);
	tiles.emplace(1, tile2);


	Level testLevel = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
												{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
	level = testLevel;

	for (int x = 0; x < level.size(); x++)
	{
		for (int y = 0; y < level[x].size(); y++)
		{
			if (level[y][x] > 2)
			{
				continue;
			}
			else if (level[y][x] == 0)
			{
				tiles[0]->setPosition((x * tileSize * 3), (y * tileSize * 3));
				Tile block = *tiles[0];
			}
			else if (level[y][x] == 1)
			{
				tiles[1]->setPosition((x * tileSize), (y * tileSize));
				Tile block = *tiles[0];
			}
		}
	}
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
			if (level[y][x] == 0)
			{
				tiles[0]->setPosition(x * tileSize, y * tileSize);
				window->draw(tiles[0]->sprite);
			}
		}
	}
}

std::vector<std::vector<int>> Map::getCurrentLevel()
{
	return level;
}