#include "MainMenu.h"

MainMenu::MainMenu()
{
	loadContent();
	m_menuB.updateOutlineMenu();
	menuButtons();
}


MainMenu::~MainMenu()
{
}

void MainMenu::loadContent()
{
	if (!m_menuMusic.openFromFile("Assets/sound/menuSong.wav"))
	{
		std::cout << "error menu music" << std::endl;
	}

	if (!m_backgroundTexture.loadFromFile("Assets/Images/main.png"))
	{
		std::cout << "main art error set up screen" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0, -350);

	if (!m_backgroundTextureTwo.loadFromFile("Assets/Images/mainTwo.png"))
	{
		std::cout << "main2 art error set up screen" << std::endl;
	}
	m_backgroundSpriteTwo.setTexture(m_backgroundTextureTwo);
	m_backgroundSpriteTwo.setPosition(0, -350);
	m_backgroundSpriteTwo.setColor(sf::Color(255, 255, 255, m_bgTransparent));
	

	if (!m_buttonBuffer.loadFromFile("Assets/sound/button.wav"))
	{
		std::cout << "error fight sound" << std::endl;
	}
	m_buttonClick.setBuffer(m_buttonBuffer);


	m_menuMusic.play();
}

void MainMenu::update(XBOXController t_controller, sf::Time t_deltaTime)
{

	if (m_bgTransparent >= 200)
	{
		m_bgflip = false;
	}
	else if (m_bgTransparent <= 50)
	{ 
		m_bgflip = true;
	}

	if (m_bgflip)
	{
		m_bgTransparent += 1;
	}
	else if (!m_bgflip)
	{
		m_bgTransparent -= 1;
	}
	m_backgroundSpriteTwo.setColor(sf::Color(255, 255, 255, m_bgTransparent));


	if (m_menuB.orderOfRect > 3)
	{
		m_menuB.orderOfRect = 0;
	}

	if (m_menuB.orderOfRect < 0)
	{
		m_menuB.orderOfRect = 3;
	}


		if (t_controller.m_currentState.LeftThumbStick.y <= -15 && ButtonTimer<0)
		{
			m_menuB.orderOfRect -= 1;
			ButtonTimer = 10;
		}

		if (t_controller.m_currentState.LeftThumbStick.y >= 15 && ButtonTimer<0)
		{
			m_menuB.orderOfRect += 1;
			ButtonTimer = 10;
		}
	
	
	ButtonTimer--;




	if (m_menuB.orderOfRect == 0)
	{
		if (t_controller.m_currentState.A)
		{
			if (!t_controller.m_previousState.A)
			{
				t_controller.m_currentState.A = true;
				setupS = true;
				
				m_buttonClick.play();
			}

		}

	}

	if (m_menuB.orderOfRect == 1)
	{
		if (t_controller.m_currentState.A)
		{
			if (!t_controller.m_previousState.A)
			{
				t_controller.m_currentState.A = true;
				optionsS = true;
				m_buttonClick.play();

			}

		}

	}

	if (m_menuB.orderOfRect == 2)
	{
		if (t_controller.m_currentState.A)
		{
			if (!t_controller.m_previousState.A)
			{
				t_controller.m_currentState.A = true;
				controlsS = true;
				m_buttonClick.play();
			}

		}

	}

	if (m_menuB.orderOfRect == 3)
	{
		if (t_controller.m_currentState.A)
		{
			if (!t_controller.m_previousState.A)
			{
				t_controller.m_currentState.A = true;
				exit = true;
				m_buttonClick.play();
			}

		}

	}

	m_menuB.updateOutlineMenu();
}

void MainMenu::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_backgroundSpriteTwo);
	t_window.draw(m_backgroundSprite);	


	m_menuB.render(t_window);
}

void MainMenu::startMusic()
{
	m_menuMusic.play();
}

void MainMenu::stopMusic()
{
	m_menuMusic.stop();
}
