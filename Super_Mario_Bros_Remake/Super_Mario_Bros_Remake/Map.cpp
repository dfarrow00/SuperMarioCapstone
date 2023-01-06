#include "Map.h"
#include "GameState.h"
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map(GameState* gameState) : game(gameState)
{
	tileSize = 48;
	tileSheet.loadFromFile("Resources/Sprites/Tile_Sheet.png");
	int tileCount = 1;
	for (int y = 0; y < tileSize * 4; y += tileSize)
	{
		for (int x = 0; x < tileSize * 5; x += tileSize)
		{
			sf::Sprite sprite(tileSheet, sf::IntRect(x, y, tileSize, tileSize));
			Tile* tile = new Tile(sprite);
			tiles.emplace(tileCount, tile);
			tileCount++;
		}
	}

	flagPoleScores.emplace(95, 100);
	flagPoleScores.emplace(96, 400);
	flagPoleScores.emplace(97, 800);
	flagPoleScores.emplace(98, 2000);
	flagPoleScores.emplace(99, 4000);

	skyColors.emplace(0, sf::Color::Black);
	skyColors.emplace(1, sf::Color::Cyan);
}

Map::~Map()
{
	for (auto& itr : tiles)
	{
		delete itr.second;
	}
	tiles.clear();
}

void Map::update(const float deltaTime)
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
				if (tileNumber == 20)
				{
					tiles[3]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[3]->sprite);
				}
				else if (tileNumber == 30 || tileNumber == 32)
				{
					if (game->getLevelNumber() == 1)
					{
						tiles[2]->setPosition(x * tileSize, y * tileSize);
						window->draw(tiles[2]->sprite);
					}
					else
					{
						tiles[13]->setPosition(x * tileSize, y * tileSize);
						window->draw(tiles[13]->sprite);
					}
				}
				else if (tileNumber == 40)
				{
					tiles[6]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[6]->sprite);
				}
				else if (tileNumber == 41)
				{
					tiles[7]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[7]->sprite);
				}
				else if (tileNumber >= 95 && tileNumber <= 98)
				{
					tiles[10]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[10]->sprite);
				}
				else if (tileNumber == 99)
				{
					tiles[11]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[11]->sprite);
				}
				else
				{
					tiles[tileNumber]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[tileNumber]->sprite);
				}
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
	level.clear();
	std::ifstream file;
	std::string fileName("Resources/Maps/Level");
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
		if (isdigit(line.at(0)))
		{
			std::vector<int> row;
			std::stringstream stream(line);
			int number;
			for (int x = 0; x < line.length(); x++)
			{
				stream >> number;
				if (number == 99)
				{
					flagPolePos = sf::Vector2f(x * tileSize, level.size() + 1 * tileSize);
				}
				else if (number == 42)
				{
					pipeExitPos = sf::Vector2f(x * tileSize, level.size() * tileSize);
					number = 0;
				}
				else if (number == 31)
				{
					number = 0;
					game->addCoinBrick(sf::Vector2f(x * tileSize, level.size() * tileSize));
				}
				row.push_back(number);
				number = 0;
			}
			level.push_back(row);
		}
		else if (line.substr(0, line.find_first_of(' ')) == "Sky")
		{
			int skyNumber = line.at(4) - '0'; //Because all char encodings for digits are all in order from 48 to 57, the int value for any digit is itself - '0' (48 char code).
			game->setSkyColor(skyColors[skyNumber]);
		}
		else
		{
			std::string entity;
			float x;
			float y;
			std::stringstream stream(line);
			stream >> entity >> x >> y;

			if (entity == "Goomba")
			{
				game->addGoomba(sf::Vector2f(x, y));
			}
			else if (entity == "Koopa")
			{
				game->addKoopaTroopa(sf::Vector2f(x, y));
			}
			else if (entity == "Coin")
			{
				game->addCoinPickup(sf::Vector2f(x, y));
			}
			else if (entity == "Piranha")
			{
				game->addPiranhaPlant(sf::Vector2f(x, y));
			}
			else if (entity == "Spawn")
			{
				spawnPos = sf::Vector2f(x, y);
			}
		}
	}
	file.close();
}

void Map::updateTile(int x, int y, int tile)
{
	level[y][x] = tile;
}

int Map::getTile(int x, int y)
{
	return level[y / tileSize][x / tileSize];
}

sf::Vector2f Map::getSpawnPos()
{
	return spawnPos;
}

sf::Vector2f Map::getFlagPolePos()
{
	return flagPolePos;
}

sf::Vector2f Map::getPipeExitPos()
{
	return pipeExitPos;
}

int Map::getFlagPoleScore(int tile)
{
	return flagPoleScores[tile];
}