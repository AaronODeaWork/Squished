#include "Ui.h"



Ui::Ui()
{
	setupAssets();
}


Ui::~Ui()
{
}

void Ui::setupAssets()
{
	//Sets up the text on the screen 
	if (!m_font.loadFromFile("ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
}

void Ui::setupStringsForMenu(std::string &t_string, std::string &t_stringTwo, std::string &t_stringThree, std::string &t_stringFour, sf::Vector2f &t_pos, sf::Color &t_color, int t_font)
{
	for (int i = 0; i < 4; i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setFillColor(t_color);
		m_text[i].setCharacterSize(t_font);
		m_text[i].setPosition(t_pos.x, t_pos.y + (i * 210));
	}
	m_text[0].setString(t_string);
	m_text[1].setString(t_stringTwo);
	m_text[2].setString(t_stringThree);
	m_text[3].setString(t_stringFour);
}

void Ui::setupStringsOptions(std::string & t_optionsString, std::string & t_optionsStringTwo, std::string & t_optionsStringThree, sf::Vector2f & t_optionsPos, sf::Color & t_optionsColor, int t_optionsFontSize)
{
	for (int i = 0; i < 3; i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setFillColor(t_optionsColor);
		m_text[i].setCharacterSize(t_optionsFontSize);
		m_text[i].setPosition(t_optionsPos.x, t_optionsPos.y + (i * 200));
	}
	m_text[0].setString(t_optionsString);
	m_text[1].setString(t_optionsStringTwo);
	m_text[2].setString(t_optionsStringThree);
}

void Ui::setupStringsForPause(std::string & t_resumeString, std::string &restart, std::string & t_exitToMain, sf::Vector2f & t_pos, int t_fontSize, sf::Color & t_color)
{
	for (int i = 0; i < 3; i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setFillColor(t_color);
		m_text[i].setCharacterSize(t_fontSize);
		m_text[i].setPosition(t_pos.x - 160, t_pos.y - 200 + (i * 200));
	}
	m_text[0].setString(t_resumeString);
	m_text[1].setString(restart);
	m_text[2].setString(t_exitToMain);
}


/// <summary>
/// Main Menu
/// </summary>
menuButtons::menuButtons()
{
	std::string Play = "Play";
	std::string Options = "Options";
	std::string Controls = "Controls";
	std::string Exit = "Exit";
	setupStringsForMenu(Play, Options,Controls,Exit, buttonPos, WHITE, m_optionsFontSize);
	
	createButtons();
}

menuButtons::~menuButtons()
{

}

void menuButtons::createButtons()
{
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		m_menuButton[i].setPosition(buttonPos.x, buttonPos.y + (i * 200));
		m_menuButton[i].setSize(sf::Vector2f(400, 100));
		m_menuButton[i].setFillColor(BLACK);
	}
}

void menuButtons::updateOutlineMenu()
{

	for (int i = 0; i < 4; i++)
	{
		if (orderOfRect == i)
		{
			m_menuButton[i].setOutlineColor(sf::Color::White);
			m_menuButton[i].setOutlineThickness(5);
		}
		else
		{
			m_menuButton[i].setOutlineColor(sf::Color::Transparent);
		}
	}
}

void menuButtons::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		t_window.draw(m_menuButton[i]);
		t_window.draw(m_text[i]);
	}

}



/// <summary>
/// Options Menu
/// </summary>
slider::slider()
{
	sliderText();
	createSlider();
	createSliderOutline();
}

slider::~slider()
{
}
void slider::sliderText()
{
	std::string MusicV ="Music Volume";
	std::string Effects = "Effects Volume" ;
	std::string Music = "Music On/Off";
	setupStringsOptions(MusicV,Effects,Music, m_sliderTextPos, WHITE, m_fontS);
}

void slider::createSlider()
{
	for (int i = 0; i < MAX_SLIDER; i++)
	{
		m_sliderSlot[i].setPosition(m_sliderPos.x, m_sliderPos.y + (i * 200));
		m_sliderSlot[i].setSize(sf::Vector2f(600, 80));
		m_sliderSlot[i].setFillColor(sf::Color::White);
		m_slidingR[i].setPosition(m_barPos.x, m_barPos.y + (i * 200));
		m_slidingR[i].setFillColor(sf::Color::Yellow);

	}

	m_slidingR[0].setSize(sf::Vector2f(m_musicBarLength, 70));
	m_slidingR[1].setSize(sf::Vector2f(m_speedBarLength, 70));
}

void slider::createSliderOutline()
{

	m_outlineChosen[0].setPosition(m_outlinePos.x, m_outlinePos.y);
	m_outlineChosen[0].setSize(sf::Vector2f(300, 60));
	m_outlineChosen[0].setFillColor(sf::Color::Transparent);

	m_outlineChosen[1].setPosition(m_outlinePos.x, m_outlinePos.y + 200);
	m_outlineChosen[1].setSize(sf::Vector2f(300, 60));
	m_outlineChosen[1].setFillColor(sf::Color::Transparent);

	m_outlineChosen[2].setPosition(m_outlinePos.x, m_outlinePos.y + 400);
	m_outlineChosen[2].setSize(sf::Vector2f(300, 60));
	m_outlineChosen[2].setFillColor(sf::Color::Transparent);
}

