#include "Player.h"


Player::Player(XBOXController & t_controller)
{

	m_controller = &t_controller;

	m_velocity = sf::Vector2f(0, 0);
	m_position = sf::Vector2f(0, 0);
	m_previousPosition = m_position;
	m_size = sf::Vector2f(0, 0);



	m_FistVelocity = sf::Vector2f(0, 0);
	m_FistPosition = m_position;
	m_FistSize = sf::Vector2f(30,20);
	m_FistForce = sf::Vector2f(1200, 50);
	PunchThrown = false;
	m_playerAlive = true;
	m_timesHit = 0;
	JumpCount = 0;
	playerHit = 0;
	m_HitForce = sf::Vector2f(0, 0);
	FistHitDetectV = false;
	FistHitDetectH = false;
	m_score = 0;

	distance = 0;
	direction = sf::Vector2f(0,0);
	m_emoteUsed = false;
}

int Player::getIndex()
{
	if (m_controller->sf_Joystick_index == -1)
	{
		return 0;
	}
	return m_controller->sf_Joystick_index;
}

void Player::update(sf::Time t_dTime)
{
	m_punchStart = std::chrono::system_clock::now();
	m_jumpStart = std::chrono::system_clock::now();

	m_FistPosition = m_position;
	m_previousPosition = m_position;

	checkInBounds();//check if player left bottom of the screen


	if (m_hitStart <= m_hitEnd)
	{
		m_hitStart = std::chrono::system_clock::now();


		if (playerHit == 1)//if left hit
		{
			m_timesHit += 1;
			m_HitForce = sf::Vector2f(-m_FistForce.x*m_timesHit, -m_FistForce.y*m_timesHit);
		}
		else if (playerHit == 2)//if right hit 
		{
			m_timesHit += 1;
			m_HitForce = sf::Vector2f(m_FistForce.x*m_timesHit, -m_FistForce.y*m_timesHit);
		}
		if (m_HitForce.x < -5 || m_HitForce.x > 5)//check hit of x
		{
			m_HitForce.x = m_HitForce.x *.6f;//decrease the hit force  for x
			m_velocity.x += m_HitForce.x*.2f;//apply a low % of that force to the player
		}
		if (m_HitForce.y < -5 || m_HitForce.y > 5)//check hit for y
		{
			m_HitForce.y = m_HitForce.y *.3f;// decrease the hit force  for y
			m_velocity.y += m_HitForce.y*.2f;//apply a low % of that force to the player
		}
	}
		if (m_velocity.x < 0)//left
		{
			DirectionLR = false;
			m_fistSprite.setScale(-1, 1);
		}
		else if (m_velocity.x > 0)//right
		{
			DirectionLR = true;
			m_fistSprite.setScale(1, 1);

		}

	
	jump(t_dTime);//check for and update jump
	Punch();
	
	m_position = m_position + (m_velocity * t_dTime.asSeconds() * m_speed);

}

void Player::render(sf::RenderWindow & t_window)
{
	//these lines normalise everything so no matter the resolution of the screen they remain scaled correctly
	m_bodySprite.setPosition(sf::Vector2f(m_position.x, m_position.y));

	m_bodySprite.setScale(.13, .13);
	m_bodySprite.setOrigin(m_bodyTexture.getSize().x*.5, m_bodyTexture.getSize().y*.6);

	m_fistSprite.setPosition(sf::Vector2f(m_FistPosition.x, m_FistPosition.y));
	m_fistSprite.setOrigin(m_fistTexture.getSize().x*.4, m_fistTexture.getSize().y*.4);


	t_window.draw(m_bodySprite);
	t_window.draw(m_fistSprite);

	
	emote(t_window);

}
void Player::position(sf::Vector2f t_pos)
{
	m_position = t_pos;
	m_FistPosition = t_pos;
}
sf::Vector2f Player::position()
{
	return m_position;
}
sf::Vector2f Player::previousPostion()
{
	return m_previousPosition;
}
void Player::velocity(sf::Vector2f t_vel)
{
	m_velocity += t_vel;
}
sf::Vector2f Player::velocity()
{
	return m_velocity;
}
void Player::FistVelocity(sf::Vector2f t_velocity)
{
	m_FistVelocity = t_velocity;
}
sf::Vector2f Player::FistVelocity()
{
	return sf::Vector2f();
}
void Player::size(sf::Vector2f t_size)
{
	m_size = t_size;
}
sf::Vector2f Player::size()
{
	return m_size;
}
void Player::mass(float t_mass)
{
	m_mass = t_mass;
}
void Player::speed(float t_speed)
{
	m_speed = t_speed;
}

bool Player::getPunch()
{
	return PunchThrown;
}

void Player::setPunch(bool t_state)
{
	PunchThrown = t_state;
}

void Player::setHit(int t_state)
{
	playerHit = t_state;
}

int Player::GetHit()
{
	return playerHit;
}

