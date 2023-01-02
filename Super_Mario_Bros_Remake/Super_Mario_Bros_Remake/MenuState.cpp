#include "MenuState.h"

MenuState::MenuState(StateManager* stateMgr) : State(stateMgr)
{
	isTransparent = true;
	titleTexture.loadFromFile("Resources/Sprites/SMB-Title.png");
	titleSprite.setTexture(titleTexture);
	titleSprite.setScale(0.75, 0.75);

	menuFont.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf");
	menuTitle.setFont(menuFont);
	menuText.setFont(menuFont);
	menuTitle.setString("Remake");
	menuText.setString("Press Enter to Start");
	menuTitle.setOutlineColor(sf::Color::Black);
	menuTitle.setOutlineThickness(2);
	menuText.setOutlineColor(sf::Color::Black);
	menuText.setOutlineThickness(2);

	titleSprite.setOrigin(titleSprite.getLocalBounds().width / 2, titleSprite.getLocalBounds().height / 2);
	menuTitle.setOrigin(menuTitle.getLocalBounds().width / 2, menuTitle.getLocalBounds().height / 2);
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	titleSprite.setPosition(384, 200);
	menuTitle.setPosition(384, 350);
	menuText.setPosition(384, 500);
}

MenuState::~MenuState()
{
}

void MenuState::activate()
{
}

void MenuState::deactivate()
{
}

void MenuState::update(const float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		stateManager->changeState(StateType::Game);
	}
}

void MenuState::draw(sf::RenderWindow* window)
{
	window->draw(titleSprite);
	window->draw(menuTitle);
	window->draw(menuText);
}