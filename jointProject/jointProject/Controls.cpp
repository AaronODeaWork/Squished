#include "Controls.h"



Controls::Controls()
{
	loadContent();
}


void Controls::loadContent()
{
	//Sets up the text on the screen 
	if (!m_font.loadFromFile("ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}


	if (!m_backgroundTexture.loadFromFile("Assets/Images/control.png"))
	{
		std::cout << "background controls art error set up screen" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(1, .75);
}

void Controls::update(XBOXController t_controller, sf::Time t_deltaTime)
{
	if (t_controller.m_currentState.Back == true)
	{
		goBack = true;
	}
	t_controller.update();
}

void Controls::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_backgroundSprite);
}