void Player::setHitCount(int t_timesHit)
{
	m_timesHit = t_timesHit;
}
void Player::HitDectionPlatform(sf::Time t_dTime, sf::Vector2f m_platformPosition, sf::Vector2f m_platformSize)
{
	HitDetectV = false;
	HitDetectH = false;

	if (m_position.x - (m_size.x / 2) <= m_platformPosition.x + (m_platformSize.x / 2) &&
		m_position.x + (m_size.x / 2) >= m_platformPosition.x - (m_platformSize.x / 2))
	{
		HitDetectV = true;
	}

	if (m_position.y + (m_size.y / 2) >= m_platformPosition.y - (m_platformSize.y / 2) &&
		m_position.y - (m_size.y / 2) <= m_platformPosition.y + (m_platformSize.y / 2))
	{
		HitDetectH = true;
	}

	if (HitDetectH == true && HitDetectV == true)
	{
		m_position.y = m_previousPosition.y;
		m_velocity.y = m_velocity.y*-.3;
		JumpCount = 0;
	}

	if (HitDetectV == true &&
		(m_position.y + (m_size.y / 2) >= m_platformPosition.y - (m_platformSize.y / 2) &&
		(m_position.y - (m_size.y / 2) <= m_platformPosition.y + (m_platformSize.y / 2))))
	{
		m_position.x = m_previousPosition.x;
		m_velocity.x =0;	
	}
	else
	{
		if (m_controller->m_currentState.LeftThumbStick.x == 0)
		{
			m_velocity.x = 0;
		}
		else
		{
			m_velocity.x = m_controller->m_currentState.LeftThumbStick.x * .6;
		}
	}


}
int Player::HitDectionPlayer(sf::Time t_dTime, sf::Vector2f m_PlayerPosition, sf::Vector2f m_PlayerSize)
{
	if (PunchThrown == true)
	{
		FistHitDetectV = false;
		FistHitDetectH = false;

		if (m_FistPosition.x - (m_FistSize.x / 2) <= m_PlayerPosition.x + (m_PlayerSize.x / 2) &&
			m_FistPosition.x + (m_FistSize.x / 2) >= m_PlayerPosition.x - (m_PlayerSize.x / 2) &&
			FistHitDetectV == false)
		{
			FistHitDetectV = true;
		}

		if (m_FistPosition.y + (m_FistSize.y / 2) >= m_PlayerPosition.y - (m_PlayerSize.y / 2) &&
			m_FistPosition.y - (m_FistSize.y / 2) <= m_PlayerPosition.y + (m_PlayerSize.y / 2) &&
			FistHitDetectH == false)
		{
			FistHitDetectH = true;
		}

		if (FistHitDetectH == true && FistHitDetectV == true)
		{
			if (!DirectionLR)
			{
				return 1;
			}
			else
			{
				return 2;
			}

		}
	}
	return 0;
}

void Player::startHitTimer()
{
	if (m_hitStart > m_hitEnd)
	{
		m_hitStart = std::chrono::system_clock::now();
		m_hitEnd = m_hitStart + std::chrono::milliseconds(200);

	}
	
}

void Player::checkInBounds()
{
	if (m_position.y > screen.s_height+60)//check if player is  fallen out of map
	{

		m_velocity.y = 0;
		m_velocity.x = 0;
		m_playerAlive = false;// set player to false
	}
	if (m_position.y < 10)//check if player hit top of screen
	{
		m_velocity.y = 0;
		m_position.y = 10;
	}
	if (m_position.x < 0)//if players leave left of screen appears right
	{
		m_position.x = screen.s_width;
	}
	else if (m_position.x > screen.s_width)// if player leaves right of screen appears left side
	{
		m_position.x = 0;
	}
}
void Player::setAlive(bool t_State)
{
	m_playerAlive = t_State;
}
bool Player::checkAlive()
{
	return m_playerAlive;
}

void Player::setColour(sf::Color t_color)
{
	m_bodySprite.setColor(t_color);
}

void Player::addScore(int t_point)
{
	m_score += t_point;
}
void Player::setScore(int t_score)
{
	m_score = t_score;
}
int Player::getScore()
{
	return m_score;
}

int Player::getdDameage()
{
	return (m_FistForce.x*m_timesHit)/100;
}

