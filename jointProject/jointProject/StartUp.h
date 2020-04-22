#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "Ui.h"
#include <chrono>
#include <thread>
#include "XBOXCONTROLLER.h"
#include "ScreenSize.h"
#include "SFML/Audio.hpp"

class StartUp {
public:
	StartUp();

	ScreenSize screen;

	void loadContent();
	void update(XBOXController t_controller, sf::Time t_dt);
	void render(sf::RenderWindow &t_window);

	int m_optionsFontSize = 34;


	sf::RectangleShape m_screenBottom;

	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite[4];


	sf::Texture m_tickTexture;
	sf::Sprite m_tickSprite[4];

	int m_joinedTotal = 0;
	bool m_joinedBool[4];

	sf::Texture m_BgTexture;
	sf::Sprite m_BgSprite;

	sf::Texture m_signTexture;
	sf::Sprite m_signSprite;

	sf::Texture m_exitSignTexture;
	sf::Sprite m_exitSignSprite;

	sf::Texture m_joinTexture;
	sf::Sprite m_joinSprite;

	sf::Texture m_curtainsTexture;
	sf::Sprite m_curtainsSprite;


	sf::SoundBuffer m_buttonBuffer;
	sf::Sound m_buttonClick;


	sf::Color m_screenColours[6];
	bool m_start = false;
	bool m_exit = false;

	bool m_buttonReleased = false;	// check if button released
	float m_releaseTimer = 0;		// how long the button has nor been pressed

	std::chrono::time_point<std::chrono::system_clock> m_screenTimerStart;
	std::chrono::time_point<std::chrono::system_clock> m_screenTimerEnd;
	int m_colourCount = 0;

};