#include "GameOverState.h"
#include <iostream>

GameOverState::GameOverState(StateManager* stateMgr) : State(stateMgr)
{
	isTransparent = true;
	menuFont.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf");

	gameOverTitle.setFont(menuFont);
	gameOverTitle.setOutlineColor(sf::Color::Black);
	gameOverTitle.setOutlineThickness(2);
	gameOverTitle.setString("Game Over!");
	gameOverTitle.setOrigin(gameOverTitle.getLocalBounds().width / 2, gameOverTitle.getLocalBounds().height / 2);
	gameOverTitle.setPosition(384, 300);

	for (int x = 0; x < 2; x++)
	{
		menuItems[x].setFont(menuFont);
		menuItems[x].setOutlineColor(sf::Color::Black);
		menuItems[x].setOutlineThickness(2);
	}

	menuItems[0].setString("Restart");
	menuItems[0].setOrigin(menuItems[0].getLocalBounds().width / 2, menuItems[0].getLocalBounds().height / 2);
	menuItems[0].setPosition(384, 425);

	menuItems[1].setString("Exit");
	menuItems[1].setOrigin(menuItems[1].getLocalBounds().width / 2, menuItems[1].getLocalBounds().height / 2);
	menuItems[1].setPosition(384, 500);

	selectionIcon.setFont(menuFont);
	selectionIcon.setOutlineColor(sf::Color::Black);
	selectionIcon.setOutlineThickness(2);
	selectionIcon.setString(">");
	selectionIcon.setOrigin(selectionIcon.getLocalBounds().width / 2, selectionIcon.getLocalBounds().height / 2);
	selectionIcon.setPosition(menuItems[0].getPosition().x - 150, menuItems[0].getPosition().y);

	background.setSize(sf::Vector2f(768, 720));
	background.setPosition(0, 0);
	background.setFillColor(sf::Color(0, 0, 0, 150));
}

GameOverState::~GameOverState()
{
}

void GameOverState::activate()
{
}

void GameOverState::deactivate()
{
}

void GameOverState::update(const float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveUp();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveDown();
	}
}

void GameOverState::draw(sf::RenderWindow* window)
{
	window->setView(window->getDefaultView());
	window->draw(background);
	window->draw(gameOverTitle);
	for (int x = 0; x < 2; x++)
	{
		window->draw(menuItems[x]);
	}
	window->draw(selectionIcon);
}

void GameOverState::enterPressed()
{
	if (selectedItem == 0)
	{
		stateManager->changeState(StateType::Game);
	}
	else
	{
		exit(0);
	}
}

void GameOverState::moveUp()
{
	if (selectedItem == 0)
	{
		return;
	}
	else
	{
		selectedItem--;
	}
	updateSelectionIcon();
}

void GameOverState::moveDown()
{
	if (selectedItem == 1)
	{
		return;
	}
	else
	{
		selectedItem++;
	}
	updateSelectionIcon();
}

void GameOverState::updateSelectionIcon()
{
	selectionIcon.setPosition(selectionIcon.getPosition().x, menuItems[selectedItem].getPosition().y);
}