#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "Ui.h"
#include "XBOXCONTROLLER.h"
class Controls
{
private:


public:

	Controls();

	void loadContent();
	void update(XBOXController t_controller, sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);


	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	bool moved = false;
	bool goBack = false;

	sf::Font m_font;

};

