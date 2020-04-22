#include "Platform.h"



Platform::Platform(sf::Vector2f size , sf::Vector2f position , float decay )
{
	m_position = position;
	m_size = size;
	m_decaySpeed = decay;
	m_PlatformRect.setOutlineColor(sf::Color::White);
	m_PlatformRect.setOutlineThickness(2.0f);

}


void Platform::update(sf::Time t_dTime)
{
	
	if (m_size.x > 0)
	{
		m_size.x -= m_decaySpeed;
	}
	else
	{
		m_size.x = 0;
		m_position.x = 0;
		m_position.y = 0;
	}
	
}

void Platform::render(sf::RenderWindow & t_window)
{
	m_PlatformRect.setPosition(sf::Vector2f(m_position.x, m_position.y));
	m_PlatformRect.setSize(sf::Vector2f(m_size.x, m_size.y));
	m_PlatformRect.setOrigin(m_PlatformRect.getSize().x/2, m_PlatformRect.getSize().y/2);

	t_window.draw(m_PlatformRect);
}


void Platform::SetPosition(sf::Vector2f t_postion)
{
	m_position = t_postion;

}

sf::Vector2f Platform::GetPosition()
{
	return m_position;
}

void Platform::SetSize(sf::Vector2f t_size)
{
	m_size = t_size;
}

sf::Vector2f Platform::GetSize()
{
	return m_size;
}

void Platform::SetDecay(float t_decay)
{
	m_decaySpeed = t_decay;
}

void Platform::setColor(sf::Color t_color)
{
	m_PlatformRect.setFillColor(t_color);
}




