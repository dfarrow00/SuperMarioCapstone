#include "IntroState.h"
#include <iostream>

IntroState::IntroState(StateManager* stateMgr) : State(stateMgr)
{
	timePassed = 0.0f;
	fadeInEndTime = 1.0f;
	fadeOutStartTime = 1.5f;
	fadeOutEndTime = 2.5f;

	introFont.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf");

	introTitle.setFont(introFont);
	introTitle.setString("Remake by");
	introTitle.setOrigin(introTitle.getLocalBounds().width / 2, introTitle.getLocalBounds().height / 2);
	introTitle.setPosition(384, 280);

	introName.setFont(introFont);
	introName.setCharacterSize(35);
	introName.setString("Dominic Farrow");
	introName.setOrigin(introName.getLocalBounds().width / 2, introName.getLocalBounds().height / 2);
	introName.setPosition(384, 350);
}

IntroState::~IntroState()
{
}

void IntroState::activate()
{
	timePassed = 0.0f;
}

void IntroState::deactivate()
{
}

void IntroState::update(const float deltaTime)
{
	//Fade in and Fade out animations
	timePassed += deltaTime;
	if (timePassed <= fadeInEndTime)
	{
		introTitle.setFillColor(sf::Color(255, 255, 255, 255 * (timePassed / fadeInEndTime)));
		introName.setFillColor(sf::Color(255, 255, 255, 255 * (timePassed / fadeInEndTime)));
	}
	else if (timePassed > fadeOutStartTime)
	{
		introTitle.setFillColor(sf::Color(255, 255, 255, 255 * (fadeOutEndTime - timePassed)));
		introName.setFillColor(sf::Color(255, 255, 255, 255 * (fadeOutEndTime - timePassed)));
	}

	if (timePassed >= fadeOutEndTime)
	{
		close();
	}
}

void IntroState::draw(sf::RenderWindow* window)
{
	window->draw(introTitle);
	window->draw(introName);
}

void IntroState::close()
{
	stateManager->changeState(StateType::Menu);
	stateManager->deleteState(StateType::Intro);
}