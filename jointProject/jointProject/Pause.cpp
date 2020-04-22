#include "Pause.h"



Pause::Pause()
{
	loadContent();
	pauseButtons();
	m_pauseB.updateOutlinePause();
}


Pause::~Pause()
{
}

void Pause::loadContent()
{
	
}

void Pause::update(XBOXController t_controller, sf::Time t_deltaTime)
{
	if (m_pauseB.m_pauseButtonOrder > 2)
	{
		m_pauseB.m_pauseButtonOrder = 0;
	}

	if (m_pauseB.m_pauseButtonOrder < 0)
	{
		m_pauseB.m_pauseButtonOrder = 2;
	}

	
		if (t_controller.m_currentState.LeftThumbStick.y <= -15 && ButtonTimer < 0)
		{
			m_pauseB.m_pauseButtonOrder -= 1;
			ButtonTimer = 10;
		}

		if (t_controller.m_currentState.LeftThumbStick.y >= 15 && ButtonTimer <0)
		{
			m_pauseB.m_pauseButtonOrder += 1;
			ButtonTimer = 10;
		}
	
	ButtonTimer--;


	if (m_pauseB.m_pauseButtonOrder == 0)
	{
		if (t_controller.m_currentState.A)
		{
			if (!t_controller.m_previousState.A)
			{
				//t_controller.m_currentState.A = false;
				m_resume = true;

			}

		}

	}

	if (m_pauseB.m_pauseButtonOrder == 1)
	{
		if (t_controller.m_currentState.A)
		{
			if (!t_controller.m_previousState.A)
			{
				m_restart = true;
			}

		}

	}

	if (m_pauseB.m_pauseButtonOrder == 2)
	{
		if (t_controller.m_currentState.A)
		{
			if (!t_controller.m_previousState.A)
			{
				//t_controller.m_currentState.A = true;
				m_moveToMain = true;
				m_pauseB.m_pauseButtonOrder = 0;
			}

		}

	}
	m_pauseB.updateOutlinePause();
}

void Pause::render(sf::RenderWindow & t_window)
{
	m_pauseB.render(t_window);
}