void Player::loadContent()
{

	if (!m_fistTexture.loadFromFile("Assets/Images/glove.png"))
	{
		std::cout << "error glove Art" << std::endl;
	}
	m_fistSprite.setTexture(m_fistTexture);

	if (!m_bodyTexture.loadFromFile("Assets/Images/cube.png"))
	{
		std::cout << "error glove Art" << std::endl;
	}
	m_bodySprite.setTexture(m_bodyTexture);

	if (!m_angerEmoteTexture.loadFromFile("Assets/Images/anger.png"))
	{
		std::cout << "error anger emote Art" << std::endl;
	}
	m_angerEmoteSprite.setTexture(m_angerEmoteTexture);

	if (!m_loveEmoteTexture.loadFromFile("Assets/Images/love.png"))
	{
		std::cout << "error love emote Art" << std::endl;
	}
	m_loveEmoteSprite.setTexture(m_loveEmoteTexture);

	if (!m_curesEmoteTexture.loadFromFile("Assets/Images/curse.png"))
	{
		std::cout << "error curse emote Art" << std::endl;
	}
	m_curesEmoteSprite.setTexture(m_curesEmoteTexture);

	if (!m_skullEmotetexture.loadFromFile("Assets/Images/skull.png"))
	{
		std::cout << "error skull emote Art" << std::endl;
	}
	m_skullEmoteSprite.setTexture(m_skullEmotetexture);
}


void Player::checkForEmote()
{

	if (m_controller->m_currentState.DpadUp == true)
	{
		m_emote = 0;
		m_emoteUsed = true;
	}
	if (m_controller->m_currentState.DpadRight == true)
	{
		m_emote = 1;
		m_emoteUsed = true;
	}
	if (m_controller->m_currentState.DpadLeft == true)
	{
		m_emote = 2;
		m_emoteUsed = true;
	}
	if (m_controller->m_currentState.DpadDown == true)
	{
		m_emote = 3;
		m_emoteUsed = true;
	}

}
void Player::moveEmote()
{
	switch (m_emote)
	{

	case 0:
		m_loveEmoteSprite.setPosition(m_position.x+30,m_position.y-100);
		break;
	case 1:
		m_angerEmoteSprite.setPosition(m_position.x + 30, m_position.y - 100);
		break;
	case 2:
		m_skullEmoteSprite.setPosition(m_position.x + 30, m_position.y - 100);
		break;
	case 3:
		m_curesEmoteSprite.setPosition(m_position.x + 30, m_position.y - 100);
		break;
	default:
		break;
	}
}
void Player::emote(sf::RenderWindow & t_window)
{


	if (m_emoteUsed == false)//checks if player emoted 
	{
		checkForEmote();
	}
	else
	{
		moveEmote();
		drawEmote(t_window);
	}

	if (m_emoteUsed == true && m_emoteStart >= m_emoteEnd + std::chrono::milliseconds(1000))//checks if player emoted 
	{
		m_emoteEnd = m_emoteStart + std::chrono::milliseconds(1000);
	}
	else
	{
		m_emoteStart = std::chrono::system_clock::now();
	}
	if (m_emoteStart > m_emoteEnd)
	{
		m_emoteUsed = false;
	}
}
void Player::drawEmote(sf::RenderWindow & t_window)
{
	switch (m_emote)
	{

	case 0:
		t_window.draw(m_loveEmoteSprite);
		break;
	case 1:
		t_window.draw(m_angerEmoteSprite);
		break;
	case 2:
		t_window.draw(m_skullEmoteSprite);
		break;
	case 3:
		t_window.draw(m_curesEmoteSprite);
		break;
	default:
		break;
	}
}

void Player::Punch()
{
	if (m_punchStart > m_punchEnd + std::chrono::milliseconds(10))
	{
		m_FistVelocity.x = 0;
	}

	if (m_controller->m_currentState.B && PunchThrown == false && m_punchStart > m_punchEnd + std::chrono::milliseconds(300))
	{
		PunchThrown = true;
		m_punchStart = std::chrono::system_clock::now();
		m_punchEnd = m_punchStart + std::chrono::milliseconds(200);
	}

	if (m_punchStart < m_punchEnd && PunchThrown == true)
	{
		if (DirectionLR == false)//checks direction of punch
		{
			m_FistVelocity.x -= 5;
		}
		else
		{
			m_FistVelocity.x += 5;
		}
	}

	if (m_punchStart > m_punchEnd && PunchThrown == true)
	{
		PunchThrown = false;
	}
	m_FistPosition += m_FistVelocity;

	direction = m_position - m_FistPosition;
	distance = sqrt((direction.x*direction.x) + (direction.y*direction.y));
	if (distance >= 60)
	{
		m_FistVelocity.x = (direction.x / (distance*.6));
		m_FistVelocity.y = (direction.y / (distance*.6));
	}
}

void Player::jump(sf::Time t_dTime)
{
	if (m_controller->m_currentState.A)//if player presses jump button and hasnt jumped more than twice
	{
		if (JumpCount < 2)
		{
			m_jumpStart = std::chrono::system_clock::now();
			m_jumpEnd = m_jumpStart + std::chrono::milliseconds(110);
		}
		JumpCount++;// increase jump count                                
	}

	if (m_jumpStart < m_jumpEnd)
	{
		m_velocity.y = m_velocity.y + (t_dTime.asSeconds() * -(100)  * m_mass);// increase y velocity
	}
	else
	{
		m_velocity.y += (t_dTime.asSeconds() * gravity * m_mass);//apply gravity
	}
}



