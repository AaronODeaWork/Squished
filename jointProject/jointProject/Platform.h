#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h" 
#include  <iostream>

class Platform
{
public:
	Platform(sf::Vector2f size, sf::Vector2f position, float decay);

	ScreenSize screen;
	void update(sf::Time t_dTime);
	void render(sf::RenderWindow &t_window);

	void SetPosition(sf::Vector2f t_postion);
	sf::Vector2f GetPosition();
	void SetSize(sf::Vector2f t_size);
	sf::Vector2f GetSize();
	void SetDecay(float t_decay);

	void setColor(sf::Color t_color);


private:

	
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	
	float m_decaySpeed;
	
	sf::RectangleShape m_PlatformRect;


};

