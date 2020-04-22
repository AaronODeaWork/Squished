#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Author.h"
#include "SplashScreen.h"
#include "XBOXCONTROLLER.h"
#include "MainMenu.h"
#include "Options.h"
#include "Controls.h"
#include "Pause.h"
#include "StartUp.h"

#include "GameStates.h"
#include "Gameplay.h"

#include "ScreenSize.h"



static double const s_MS_PER_UPDATE = 10.0;

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();



private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	enum class gameState // enum to set up the screens
	{
		AUTHOR,
		SPLASH,
		MAINMENU,
		GAMEPLAY,
		CONTROLS,
		SETUP,
		OPTIONS,
		EXIT,

	};


	gameState m_currentState = gameState::AUTHOR;//start of game screen 
	GameState m_gameState;

	/// <summary>
	/// SCREENS
	/// </summary>
	Author m_authorScreen;
	SplashScreen m_splashScreen;
	StartUp m_startUp;
	Gameplay m_gameplay;
	Pause m_pauseM;


	/// <summary>
	/// Menus
	/// </summary>
	MainMenu m_menu;
	Options m_options;
	Controls m_controls;

	//JoyStick
	sf::RenderWindow m_window; // main SFML window

	static const unsigned int m_inputs = 4;
	XBOXController m_controller[m_inputs];
	

	sf::Time timeElapsed;  //Timer To Switch Between Screens
	sf::Clock tClock;


	sf::View m_default;//view for game 
	void checkControllerConnect(XBOXController controllers[]);
};

#endif // !GAME
