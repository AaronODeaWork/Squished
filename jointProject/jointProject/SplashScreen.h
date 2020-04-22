#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

#include "XBOXCONTROLLER.h"
#include "ScreenSize.h"

class SplashScreen
{
public:
	SplashScreen();
	~SplashScreen();

	ScreenSize m_screen;


	void loadContent();
	void update(XBOXController t_controller, sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);



	///BOOLS///
	bool m_APressed = false;
private:
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;


	float m_timerEnd = 60;//timer for leaveing screen

	sf::Font m_font;
};

