#include "MenuState.h"
#include <iostream>

MenuState::MenuState(StateManager* stateMgr) : State(stateMgr)
{
	isTransparent = true;
	titleTexture.loadFromFile("Resources/Sprites/SMB-Title.png");
	titleSprite.setTexture(titleTexture);
	titleSprite.setScale(0.75, 0.75);
	titleSprite.setOrigin(titleSprite.getLocalBounds().width / 2, titleSprite.getLocalBounds().height / 2);
	titleSprite.setPosition(384, 200);

	menuFont.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf");

	for (int x = 0; x < 2; x++)
	{
		menuItems[x].setFont(menuFont);
		menuItems[x].setOutlineColor(sf::Color::Black);
		menuItems[x].setOutlineThickness(2);
	}

	menuItems[0].setString("Play");
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
	selectionIcon.setPosition(menuItems[0].getPosition().x - 100, menuItems[0].getPosition().y);
}

MenuState::~MenuState()
{
}

void MenuState::activate()
{
	stateManager->setBackgroundColor(sf::Color::Cyan);
}

void MenuState::deactivate()
{
}

void MenuState::update(const float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveUp();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveDown();
	}
}

void MenuState::draw(sf::RenderWindow* window)
{
	window->draw(titleSprite);
	for (int x = 0; x < 2; x++)
	{
		window->draw(menuItems[x]);
	}
	window->draw(selectionIcon);
}

void MenuState::moveUp()
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

void MenuState::moveDown()
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

void MenuState::updateSelectionIcon()
{
	selectionIcon.setPosition(selectionIcon.getPosition().x, menuItems[selectedItem].getPosition().y);
}