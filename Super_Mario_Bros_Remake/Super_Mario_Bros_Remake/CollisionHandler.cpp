#include "CollisionHandler.h"
#include "Map.h"
#include "GameObject.h"
#include "Mario.h"
#include "KoopaTroopa.h"
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

void CollisionHandler::checkMapCollisions(std::vector<GameObject*>& gameObjects)
{
	for (GameObject* object : gameObjects)
	{
		if (!object->isActive() || !object->getCheckCollision())
		{
			continue;
		}
		std::vector<sf::Vector2f> points;
		int spriteHeight = object->getSpriteHeight();
		sf::Vector2f topLeft = object->getPosition() + sf::Vector2f(3, 0);
		sf::Vector2f topRight = topLeft + sf::Vector2f(TILESIZE - 3, 0);
		sf::Vector2f bottomLeft = topLeft + sf::Vector2f(0, spriteHeight);
		sf::Vector2f bottomRight = bottomLeft + sf::Vector2f(TILESIZE - 3, 0);
		points.push_back(topLeft);
		points.push_back(topRight);
		points.push_back(bottomLeft);
		points.push_back(bottomRight);

		if (spriteHeight >= 96)
		{
			sf::Vector2f middleLeft = topLeft + sf::Vector2f(0, spriteHeight / 2);
			sf::Vector2f middleRight = middleLeft + sf::Vector2f(TILESIZE - 3, 0);
			points.push_back(middleLeft);
			points.push_back(middleRight);
		}

		for (sf::Vector2f point : points)
		{
			if (point.y < 0)
			{
				continue;
			}
			else if (point.y >= 710)
			{
				object->hit();
				if (object->getObjectType() == ObjectType::Mario)
				{
					game->stopMusic();
				}
				break;
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
				if (col.object->getObjectType() == ObjectType::Mario)
				{
					game->levelComplete(map->getFlagPoleScore(col.tile), map->getFlagPolePos());
					break;
				}
			}
			float offsetX = (objAABB.left + (objAABB.width / 2)) - (col.tileAABB.left + (col.tileAABB.width / 2));
			float offsetY;
			if (col.object->getSpriteHeight() > 48)
			{
				//Not yet tested for KoopaTroopa's height
				if (objAABB.top < col.tileAABB.top)
				{
					offsetY = (objAABB.top + (objAABB.height / 2) + (objAABB.height / 4)) - (col.tileAABB.top + (col.tileAABB.height / 2));
				}
				else
				{
					offsetY = (objAABB.top + (objAABB.height / 2) - (objAABB.height / 4)) - (col.tileAABB.top + (col.tileAABB.height / 2));
				}
			}
			else
			{
				offsetY = (objAABB.top + (objAABB.height / 2)) - (col.tileAABB.top + (col.tileAABB.height / 2));
			}
			float resolve = 0;
			if (abs(offsetX) > abs(offsetY))
			{
				if (offsetX > 0)
				{
					resolve = ((col.tileAABB.left + col.tileAABB.width) - objAABB.left);
				}
				else
				{
					resolve = -((objAABB.left + objAABB.width) - col.tileAABB.left);
					if (col.object->getObjectType() == ObjectType::Mario)
					{
						if ((col.tile == 14 || col.tile == 15) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						{
							int currentLevel = game->getLevelNumber();
							if (currentLevel > 100 && currentLevel % 10 == 1)
							{
								int returnLevelNumber = currentLevel;
								while (returnLevelNumber >= 10)
								{
									returnLevelNumber /= 10;
								}
								game->enterPipe(returnLevelNumber, false);
							}
							else if (currentLevel > 100 && currentLevel % 10 > 1)
							{
								game->enterPipe(currentLevel - 1, false);
							}
							else
							{
								//NOTE Duplicated code from below.
								int levelToLoad = (game->getLevelNumber() * 100) + 1;
								game->enterPipe(levelToLoad, false);
							}
						}
					}
				}
				col.object->setPosition(col.object->getPosition().x + resolve, col.object->getPosition().y);
				col.object->setCollidingX(true);
			}
			else
			{
				if (offsetY > 0)
				{
					resolve = ((col.tileAABB.top + col.tileAABB.height) - objAABB.top);
					if (Mario* mario = dynamic_cast<Mario*>(col.object))
					{
						if (mario->getVelocity().y < 0)
						{
							if (col.tile == 3)
							{
								sf::Vector2f coinPos(col.tileAABB.left, col.tileAABB.top);
								game->addCoinEffect(coinPos);
								map->updateTile(col.tileAABB.left / TILESIZE, col.tileAABB.top / TILESIZE, 8);
							}
							else if (col.tile == 20 || col.tile == 32)
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
							else if ((col.tile == 2 || col.tile == 13) && mario->getSpriteHeight() > 48)
							{
								map->updateTile(col.tileAABB.left / TILESIZE, col.tileAABB.top / TILESIZE, 0);
								game->addParticles(sf::Vector2f(col.tileAABB.left, col.tileAABB.top));
							}
						}
					}
				}
				else
				{
					resolve = -((objAABB.top + objAABB.height) - col.tileAABB.top);
					col.object->setOnGround(true);
					if (col.object->getObjectType() == ObjectType::Mario)
					{
						if ((col.tile == 40 || col.tile == 41) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							if (game->getLevelNumber() < 100)
							{
								int levelToLoad = (game->getLevelNumber() * 100) + 1;
								game->enterPipe(levelToLoad, true);
							}
							else
							{
								game->enterPipe(game->getLevelNumber() + 1, true);
							}
						}
					}
					
				}
				col.object->setPosition(col.object->getPosition().x, col.object->getPosition().y + resolve);
				col.object->setCollidingY(true);
			}
		}
		collisions.clear();
	}
}
/*Code reference ends here*/

void CollisionHandler::resolveCollision(GameObject* obj1, GameObject* obj2, sf::FloatRect intersection)
{
	if (intersection.width > intersection.height)
	{
		if (obj2->getPosition().y > obj1->getPosition().y)
		{
			obj2->setPosition(obj2->getPosition().x, obj2->getPosition().y + intersection.height);
		}
		else
		{
			obj2->setPosition(obj2->getPosition().x, obj2->getPosition().y - intersection.height);
			obj2->setOnGround(true);
		}
		obj2->setCollidingY(true);
	}
	else
	{
		if (obj2->getPosition().x > obj1->getPosition().x)
		{
			obj2->setPosition(obj2->getPosition().x + intersection.width, obj2->getPosition().y);
		}
		else
		{
			obj2->setPosition(obj2->getPosition().x - intersection.width, obj2->getPosition().y);
		}
		obj2->setCollidingX(true);
	}
}

void CollisionHandler::checkObjectCollisions(std::vector<GameObject*>& gameObjects)
{
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); itr++)
	{
		GameObject* current = *itr;
		for (auto itr2 = itr + 1; itr2 != gameObjects.end(); itr2++)
		{
			GameObject* other = *itr2;
			sf::FloatRect intersection;
			if (current->isActive() && other->isActive() && current->getAABB().intersects(other->getAABB(), intersection))
			{
				if (Mario* marioObject = dynamic_cast<Mario*>(current))
				{
					if (marioObject->getStarPower())
					{
						if (other->getObjectType() == ObjectType::KoopaTroopa)
						{
							KoopaTroopa* koopaObject = dynamic_cast<KoopaTroopa*>(other);
							if (koopaObject->getCurrentState() == KoopaState::Walking)
							{
								other->hit();
							}
							else
							{
								koopaObject->kick(marioObject->getPosition().x < koopaObject->getPosition().x);
							}
						}
						other->hit();
						break;
					}
					if (other->getObjectType() == ObjectType::Mushroom)
					{
						other->hit();
						marioObject->powerUp();
						game->addScore(1000);
					}
					else if (other->getObjectType() == ObjectType::Goomba)
					{
						if (intersection.top == other->getAABB().top && intersection.width > intersection.height)
						{
							if (other->isActive())
							{
								marioObject->setVelocityY(-300);
								game->addScore(100);
							}
							other->hit();
						}
						else if (other->isActive() && !marioObject->getInvinsible())
						{
							if (marioObject->getSpriteHeight() == 48)
							{
								game->stopMusic();
							}
							marioObject->hit();
							game->getHUD()->setLives(marioObject->getLives());
						}
					}
					else if (KoopaTroopa* koopaObject = dynamic_cast<KoopaTroopa*>(other))
					{
						if (intersection.top == koopaObject->getAABB().top && intersection.width > intersection.height)
						{
							if (koopaObject->getCurrentState() == KoopaState::Walking)
							{
								marioObject->setVelocityY(-300);
								game->addScore(100);
								koopaObject->hit();
							}
							else
							{
								marioObject->setVelocityY(-200);
								koopaObject->kick(marioObject->getPosition().x < koopaObject->getPosition().x);
							}
						}
						else if (koopaObject->isActive() && !marioObject->getInvinsible())
						{
							if (koopaObject->getCurrentState() == KoopaState::Shell && koopaObject->getVelocity().x == 0)
							{
								koopaObject->kick(marioObject->getPosition().x < koopaObject->getPosition().x);
							}
							else
							{
								if (marioObject->getSpriteHeight() == 48)
								{
									game->stopMusic();
								}
								marioObject->hit();
								game->getHUD()->setLives(marioObject->getLives());
							}
						}
					}
					else if (other->getObjectType() == ObjectType::Star)
					{
						marioObject->starPowerUp();
						game->pauseMusic();
						game->getStarPowerTimer()->restart();
						other->hit();
						game->addScore(1000);
					}
					else if (other->getObjectType() == ObjectType::CoinBrick)
					{
						resolveCollision(other, marioObject, intersection);
						if (intersection.width > intersection.height && marioObject->getPosition().y > other->getPosition().y)
						{
							other->hit();
						}
					}
					else if (other->getObjectType() == ObjectType::CoinPickup)
					{
						other->hit();
						game->addCoins(1);
						game->addScore(100);
					}
					else if (other->getObjectType() == ObjectType::PiranhaPlant && !marioObject->getPlayingPipeAnim())
					{
						marioObject->hit();
						game->stopMusic();
					}
				}

				else if (current->getObjectType() == ObjectType::Goomba)
				{
					if (other->getObjectType() == ObjectType::Goomba)
					{
						if (current->isActive() && other->isActive())
						{
							current->setVelocity(-current->getVelocity());
							current->setFacingLeft(!current->getFacingLeft());
							other->setVelocity(-other->getVelocity());
							other->setFacingLeft(!other->getFacingLeft());
						}
					}
					else if (KoopaTroopa* koopaObject = dynamic_cast<KoopaTroopa*>(other))
					{
						if (current->isActive() && koopaObject->isActive())
						{
							if (koopaObject->getCurrentState() != KoopaState::Shell)
							{
								current->setVelocity(-current->getVelocity());
								current->setFacingLeft(!current->getFacingLeft());
								koopaObject->setVelocity(-koopaObject->getVelocity());
								koopaObject->setFacingLeft(!koopaObject->getFacingLeft());
							}
							else
							{
								current->hit();
								game->addScore(100);
							}
						}
					}
				}

				else if (KoopaTroopa* koopaObject = dynamic_cast<KoopaTroopa*>(current))
				{
					if (Enemy* enemyObject = dynamic_cast<Enemy*>(other))
					{
						if (koopaObject->isActive() && enemyObject->isActive())
						{
							if (koopaObject->getCurrentState() != KoopaState::Shell)
							{
								koopaObject->setVelocity(-koopaObject->getVelocity());
								koopaObject->setFacingLeft(!koopaObject->getFacingLeft());
								enemyObject->setVelocity(-enemyObject->getVelocity());
								enemyObject->setFacingLeft(!enemyObject->getFacingLeft());
							}
							else
							{
								enemyObject->hit();
								game->addScore(100);
							}
						}
					}
				}

				else if (current->getObjectType() == ObjectType::CoinBrick)
				{
					resolveCollision(current, other, intersection);
				}
			}
		}
	}
}