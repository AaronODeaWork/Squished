#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "Ui.h"
#include "XBOXCONTROLLER.h"
#include "ScreenSize.h"
#include "SFML/Audio.hpp"


class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void loadContent();
	void update(XBOXController controller, sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);


	void startMusic();
	void stopMusic();


	Ui m_ui;
	menuButtons m_menuB;

	bool moved = false;
	bool setupS = false;
	bool controlsS = false;
	bool optionsS = false;
	bool exit = false;
private:
	int ButtonTimer = 10;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTextureTwo;
	sf::Sprite m_backgroundSpriteTwo;

	sf::SoundBuffer m_buttonBuffer;
	sf::Sound m_buttonClick;


	sf::Music m_menuMusic;

	float m_bgTransparent = 50;
	bool m_bgflip = true;
	sf::Text m_mainMenuText;

	sf::Font m_font;
};

