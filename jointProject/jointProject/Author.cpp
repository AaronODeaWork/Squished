#include "Author.h"

Author::Author()
{
	loadContent();
}

void Author::loadContent()
{

	if (!m_backgroundTexture.loadFromFile("Assets/Images/author.png"))
	{
		std::cout << "author art error set up screen" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(1, .7);
}

void Author::update()
{
}

void Author::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_backgroundSprite);
}
