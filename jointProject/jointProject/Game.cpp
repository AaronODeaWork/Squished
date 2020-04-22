
#include "Game.h"
#include <iostream>



//Screen is full screen for the moment
Game::Game() : m_window{ sf::VideoMode{ ScreenSize::s_width, ScreenSize::s_height, 32 }
, "SQUISHED ",sf::Style::Fullscreen }
{
	m_window.setVerticalSyncEnabled(true);
	checkControllerConnect(m_controller);

	m_default.setSize(ScreenSize::s_width, ScreenSize::s_height);
	m_default.setCenter(ScreenSize::s_width / 2, ScreenSize::s_height / 2);

}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}

		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	m_window.setView(m_default);

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		switch (m_currentState)
		{
		case Game::gameState::AUTHOR:
			break;

		case::Game::gameState::SPLASH:
			break;

		case gameState::MAINMENU:
			break;

		case gameState::SETUP:
			break;

		case gameState::CONTROLS:
			break;

		case gameState::OPTIONS:
			break;

		case gameState::GAMEPLAY:
			break;

		default:
			break;
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	for (int i = 0; i < m_inputs;i++)
	{
	m_controller[i].update();
	}


	switch (m_currentState)
	{
		/// <summary>
		/// update used for the Author screen
		/// <summary>
	case::Game::gameState::AUTHOR:
		m_authorScreen.update();

		//Timer To Move to next Screen
		timeElapsed = tClock.getElapsedTime();
		if (timeElapsed.asSeconds() >= 2)
		{
			m_currentState = gameState::SPLASH;
			timeElapsed = tClock.restart();
		}
		break;

		/// <summary>
		/// update used for the Splash screen
		/// <summary>
	case::Game::gameState::SPLASH:
		m_splashScreen.update(m_controller[0], t_deltaTime);
		if (m_splashScreen.m_APressed == true)
		{
			m_currentState = gameState::MAINMENU;
		}
		break;

		/// <summary>
		/// update used for the Main Menu screen
		/// <summary>
	case::Game::gameState::MAINMENU:
		m_menu.update(m_controller[0], t_deltaTime);

		if (m_menu.setupS)
		{
			m_currentState = gameState::SETUP;
		}
		if (m_menu.optionsS)
		{
			m_currentState = gameState::OPTIONS;
		}
		if (m_menu.controlsS)
		{
			m_currentState = gameState::CONTROLS;
		}
		if (m_menu.exit)
		{
			m_currentState = gameState::EXIT;
		}

		break;
	case::Game::gameState::SETUP:

		for (int i = 0; i < m_inputs; i++)//loop for updating controlers on setup screen
		{
			m_startUp.update(m_controller[i], t_deltaTime);
		}
		if (m_startUp.m_exit == true)
		{
			m_currentState = gameState::MAINMENU;
			m_menu.setupS = false;
			m_startUp.m_exit = false;		
		}

		if (m_startUp.m_start == true)
		{

			m_gameplay.setUpGame(m_startUp.m_joinedTotal);//put num of players here 
			m_gameplay.restartGame(m_startUp.m_joinedTotal);



			m_currentState = gameState::GAMEPLAY;
			m_startUp.m_start = false;
			m_gameplay.playMusic(); 
			m_menu.stopMusic();
			
		}

		break;

	case::Game::gameState::OPTIONS:
		m_options.update(m_controller[0], t_deltaTime);

		if (m_options.m_returnMenu == true)
		{
			m_currentState = gameState::MAINMENU;
			m_options.m_returnMenu = false;
			m_menu.optionsS = false;
		}

		
		if (m_controls.goBack == true)
		{
			m_currentState = gameState::MAINMENU;
			m_controls.goBack = false;
		}



		break;

		/// <summary>
		/// update used for the Gameplay 
		/// <summary>
	case::Game::gameState::GAMEPLAY:
		m_gameplay.update(t_deltaTime, m_controller[0]);
		
		if (m_gameplay.returnToMain == true)
		{
			m_startUp.m_exit = true;
			m_currentState = gameState::MAINMENU;
			m_gameplay.returnToMain = false;
			m_pauseM.m_moveToMain = false;
			m_gameplay.clearPlayers();
			m_menu.startMusic();

		}
		break;

		/// <summary>
		/// update used for the Options screen
		/// <summary>
	case::Game::gameState::CONTROLS:

		m_controls.update(m_controller[0], t_deltaTime);	

		if (m_controls.goBack)
		{
			m_currentState = gameState::MAINMENU;
			m_controls.goBack = false;
			m_menu.controlsS = false;

		}
		break;

	case gameState::EXIT:
		m_window.close();
	default:
		break;
	}
}


/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear();
	switch (m_currentState)
	{
	case gameState::AUTHOR:
		m_authorScreen.render(m_window);
		break;
	case gameState::SPLASH:
		m_splashScreen.render(m_window);
		break;
	case gameState::MAINMENU:
		m_menu.render(m_window);
		break;
	case gameState::SETUP:
		m_startUp.render(m_window);
		break;
	case gameState::GAMEPLAY:
		m_gameplay.render(m_window);
		break;

	case gameState::CONTROLS:
		m_controls.render(m_window);
		break;
	case gameState::OPTIONS:
		m_options.render(m_window);
		break;
	}
	m_window.display();
}
void Game::checkControllerConnect(XBOXController controllers[])
{
	for (int i = 0; i < m_inputs; i++)
	{
		if (!controllers[i].isConnected())
		{
			if (controllers[i].connect(i))
			{
				std::cout << "Controller Connected: " << i << std::endl;
			}
		}
	}
}
