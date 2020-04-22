#pragma once

#include <SFML/Audio.hpp>
#include <iostream>
#include "XBOXCONTROLLER.h"
#include "ScreenSize.h"
#include "GameStates.h"
#include "Pause.h"
#include <chrono>
#include <thread>
#include "Player.h"
#include "Platform.h"



class Gameplay {
public:
	Gameplay();

	void run();
	void processGameEvents();
	void update(sf::Time t_deltaTime, XBOXController t_xbox);
	void loadContent();
	void restartGame(int t_numPlayers);

	void setUpGame(int t_numPlayers);
	void render(sf::RenderWindow & t_window);
	
	void playMusic();
	void clearPlayers();

	void getLeader();
	Pause m_pause;//pause state for game
	ScreenSize screen;

	GameState m_gamestate{ GameState::GAME_RUNNING };//Initial Game State set to Game Running
	bool returnToMain = false;
	bool m_resetViewForMain = false;

private:
	std::chrono::time_point<std::chrono::system_clock> m_winTimerStart;
	std::chrono::time_point<std::chrono::system_clock> m_winTimerEnd;

	std::chrono::time_point<std::chrono::system_clock> m_winGameTimerStart;
	std::chrono::time_point<std::chrono::system_clock> m_winGameTimerEnd;
	int m_leaderId = 0;

	sf::Music CrowdBgMusic;
	sf::SoundBuffer m_fightStartBuffer;
	sf::Sound m_fightStart;


	sf::SoundBuffer m_winSoundBuffer;
	sf::Sound m_winSound;
	
	sf::Sprite m_winSprite;
	sf::Texture m_winTexture;

	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;

	sf::Sprite m_pauseSprite;
	sf::Texture m_pauseTexture;
	sf::RectangleShape m_pauseBar[4];
	sf::Vector2f m_PausePostion[4];

	sf::Sprite m_winGameSprite;
	sf::Texture m_winGameTexture;
	sf::Vector2f m_winPostion[5];
	int m_rank[5];
	bool m_rankPlaced[5];
	bool m_rankPlacedAgain[5];
	bool m_rankingDone;

	sf::Texture m_crownTexture;
	sf::Sprite m_crownSprite;

	sf::Texture m_uiTexture;
	sf::Sprite m_uiSprite[4];
	sf::RectangleShape m_winBar[4];

	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite[4];
	sf::Text m_playerDamageText[4];

	sf::Color m_screenColours[6];
	sf::Vector2f m_winBarSize[6];


	int m_numberOfPlayers = 4;
	static const unsigned int m_numberOfPlatform = 4;

	std::vector<Player> m_player;
	std::vector<Platform> m_platforms;

	sf::Vector2f m_platformOne[4];
	sf::Vector2f m_platformTwo[4];
	sf::Vector2f m_platformThree[4];
	sf::Vector2f m_platformFour[4];


	XBOXController m_controller[4];
	
	
	//JoyStick
	sf::Font m_font;
	sf::Text m_gameplayText;

	sf::Time timeElapsed;

	sf::Clock tClock;
	
	void checkControllerConnect(XBOXController controllers[]);
	bool checkPlayersAlive();
};