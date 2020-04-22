#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "Ui.h"
#include "XBOXCONTROLLER.h"
class Pause
{
public:
	Pause();
	~Pause();


	void loadContent();
	void update(XBOXController controller, sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);

	bool m_moveToMain = false;
	bool m_resume = false;
	bool m_restart = false;


	int ButtonTimer = 10;
	Ui m_ui;
	pauseButtons m_pauseB;
};

