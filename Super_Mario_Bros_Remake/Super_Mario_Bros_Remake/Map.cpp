#include "Map.h"
#include "GameState.h"
#include <iostream>

Map::Map(GameState* gameState) : game(gameState)
{
	tileSize = 48;
	tileSheet.loadFromFile("Resources/Tile_Sheet.png");
	int tileCount = 1;
	for (int y = 0; y < tileSize * 4; y += tileSize)
	{
		for (int x = 0; x < tileSize * 3; x += tileSize)
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
				if (tileNumber == 20)
				{
					tiles[3]->setPosition(x * tileSize, y * tileSize);
					window->draw(tiles[3]->sprite);
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
				row.push_back(number);
				number = 0;
			}
			level.push_back(row);
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
		}
	}
	file.close();
}

void Map::updateTile(int x, int y, int tile)
{
	level[y][x] = tile;
}

bool Map::isColliding(sf::Vector2f pos, sf::Vector2f velocity, bool isBig)
{
	bool colliding = false;
	std::vector<sf::Vector2f> points;

	sf::Vector2f topLeft = pos + velocity; points.push_back(topLeft);
	sf::Vector2f topRight = topLeft; topRight.x += tileSize; points.push_back(topRight);
	sf::Vector2f bottomLeft = topLeft; bottomLeft.y += tileSize; points.push_back(bottomLeft);
	sf::Vector2f bottomRight = topRight; bottomRight.y += tileSize; points.push_back(bottomRight);

	for (sf::Vector2f point : points)
	{
		if (point.y < 0)
		{
			continue;
		}
		unsigned int tile = level[point.y / tileSize][point.x / tileSize];
		if (checkPoint(tile, point, pos, isBig))
		{
			colliding = true;
		}
	}

	if (isBig)
	{
		sf::Vector2f bigBottomLeft = bottomLeft; bigBottomLeft.y += tileSize;
		sf::Vector2f bigBottomRight = bigBottomLeft; bigBottomRight.x += tileSize;

		if (bigBottomLeft.y > 0.0)
		{
			unsigned int tile = level[bigBottomLeft.y / tileSize][bigBottomLeft.x / tileSize];
			if (checkPoint(tile, bigBottomLeft, pos, isBig))
			{
				colliding = true;
			}
		}

		if (bigBottomRight.y > 0.0)
		{
			unsigned int tile = level[bigBottomRight.y / tileSize][bigBottomRight.x / tileSize];
			if (checkPoint(tile, bigBottomRight, pos, isBig))
			{
				colliding = true;
			}
		}
	}
	return colliding;
}

bool Map::checkPoint(unsigned int tile, sf::Vector2f point, sf::Vector2f pos, bool isBig)
{
	if (tile > 0)
	{
		if (tile == 3 && pos.y > point.y)
		{
			sf::Vector2f coinPos((int)(point.x / tileSize) * tileSize, (int)(point.y / tileSize) * tileSize - 1);
			game->addCoin(sf::Vector2f(coinPos));
			updateTile(point.x / tileSize, point.y / tileSize, 8);
		}

		else if (tile == 20 && pos.y > point.y)
		{
			sf::Vector2f mushroomPos((int)(point.x / tileSize) * tileSize, (int)(point.y / tileSize) * tileSize - 1);
			game->addMushroom(sf::Vector2f(mushroomPos));
			updateTile(point.x / tileSize, point.y / tileSize, 8);
		}
		else if (tile >= 95)
		{
			game->levelComplete(flagPoleScores[tile]);
		}
		else if (isBig && tile == 2 && pos.y > point.y)
		{
			updateTile(point.x / tileSize, point.y / tileSize, 0);
			game->addParticles(sf::Vector2f((int)(point.x / tileSize) * tileSize, ((int)point.y / tileSize) * tileSize));
		}
		return true;
	}
	return false;
}

sf::Vector2f Map::getFlagPolePos()
{
	return flagPolePos;
}