void slider::updateSliderOutline()
{

	for (int i = 0; i < 3; i++)
	{
		if (m_orderOfRectsOptions == i)
		{
			m_outlineChosen[i].setOutlineColor(sf::Color::White);
			m_outlineChosen[i].setOutlineThickness(5);
		}
		else
		{
			m_outlineChosen[i].setOutlineColor(sf::Color::Transparent);
		}
	}
}

void slider::changeMusicSliderColour()
{

	if (m_musicBarLength < 200)
	{
		m_slidingR[0].setFillColor(sf::Color::Red);
	}


	if (m_musicBarLength > 200)
	{
		m_slidingR[0].setFillColor(sf::Color::Yellow);
	}

	if (m_musicBarLength > 450)
	{
		m_slidingR[0].setFillColor(sf::Color::Green);
	}
}

void slider::changeEffectsColour()
{

	if (m_speedBarLength < 200)
	{
		m_slidingR[1].setFillColor(sf::Color::Red);
	}


	if (m_speedBarLength > 200)
	{
		m_slidingR[1].setFillColor(sf::Color::Yellow);
	}

	if (m_speedBarLength > 450)
	{
		m_slidingR[1].setFillColor(sf::Color::Green);
	}

}

void slider::updateSlider()
{
	m_slidingR[0].setSize(sf::Vector2f(m_musicBarLength, 70));
	m_slidingR[1].setSize(sf::Vector2f(m_speedBarLength, 70));

}

void slider::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < 3; i++)
	{
		t_window.draw(m_outlineChosen[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		t_window.draw(m_sliderText[i]);
		t_window.draw(m_sliderSlot[i]);
		t_window.draw(m_slidingR[i]);

	}

	for (int i = 0; i < 3; i++)
	{
		t_window.draw(m_text[i]);
	}
}


// constructor for checkbox
checkBox::checkBox()
{
	createCheckBox();
	setupCheckImage();
}

// deconstructor for checkbox
checkBox::~checkBox()
{
}


// draw checkbox to the screen
void checkBox::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < 2; i++)
	{
		t_window.draw(m_checkB[i]);
	}

	if (m_musicOn == true)
	{
		t_window.draw(m_tick);
	}
}

/// <summary>
/// creator function for checkbox
/// </summary>
void checkBox::createCheckBox()
{
	for (int i = 0; i < 2; i++)
	{
		m_checkB[i].setPosition(m_checkPos.x + (i * 5), m_checkPos.y + (i * 5));
		m_checkB[i].setSize(sf::Vector2f(50.0f - (i * 10.0f), 50.0f - (i * 10.0f)));
	}
	m_checkB[0].setFillColor(sf::Color::Black);
	m_checkB[1].setFillColor(sf::Color::White);
}

/// <summary>
/// setup image for checkbox
/// </summary>
void checkBox::setupCheckImage()
{
	if (!tickT.loadFromFile("Assets/Images/tick.png"))
	{
		std::cout << "problem loading  tick Image" << std::endl;
	}

	m_tick.setTexture(tickT);
	m_tick.setPosition(sf::Vector2f(408, 506));
	m_tick.scale(1 * 0.06f, 1 * 0.06f);
}

void checkBox::musicIsOn()
{
	m_musicOn = true;
}

void checkBox::musicIsOff()
{
	m_musicOn = false;
}

//Pause Buttons 
pauseButtons::pauseButtons()
{
	std::string Resume = "Resume";
	std::string Restart ="Restart";
	std::string Exit ="Exit to Main Menu";
	setupStringsForPause(Resume,Restart, Exit, buttonPos, m_FontSize, WHITE);
	createButtons();
}

pauseButtons::~pauseButtons()
{
}

void pauseButtons::createButtons()
{
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		m_pauseButton[i].setOrigin(200, 75);
		m_pauseButton[i].setPosition(buttonPos.x, buttonPos.y + (i * 200) - 150);
		m_pauseButton[i].setSize(sf::Vector2f(400, 100));
		m_pauseButton[i].setFillColor(BLACK);
		m_pauseButton[i].setOutlineColor(sf::Color::White);
	}
}

void pauseButtons::updateOutlinePause()
{

	for (int i = 0; i < 3; i++)
	{
		if (m_pauseButtonOrder == i)
		{
			m_pauseButton[i].setOutlineColor(sf::Color::White);
			m_pauseButton[i].setOutlineThickness(5);
		}
		else
		{
			m_pauseButton[i].setOutlineColor(sf::Color::Transparent);
		}
	}
}

void pauseButtons::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		t_window.draw(m_pauseButton[i]);
		t_window.draw(m_text[i]);
	}
}



void squareButtons::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < 2; i++)
	{
		t_window.draw(m_squareButton[i]);
		t_window.draw(m_text[i]);
	}
}
