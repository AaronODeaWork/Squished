#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "XBOXCONTROLLER.h"
#include "Ui.h"

class Options
{
public:
	Options();
	~Options();

	Ui m_guiOptions;
	slider m_sliderBars;
	checkBox m_cBox;

	bool m_returnMenu = false;


	void loadContent();
	void update(XBOXController t_controller, sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);

	bool m_moved = false;

	XBOXController controller;

private:
	int ButtonTimer = 10;


	sf::Font m_font;
};

