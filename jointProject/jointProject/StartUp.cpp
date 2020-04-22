#include "StartUp.h"

StartUp::StartUp()
{
	loadContent();


}

void StartUp::loadContent()
{

	if (!m_buttonBuffer.loadFromFile("Assets/sound/button.wav"))
	{
		std::cout << "error fight sound" << std::endl;
	}
	m_buttonClick.setBuffer(m_buttonBuffer);


	m_screenColours[0] = sf::Color(255, 0, 0,200);
	m_screenColours[1] = sf::Color(255, 127, 0, 200);
	m_screenColours[2] = sf::Color(255, 255, 0, 200);
	m_screenColours[3] = sf::Color(0, 255, 0, 200);
	m_screenColours[4] = sf::Color(0, 0, 255, 200);
	m_screenColours[5] = sf::Color(75, 0, 130, 200);


	if (!m_playerTexture.loadFromFile("Assets/Images/cube.png"))
	{
		std::cout << "player art error set up screen" << std::endl;
	}

	for (int i = 0; i < 4; i++)
	{
		m_playerSprite[i].setTexture(m_playerTexture);
		m_playerSprite[i].setScale(.5, .5);
		m_playerSprite[i].setOrigin(m_playerTexture.getSize().x / 2, m_playerTexture.getSize().y / 2);
	}
	m_playerSprite[0].setColor(sf::Color(255, 255, 255, 200));
	m_playerSprite[1].setColor(sf::Color(255, 0, 0, 200));
	m_playerSprite[2].setColor(sf::Color(200, 0, 255, 200));
	m_playerSprite[3].setColor(sf::Color(255, 200, 0, 200));

	m_playerSprite[0].setPosition(sf::Vector2f( screen.s_width*.2, screen.s_height*.5));
	m_playerSprite[1].setPosition(sf::Vector2f( screen.s_width*.4, screen.s_height*.5));
	m_playerSprite[2].setPosition(sf::Vector2f( screen.s_width*.6, screen.s_height*.5));
	m_playerSprite[3].setPosition(sf::Vector2f( screen.s_width*.8, screen.s_height*.5));


	if (!m_tickTexture.loadFromFile("Assets/Images/tick.png"))
	{
		std::cout << "tick art error set up screen" << std::endl;
	}

	for (int i = 0; i < 4; i++)
	{
		m_tickSprite[i].setTexture(m_tickTexture);
		m_tickSprite[i].setScale(2, 2);
		m_tickSprite[i].setOrigin(m_tickTexture.getSize().x / 2, m_tickTexture.getSize().y / 2);
		m_joinedBool[i] = false;
	}
	m_tickSprite[0].setPosition(sf::Vector2f(screen.s_width*.28, screen.s_height*.4));
	m_tickSprite[1].setPosition(sf::Vector2f(screen.s_width*.48, screen.s_height*.4));
	m_tickSprite[2].setPosition(sf::Vector2f(screen.s_width*.68, screen.s_height*.4));
	m_tickSprite[3].setPosition(sf::Vector2f(screen.s_width*.88, screen.s_height*.4));


	if (!m_signTexture.loadFromFile("Assets/Images/start.png"))
	{
		std::cout << "sign art error set up screen" << std::endl;
	}
	m_signSprite.setTexture(m_signTexture);
	m_joinSprite.setOrigin(m_signTexture.getSize().x / 2, m_signTexture.getSize().y / 2);
	m_signSprite.setPosition(sf::Vector2f(screen.s_width*.7, screen.s_height*.71));
	m_signSprite.setScale(.6,.6);


	if (!m_exitSignTexture.loadFromFile("Assets/Images/exit.png"))
	{
		std::cout << "sign art error set up screen" << std::endl;
	}
	m_exitSignSprite.setTexture(m_exitSignTexture);
	m_exitSignSprite.setOrigin(m_exitSignTexture.getSize().x / 2, m_exitSignTexture.getSize().y / 2);
	m_exitSignSprite.setScale(.6,.6);
	m_exitSignSprite.setPosition(sf::Vector2f(screen.s_width*.23, screen.s_height*.84));



	m_screenBottom.setSize(sf::Vector2f(screen.s_width*.96, screen.s_height*.28));
	m_screenBottom.setPosition(screen.s_width*.02, screen.s_height*.7);
	m_screenBottom.setOutlineColor(sf::Color::White);
	m_screenBottom.setOutlineThickness(20);

	if (!m_curtainsTexture.loadFromFile("Assets/Images/sides.png"))
	{
		std::cout << "curtains art error set up screen" << std::endl;
	}
	m_curtainsSprite.setTexture(m_curtainsTexture);
	m_curtainsSprite.setScale(4,1.5);

	if (!m_BgTexture.loadFromFile("Assets/Images/brick.png"))
	{
		std::cout << "join art error set up screen" << std::endl;
	}
	m_BgSprite.setTexture(m_BgTexture);
	m_BgSprite.setPosition(0, -350);



	if (!m_joinTexture.loadFromFile("Assets/Images/join.png"))
	{
		std::cout << "join art error set up screen" << std::endl;
	}
	m_joinSprite.setTexture(m_joinTexture);
	m_joinSprite.setOrigin(m_joinTexture.getSize().x / 2, m_joinTexture.getSize().y / 2);
	m_joinSprite.setScale(.6, .6);
	m_joinSprite.setPosition(screen.s_width*.5, screen.s_height*.84);
}

void StartUp::update(XBOXController t_controller, sf::Time t_dt)
{

	m_screenTimerStart = std::chrono::system_clock::now();
	if (m_screenTimerStart > m_screenTimerEnd)
	{
		m_screenTimerEnd = m_screenTimerStart + std::chrono::milliseconds(1000);
		m_colourCount++;
		if (m_colourCount >= 6)
		{
			m_colourCount = 0;
		}
	}
	m_screenBottom.setFillColor(m_screenColours[m_colourCount]);

	if (t_controller.m_currentState.Back == true)
	{
		m_exit = true;
		m_buttonClick.play();
	}
	
	if (t_controller.m_currentState.Start == true&& m_joinedTotal >= 2)
	{
		if (!t_controller.m_previousState.Start)
		{
			m_start = true;
			m_buttonClick.play();
		}
	}


	for (int i = 0; i < 4; i++)
	{

		if (t_controller.sf_Joystick_index == i && m_joinedBool[i] == false)
		{
			if (t_controller.m_currentState.A)
			{
				m_joinedBool[i] = true;
				m_joinedTotal++;
				m_buttonClick.play();
			}
		}
		else if (t_controller.sf_Joystick_index == i && m_joinedBool[i] == true)
		{
			if (t_controller.m_currentState.B)
			{
				m_joinedBool[i] = false;
				m_joinedTotal--;
				m_buttonClick.play();
			}
		}
	}
}

void StartUp::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::Black);
	t_window.draw(m_BgSprite);
	t_window.draw(m_curtainsSprite);
	t_window.draw(m_screenBottom);
	t_window.draw(m_signSprite);
	t_window.draw(m_exitSignSprite);
	t_window.draw(m_joinSprite);
	

	for (int i = 0; i < 4; i++)
	{
		if (m_joinedBool[i] == true)
		{
			t_window.draw(m_tickSprite[i]);
		}
	}

	

	for (int i = 0; i < 4; i++)
	{
		t_window.draw(m_playerSprite[i]);
	}
}
