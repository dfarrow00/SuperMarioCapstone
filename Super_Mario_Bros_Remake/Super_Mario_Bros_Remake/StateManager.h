#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "State.h"
#include "MenuState.h"
#include "GameState.h"

enum class StateType
{
	Menu, Game, Paused
};

class StateManager
{
public:
	StateManager(sf::RenderWindow* window);
	~StateManager();

	void changeState(StateType state);

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

private:
	std::vector<std::pair<StateType, State*>> states;
};