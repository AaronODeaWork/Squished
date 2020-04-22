#include "Options.h"



Options::Options()
{

	slider();
	checkBox();
	loadContent();
}


Options::~Options()
{
}

void Options::loadContent()
{
	//Sets up the text on the screen 
	if (!m_font.loadFromFile("ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
}

void Options::update(XBOXController t_controller, sf::Time t_deltaTime)
{

	if (t_controller.m_currentState.Back == true)
	{

		m_returnMenu = true;
	}

	if (m_sliderBars.m_orderOfRectsOptions > 2)
	{
		m_sliderBars.m_orderOfRectsOptions = 0;

	}

	if (m_sliderBars.m_orderOfRectsOptions < 0)
	{
		m_sliderBars.m_orderOfRectsOptions = 2;

	}

	
		if (t_controller.m_currentState.LeftThumbStick.y <= -15 && ButtonTimer < 0) // moving down
		{
			m_sliderBars.m_orderOfRectsOptions -= 1;
			m_sliderBars.updateSliderOutline();
			ButtonTimer = 10;
		}
		if (t_controller.m_currentState.LeftThumbStick.y >= 15 && ButtonTimer < 0) // moving up
		{
			m_sliderBars.m_orderOfRectsOptions += 1;
			m_sliderBars.updateSliderOutline();
			
			ButtonTimer = 10;
		}

		ButtonTimer--;




	//MOVING SLIDERS
	//Music
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) - t_controller.dPadThreshold > 0)
	{
		if (t_controller.m_currentState.DpadRight = true && m_sliderBars.m_orderOfRectsOptions == 0)
		{

			if (m_sliderBars.m_musicBarLength <= 585)
			{
				m_sliderBars.m_musicBarLength += 6;
				m_sliderBars.updateSlider();

				m_sliderBars.changeMusicSliderColour();

			}
		}

	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) + t_controller.dPadThreshold < 0)
	{
		if (t_controller.m_currentState.DpadLeft = true && m_sliderBars.m_orderOfRectsOptions == 0)
		{
			if (m_sliderBars.m_musicBarLength > m_sliderBars.MIN_BAR)
			{


				if (m_sliderBars.m_musicBarLength > 1)
				{
					m_sliderBars.m_musicBarLength -= 6;
					m_sliderBars.updateSlider();
					m_sliderBars.changeMusicSliderColour();
				}
			}
		}
	}

	//Sound Effects Speed
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) - t_controller.dPadThreshold > 0)
	{
		if (t_controller.m_currentState.DpadRight = true && m_sliderBars.m_orderOfRectsOptions == 1)
		{

			if (m_sliderBars.m_speedBarLength <= 585)
			{
				m_sliderBars.m_speedBarLength += 6;
				m_sliderBars.updateSlider();
				m_sliderBars.changeEffectsColour();

			}
		}
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) + t_controller.dPadThreshold < 0)
	{
		if (t_controller.m_currentState.DpadLeft = true && m_sliderBars.m_orderOfRectsOptions == 1)
		{

			if (m_sliderBars.m_speedBarLength >= 0)
			{
				m_sliderBars.m_speedBarLength -= 6;
				m_sliderBars.updateSlider();
				m_sliderBars.changeEffectsColour();


			}
		}
	}

	//CHECKBOX
	if (m_sliderBars.m_orderOfRectsOptions == 2 && t_controller.m_currentState.A == true)
	{
		if (!t_controller.m_previousState.A == true)
		{
			if (m_cBox.m_musicOn )
			{
				m_cBox.musicIsOn();
			}
		}

	}

	if (m_sliderBars.m_orderOfRectsOptions == 2 && t_controller.m_currentState.A == true)
	{
		if (!t_controller.m_previousState.A == true)
		{
			if (m_cBox.m_musicOn == true )
			{
				m_cBox.musicIsOff();

			}
		}
	}


}

void Options::render(sf::RenderWindow & t_window)
{
	m_sliderBars.render(t_window);
	m_cBox.render(t_window);
}
