#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "State.h"

enum class StateType
{
	Intro, Menu, Game, Paused
};

class StateManager
{
public:
	StateManager(sf::RenderWindow* window);
	~StateManager();

	void changeState(StateType state);
	void deleteState(StateType state);

	void update(const float deltaTime);
	void draw(sf::RenderWindow* window);

	void setBackgroundColor(sf::Color color);
	sf::Color getSkyColor();

private:
	std::vector<std::pair<StateType, State*>> states;
	sf::Color skyColor;
};