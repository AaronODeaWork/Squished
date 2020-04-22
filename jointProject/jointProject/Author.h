#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "ScreenSize.h"



class Author
{
public:
	Author();

	ScreenSize m_screen;

	void loadContent();
	void update();
	void render(sf::RenderWindow & t_window);

private:

	sf::Text m_authorText;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;


	sf::Font m_font;
};

