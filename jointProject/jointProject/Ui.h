#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "XBOXCONTROLLER.h"
#include "ScreenSize.h"
#include <xstring>

class Ui
{
public:
	Ui();
	~Ui();

	/// <summary>
	/// Array Size
	/// </summary>

	void setupAssets();
	void setupStringsForMenu(std::string &t_string, std::string &t_stringTwo, std::string &t_stringThree, std::string &t_stringFour, sf::Vector2f &t_pos, sf::Color &t_color, int t_font);
	void setupStringsOptions(std::string &t_optionsString, std::string &t_optionsStringTwo, std::string &t_optionsStringThree, sf::Vector2f &t_optionsPos, sf::Color &t_optionsColor, int t_optionsFontSize);
	void setupStringsForPause(std::string & t_resumeString, std::string &restart, std::string &t_exitToMain, sf::Vector2f &t_pos, int t_fontSize, sf::Color & t_color);



	sf::Color WHITE = { 255,255,255,255 };
	sf::Color BLACK = { 0,0,0,100 };
	sf::Text m_text[5];
	sf::Font m_font;
};

class menuButtons :Ui
{
public:
	menuButtons();
	~menuButtons();

	void createButtons();
	void updateOutlineMenu();

	void render(sf::RenderWindow & t_window);



	/// <summary>
	/// To check which rectangle is selected
	/// </summary>
	int orderOfRect = 0;

	/// <summary>
	/// Button Pos
	/// </summary>
	float m_x = 50;
	float m_y = 75;

	sf::Vector2f buttonPos{ m_x,m_y };

	sf::RectangleShape m_menuButton[4];

	int m_optionsFontSize = 34;

	const int MAX_BUTTONS = 4;


};


class slider :Ui
{
public:
	slider();
	~slider();

	void sliderText();
	void createSlider();
	void createSliderOutline();
	void updateSliderOutline();
	void changeMusicSliderColour();
	void changeEffectsColour();

	void updateSlider();
	void render(sf::RenderWindow &t_window);

	int m_orderOfRectsOptions = 0;

	float m_musicBarLength = 290;
	float m_speedBarLength = 290;

	float MIN_BAR = 0.0f;
	float MAX_BAR = 599.0f;

private:
	sf::RectangleShape m_sliderSlot[2]; // apply an image on top to mimic a slider slot 
	sf::RectangleShape m_slidingR[2];
	sf::RectangleShape m_outlineChosen[3];

	// Used for the sliders
	float m_x = 400.0f;
	float m_y = 80.0f;

	//used for slider text
	float m_xText = 50.0f;
	float m_yText = 100.0f;

	//used for the sliding bar itself
	float m_barX = 405.0f;
	float m_barY = 85.0f;

	//Used for the Outline of the Text
	float m_outlineX = 40.0f;
	float m_outlineY = 100.0f;


	sf::Vector2f m_sliderPos{ m_x,m_y }; // for the shell of the slider
	sf::Vector2f m_sliderTextPos{ m_xText,m_yText }; // for the text of each slider
	sf::Vector2f m_outlinePos{ m_outlineX,m_outlineY }; // used for the outline of the text
	sf::Vector2f m_barPos{ m_barX,m_barY };

	sf::Text m_sliderText[2];

	const int MAX_RECTANGLE_BUTTONS = 3;
	const int MAX_SLIDER = 2;


	//Changable font size
	int m_fontS = 32;

	//Used to change the spacing of the Text
	int m_spacing = 3;
};

class checkBox :Ui
{
public:

	checkBox();
	~checkBox();
	void render(sf::RenderWindow & t_window);
	void createCheckBox();
	void setupCheckImage();
	void musicIsOn();
	void musicIsOff();


	//Checks if the music is active
	bool m_musicOn = false;


	//position for the check box
	float m_checkX = 400.0f;
	float m_checkY = 500.0f;
	sf::Vector2f m_checkPos{ m_checkX,m_checkY };


private:
	sf::RectangleShape m_checkB[2];
	sf::Sprite m_tick;
	sf::Texture tickT;
};

class pauseButtons :Ui
{
public:
	pauseButtons();
	~pauseButtons();

	void createButtons();
	void updateOutlinePause();

	void render(sf::RenderWindow & t_window);



	/// <summary>
	/// To check which rectangle is selected
	/// </summary>
	int m_pauseButtonOrder = 0;

	/// <summary>
	/// Button Pos
	/// </summary>


	sf::Vector2f buttonPos{ ScreenSize::s_width * 0.23f , ScreenSize::s_height * 0.5f };

	sf::RectangleShape m_pauseButton[3];

	int m_FontSize = 34;

	const int MAX_BUTTONS = 3;


};

class squareButtons : Ui
{
public:

	sf::RectangleShape m_squareButton[2];
	sf::Vector2f m_squarePos{ 900 , 650 };
	int m_orderOfRectSquaresThrust = 0;
	int m_orderOfRectSquaresLG = 0;
	int m_orderOfRectSquaresFuel = 0;
	int m_orderOfRectSquaresCargo = 0;
	int m_orderOfRectSquaresFlares = 0;


	int m_FontSize = 34;

	void render(sf::RenderWindow & t_window);

};

