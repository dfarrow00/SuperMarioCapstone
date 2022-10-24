#include "CollisionHandler.h"
#include "Map.h"
#include "GameObject.h"
#include "Mario.h"
#include "GameState.h"

bool sortCollisions(const Collision& col1, const Collision& col2)
{
	return col1.area > col2.area;
}

CollisionHandler::CollisionHandler(Map* gameMap, GameState* gameState) : map(gameMap), game(gameState)
{
	
}

CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::checkCollisions(std::vector<GameObject*>& gameObjects)
{
	for (GameObject* object : gameObjects)
	{
		if (!object->isActive() || !object->getCheckCollision())
		{
			continue;
		}
		std::vector<sf::Vector2f> points;
		int spriteHeight = object->getSprite().getGlobalBounds().height;
		sf::Vector2f topLeft = object->getPosition();
		sf::Vector2f topRight = topLeft + sf::Vector2f(TILESIZE, 0);
		sf::Vector2f bottomLeft = topLeft + sf::Vector2f(0, spriteHeight);
		sf::Vector2f bottomRight = bottomLeft + sf::Vector2f(TILESIZE, 0);
		points.push_back(topLeft);
		points.push_back(topRight);
		points.push_back(bottomLeft);
		points.push_back(bottomRight);

		if (spriteHeight >= 96)
		{
			sf::Vector2f middleLeft = topLeft + sf::Vector2f(0, spriteHeight / 2);
			sf::Vector2f middleRight = middleLeft + sf::Vector2f(TILESIZE, 0);
			points.push_back(middleLeft);
			points.push_back(middleRight);
		}

		for (sf::Vector2f point : points)
		{
			if (point.y < 0)
			{
				continue;
			}
			unsigned int tile = map->getTile(point.x, point.y);
			if (tile == 0)
			{
				continue;
			}
			/*R.Pupius, SFML game development by example : Create and develop exciting games from start to finish using SFML.Birmingham, UK : Packt Publishing, 2015.
			* Code Starts here */
			sf::FloatRect tileAABB(floor(point.x / TILESIZE) * TILESIZE, floor(point.y / TILESIZE) * TILESIZE, TILESIZE, TILESIZE);
			sf::FloatRect intersection;
			object->getAABB().intersects(tileAABB, intersection);
			float area = intersection.width * intersection.height;
			Collision newCollision(object, area, tile, tileAABB);
			collisions.emplace_back(newCollision);
			/*Code reference ends here*/
		}
	}
	resolveCollisions();
}

/*R.Pupius, SFML game development by example : Create and develop exciting games from start to finish using SFML.Birmingham, UK : Packt Publishing, 2015.
* Code Starts here */
void CollisionHandler::resolveCollisions()
{
	if (!collisions.empty())
	{
		std::sort(collisions.begin(), collisions.end(), sortCollisions);
		for (Collision& col : collisions)
		{
			sf::FloatRect objAABB = col.object->getAABB();
			if (!objAABB.intersects(col.tileAABB))
			{
				continue;
			}
			if (col.tile >= 95)
			{
				if (Mario* mario = dynamic_cast<Mario*>(col.object))
				{
					game->levelComplete(map->getFlagPoleScore(col.tile), map->getFlagPolePos());
				}
			}
			float offsetX = (objAABB.left + (objAABB.width / 2)) - (col.tileAABB.left + (col.tileAABB.width / 2));
			float offsetY = (objAABB.top + (objAABB.height / 2)) - (col.tileAABB.top + (col.tileAABB.height / 2));
			float resolve = 0;
			if (abs(offsetX) > abs(offsetY))
			{
				if (offsetX > 0)
				{
					resolve = ((col.tileAABB.left + TILESIZE) - objAABB.left);
				}
				else
				{
					resolve = -((objAABB.left + objAABB.width) - col.tileAABB.left);
				}
				col.object->setPosition(col.object->getPosition().x + resolve, col.object->getPosition().y);
				col.object->setCollidingX(true);
			}
			else
			{
				if (offsetY > 0)
				{
					resolve = ((col.tileAABB.top + TILESIZE) - objAABB.top);
					if (Mario* mario = dynamic_cast<Mario*>(col.object))
					{
						if (col.tile == 3)
						{
							sf::Vector2f coinPos(col.tileAABB.left, col.tileAABB.top);
							game->addCoin(coinPos);
							map->updateTile(col.tileAABB.left / TILESIZE, col.tileAABB.top / TILESIZE, 8);
						}
						else if (col.tile == 20)
						{
							sf::Vector2f mushroomPos(col.tileAABB.left, col.tileAABB.top);
							game->addMushroom(mushroomPos);
							map->updateTile(col.tileAABB.left / TILESIZE, col.tileAABB.top / TILESIZE, 8);
						}
						else if (col.tile == 30)
						{
							sf::Vector2f starPos(col.tileAABB.left, col.tileAABB.top);
							game->addStar(starPos);
							map->updateTile(col.tileAABB.left / TILESIZE, col.tileAABB.top / TILESIZE, 8);
						}
						else if (col.tile == 2 && mario->getSpriteHeight() > 48)
						{
							map->updateTile(col.tileAABB.left / TILESIZE, col.tileAABB.top / TILESIZE, 0);
							game->addParticles(sf::Vector2f(col.tileAABB.left, col.tileAABB.top));
						}
					}
				}
				else
				{
					resolve = -((objAABB.top + objAABB.height) - col.tileAABB.top);
					col.object->setOnGround(true);
				}
				col.object->setPosition(col.object->getPosition().x, col.object->getPosition().y + resolve);
				col.object->setCollidingY(true);
			}
		}
		collisions.clear();
	}
}
/*Code reference ends here*/