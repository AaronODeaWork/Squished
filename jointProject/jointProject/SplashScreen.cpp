#include "SplashScreen.h"

SplashScreen::SplashScreen()
{

	loadContent();
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::loadContent()
{

	if (!m_backgroundTexture.loadFromFile("Assets/Images/splash.png"))
	{
		std::cout << "author art error set up screen" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(1, .7);
}

void SplashScreen::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_backgroundSprite);
}



void SplashScreen::update(XBOXController t_controller, sf::Time t_deltaTime)
{

	if (t_controller.m_currentState.A)
	{
		m_APressed = true;

	}



}