#include "Map.h"
#include "GameState.h"
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map(GameState* gameState) : game(gameState)
{
	//Loading tile sprites from spritesheet.
	tileSize = 48;
	tileSheet.loadFromFile("Resources/Sprites/Tile_Sheet.png");
	int tileCount = 1;
	//For each row in the tile sheet
	for (int y = 0; y < tileSize * 4; y += tileSize)
	{
		//For each column in the tile sheet
		for (int x = 0; x < tileSize * 5; x += tileSize)
		{
			sf::Sprite sprite(tileSheet, sf::IntRect(x, y, tileSize, tileSize));
			Tile* tile = new Tile(sprite);
			tiles.emplace(tileCount, tile);
			tileCount++;
		}
	}

	//End level flagpole scores
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
			//If the tile is outside of the camera's view, don't draw it.
			if ((x * tileSize) + tileSize < viewLeft || x * tileSize > viewRight)
			{
				continue;
			}
			//If tile value at this co-ordinate is zero, no tile is needed to be drawn.
			else if (level[y][x] == 0)
			{
				continue;
			}
			else
			{
				int tileNumber = level[y][x];
				//If tile is a mushroom containing '?' block, draw the '?' block tile.
				if (tileNumber == 20)
				{
					tiles[3]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[3]->sprite);
				}
				//If tile is a star power or mushroom containing brick block, draw brick sprite. 
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
				//If tile is left pipe entrance, draw pipe top.
				else if (tileNumber == 40)
				{
					tiles[6]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[6]->sprite);
				}
				//If tile is right pipe entrance, draw pipe top.
				else if (tileNumber == 41)
				{
					tiles[7]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[7]->sprite);
				}
				//If tile is part of the flag pole, draw the flag pole pipe.
				else if (tileNumber >= 95 && tileNumber <= 98)
				{
					tiles[10]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[10]->sprite);
				}
				//If tile is the flag of the flagpole, draw the flag.
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
	//Load level text file.
	level.clear();
	std::ifstream file;
	std::string fileName("Resources/Maps/Level");
	fileName.append(std::to_string(mapNumber));
	fileName.append(".txt");
	file.open(fileName);

	if (!file.is_open())
	{
		std::cerr << "Failed to load map file!" << std::endl;
		return;
	}

	//For each line in the text file, process the data.
	std::string line;
	while (std::getline(file, line))
	{
		//If text file line is defining map geometry, store the digits in the 'level' vector.
		if (isdigit(line.at(0)))
		{
			std::vector<int> row;
			std::stringstream stream(line);
			int number;
			for (int x = 0; x < line.length(); x++)
			{
				stream >> number;
				//If flagpole number is read, store the 'x' coordinate.
				if (number == 99)
				{
					flagPolePos = sf::Vector2f(x * tileSize, level.size() + 1 * tileSize);
				}
				//If number read is pipe exit, store the pipe exit co-ordinates.
				else if (number == 42)
				{
					pipeExitPos = sf::Vector2f(x * tileSize, level.size() * tileSize);
					number = 0;
				}
				//If number read is coin brock block, add coin brick game object in corresponding location.
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
		//If text file line is defining the background, read the data and set the level background.
		else if (line.substr(0, line.find_first_of(' ')) == "Sky")
		{
			int skyNumber = line.at(4) - '0'; //Because all char encodings for digits are all in order from 48 to 57, the int value for any digit is itself - '0' (48 char code).
			game->setBackground(skyNumber);
		}
		//If line is defining a gameobject or entity, spawn the corresponding game object.
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
				game->addKoopaTroopa(sf::Vector2f(x, y), false);
			}
			else if (entity == "RedKoopa")
			{
				game->addKoopaTroopa(sf::Vector2f(x, y), true);
			}
			else if (entity == "Coin")
			{
				game->addCoinPickup(sf::Vector2f(x, y));
			}
			else if (entity == "Piranha")
			{
				game->addPiranhaPlant(sf::Vector2f(x, y));
			}
			else if (entity == "Platform")
			{
				int direction;
				stream >> direction;
				game->addPlatform(sf::Vector2f(x, y), direction);
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

int Map::getLevelWidth()
{
	return level[0].size();
}