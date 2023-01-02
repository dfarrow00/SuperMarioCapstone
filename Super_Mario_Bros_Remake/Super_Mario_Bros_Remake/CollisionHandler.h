#pragma once
#include <SFML/Graphics.hpp>

class GameObject;
class Map;
class GameState;

/*R.Pupius, SFML game development by example : Create and develop exciting games from start to finish using SFML.Birmingham, UK : Packt Publishing, 2015.
* Code Starts here */
struct Collision
{
	Collision(GameObject* gameObject, float colArea, int colTile, sf::FloatRect colTileAABB) : object(gameObject), area(colArea), tile(colTile), tileAABB(colTileAABB)
	{
	}

	GameObject* object;
	float area;
	int tile;
	sf::FloatRect tileAABB;
};
/*End of reference code*/

bool sortCollisions(const Collision& col1, const Collision& col2);

class CollisionHandler
{
public:
	CollisionHandler(Map* gameMap, GameState* gameState);
	~CollisionHandler();

	void checkMapCollisions(std::vector<GameObject*>& gameObjects);
	void resolveCollision(GameObject* obj1, GameObject* obj2, sf::FloatRect intersection);
	void checkObjectCollisions(std::vector<GameObject*>& gameObjects);
	
private:
	void resolveCollisions();
	std::vector<Collision> collisions;

	Map* map;
	GameState* game;
	const int TILESIZE = 48;
};