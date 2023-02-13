#include "PauseState.h"

PauseState::PauseState(StateManager* stateMgr) : State(stateMgr)
{
	isTransparent = true;
	pauseFont.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf");
	pauseText.setFont(pauseFont);
	pauseText.setOutlineColor(sf::Color::Black);
	pauseText.setOutlineThickness(2);
	pauseText.setString("PAUSED");
	pauseText.setOrigin(pauseText.getLocalBounds().width / 2, pauseText.getLocalBounds().height / 2);
	pauseText.setPosition(384, 360);

	background.setSize(sf::Vector2f(768, 720));
	background.setPosition(0, 0);
	background.setFillColor(sf::Color(0, 0, 0, 150));
}

PauseState::~PauseState()
{
}

void PauseState::activate()
{
	
}

void PauseState::deactivate()
{

}

void PauseState::update(const float deltaTime)
{
	
}

void PauseState::draw(sf::RenderWindow* window) 
{
	window->setView(window->getDefaultView());
	window->draw(background);
	window->draw(pauseText);
}