#include "Gameplay.h"

Gameplay::Gameplay()
{

	loadContent();
	setUpGame(4);
	m_player.clear();
	m_platforms.clear();
	m_rank[0] = 5;
	m_rank[1] = 4;
	m_rank[2] = 3;
	m_rank[3] = 2;
	m_rank[4] = 1;


}

void Gameplay::run()
{
}
void Gameplay::processGameEvents()
{
}

void Gameplay::update(sf::Time t_deltaTime, XBOXController t_xbox)
{			
	checkControllerConnect(m_controller);//check the controlers connected 
	
	for (int i = 0; i < m_numberOfPlayers; i++)//update for each players controller
	{
		m_controller[i].update();
	}
	switch (m_gamestate)
	{
	case GameState::GAME_RUNNING://update fro game running 
		if (checkPlayersAlive())
		{
			
			m_gamestate = GameState::GAME_WIN;
			m_winTimerStart = std::chrono::system_clock::now();
			m_winTimerEnd = m_winTimerStart + std::chrono::milliseconds(1000);

			for (int i = 0; i < m_numberOfPlayers; i++)//loop through all the players 
			{
				if (m_player[i].checkAlive() == true)// check if player is alive
				{
					m_player[i].addScore(1);
					break;
				}
			}
			getLeader();

		}

		m_crownSprite.setPosition(m_player[m_leaderId].position().x-60, m_player[m_leaderId].position().y-60);//moveing the crown with the player 
	    for (int i = 0; i < m_numberOfPlayers; i++)//loop for player and hitdetection update
		{
		m_player[i].update(t_deltaTime);//player update
		m_playerDamageText[i].setString(std::to_string(m_player[i].getdDameage()));

			for (int j = 0; j < m_numberOfPlatform; j++)//update for each player to platform hit detection
			{
				m_player[i].HitDectionPlatform(t_deltaTime, m_platforms[j].GetPosition(), m_platforms[j].GetSize());
			} 
			for (int k = 0; k < m_numberOfPlayers; k++)//loop for player fist  hit detection
			{
				if (i != k && m_player[i].getPunch() && m_player[i].GetHit() == 0 )//checks if the hit detect is not checking itself 
				{
					m_player[k].setHit(m_player[i].HitDectionPlayer
					(t_deltaTime,m_player[k].position(), m_player[k].size()));//player fist and players 
					m_player[k].startHitTimer();
				}
			}
		}

		for (int i = 0; i < m_numberOfPlatform; i++)//update for platforms shrinking
		{
			m_platforms[i].update(t_deltaTime);
		}

		if (t_xbox.m_currentState.Start == true)//update for pauseing the game
		{
			if (!t_xbox.m_previousState.Start)//check if start pressed  was not the previous button 
			{
				m_gamestate = GameState::GAME_PAUSE;
			}
		}

		break;
	case GameState::GAME_WIN://update for win state 
		m_winTimerStart = std::chrono::system_clock::now();
		m_crownSprite.setPosition(m_player[m_leaderId].position().x - 60, m_player[m_leaderId].position().y - 60);//moveing the crown with the player 

		std::cout << "match win " << std::endl;
		for (int i = 0; i < m_numberOfPlayers; i++)//loop through all the players 
		{
			if (m_player[i].checkAlive() == true)// check if player is alive
			{
				m_player[i].position(sf::Vector2f((screen.s_width / 2)+60, screen.s_height*.55));
			}
		}

		if (m_winTimerStart >= m_winTimerEnd)
		{
			restartGame(m_numberOfPlayers);
			m_fightStart.play();
			CrowdBgMusic.play();
			m_gamestate = GameState::GAME_RUNNING;
		}
	
		break;

	case GameState::GAME_PAUSE://update for game paused 
		CrowdBgMusic.stop();
		m_pause.update(t_xbox, t_deltaTime);// update the pause screen

		for (int i = 0; i < m_numberOfPlayers; i++)
		{
			m_player[i].position(m_PausePostion[i]);
		}


		if (m_pause.m_resume == true)// resume is true return to game 
		{
			CrowdBgMusic.play();
			m_gamestate = GameState::GAME_RUNNING;
			m_pause.m_resume = false;
			for (int i = 0; i < m_numberOfPlayers; i++)
			{
				m_player[i].position(m_player[i].previousPostion());
			}
		}
		if (m_pause.m_restart == true)// if restart is pressed restart match 
		{
			CrowdBgMusic.play();
			restartGame(m_numberOfPlayers);
			m_fightStart.play();
			m_pause.m_restart = false;
			m_gamestate = GameState::GAME_RUNNING;
		}
	
		if (m_pause.m_moveToMain == true)//if return to menu button pressed return to the menu
		{
			CrowdBgMusic.stop();
			m_resetViewForMain = true;
			returnToMain = true;
			m_gamestate = GameState::GAME_RUNNING;
			m_pause.m_moveToMain = false;
		}
		break;

	case GameState::GAME_END:

		m_winGameTimerStart = std::chrono::system_clock::now();
		if (m_winGameTimerStart >= m_winGameTimerEnd)
		{
			CrowdBgMusic.stop();
			for (int i = 0; i < m_numberOfPlayers; i++)
			{
				m_player[i].setScore(0);
			}
			
			m_resetViewForMain = true;
			returnToMain = true;
			m_gamestate = GameState::GAME_RUNNING;
		}

		break;
	default:
		break;
	}
}

void Gameplay::loadContent()
{
	m_screenColours[0] = sf::Color(255, 0, 0, 200);
	m_screenColours[1] = sf::Color(255, 127, 0, 200);
	m_screenColours[2] = sf::Color(255, 255, 0, 200);
	m_screenColours[3] = sf::Color(0, 255, 0, 200);
	m_screenColours[4] = sf::Color(0, 0, 255, 200);
	m_screenColours[5] = sf::Color(75, 0, 130, 200);


	m_winBarSize[0] = sf::Vector2f(40,0);
	m_winBarSize[1] = sf::Vector2f(40, -50);
	m_winBarSize[2] = sf::Vector2f(40, -85);
	m_winBarSize[3] = sf::Vector2f(40, -120);
	m_winBarSize[4] = sf::Vector2f(40, -155);
	m_winBarSize[5] = sf::Vector2f(40, -185);

	m_winPostion[0] = sf::Vector2f((screen.s_width / 2)+50 ,635);
	m_winPostion[1] = sf::Vector2f((screen.s_width / 2)-80 ,775);
	m_winPostion[2] = sf::Vector2f((screen.s_width / 2)+130,945);
	m_winPostion[3] = sf::Vector2f((screen.s_width / 2)-50 ,1135);
	m_winPostion[4] = sf::Vector2f((screen.s_width / 2), 1385);



	m_PausePostion[0] = sf::Vector2f(screen.s_width * .5, screen.s_height*.75);
	m_PausePostion[1] = sf::Vector2f(screen.s_width * .6, screen.s_height*.75);
	m_PausePostion[2] = sf::Vector2f(screen.s_width * .7, screen.s_height*.75);
	m_PausePostion[3] = sf::Vector2f(screen.s_width * .8, screen.s_height*.75);




	 
	m_platformOne[0] = sf::Vector2f(sf::Vector2f(screen.s_width / 2, screen.s_height * .8));
	m_platformOne[1] = sf::Vector2f(sf::Vector2f(screen.s_width / 2, screen.s_height*.4));
	m_platformOne[2] = sf::Vector2f(sf::Vector2f(screen.s_width / 2, screen.s_height * .7));
	m_platformOne[3] = sf::Vector2f(sf::Vector2f(screen.s_width / 2, screen.s_height * .5));

	m_platformTwo[0] = sf::Vector2f(250, screen.s_height *.5);
	m_platformTwo[1] = sf::Vector2f(250, screen.s_height *.8);
	m_platformTwo[2] = sf::Vector2f(250, screen.s_height *.6);
	m_platformTwo[3] = sf::Vector2f(250, screen.s_height *.2);

	m_platformThree[0] = sf::Vector2f(screen.s_width - 250, screen.s_height * .5);
	m_platformThree[1] = sf::Vector2f(screen.s_width - 250, screen.s_height * .8);
	m_platformThree[2] = sf::Vector2f(screen.s_width - 250, screen.s_height * .8);
	m_platformThree[3] = sf::Vector2f(screen.s_width - 250, screen.s_height * .2);

	m_platformFour[0] = sf::Vector2f(screen.s_width / 2, 300);
	m_platformFour[1] = sf::Vector2f(sf::Vector2f(screen.s_width / 2, screen.s_height * .7));
	m_platformFour[2] = sf::Vector2f(screen.s_width / 2, screen.s_height * .6);
	m_platformFour[3] = sf::Vector2f(screen.s_width / 2, screen.s_height * .8);




	if (!m_font.loadFromFile("ariblk.ttf"))
	{
		std::cout << "font error" << std::endl ;
	}

	if (!CrowdBgMusic.openFromFile("Assets/sound/fightBackground.wav"))
	{
		std::cout << "error crowd music" << std::endl;
	}

	if (!m_fightStartBuffer.loadFromFile("Assets/sound/fightVoice.wav"))
	{
		std::cout << "error fight sound" << std::endl;
	}
	m_fightStart.setBuffer(m_fightStartBuffer);

	if (!m_winSoundBuffer.loadFromFile("Assets/sound/win.wav"))
	{
		std::cout << "error Win sound" << std::endl;
	}
	m_winSound.setBuffer(m_winSoundBuffer);

	if (!m_winTexture.loadFromFile("Assets/Images/Win.png"))
	{
		std::cout << "error Win Art" << std::endl;
	}
	m_winSprite.setTexture(m_winTexture);
	m_winSprite.setPosition(sf::Vector2f((screen.s_width / 2)-450, screen.s_height*.34));


	if (!m_pauseTexture.loadFromFile("Assets/Images/graph.png"))
	{
		std::cout << "error with graph art " << std::endl;
	}
	m_pauseSprite.setTexture(m_pauseTexture);
	m_pauseSprite.setPosition(sf::Vector2f((screen.s_width / 2)- 200, screen.s_height*.02));

	if (!m_crownTexture.loadFromFile("Assets/Images/crown.png"))
	{
		std::cout << "error crown Art" << std::endl;
	}
	m_crownSprite.setTexture(m_crownTexture);
	m_crownSprite.rotate(-30.0f);

	if (!m_bgTexture.loadFromFile("Assets/Images/bgGame.png"))
	{
		std::cout << "background  Art error" << std::endl;
	}
	m_bgSprite.setTexture(m_bgTexture);

	if (!m_winGameTexture.loadFromFile("Assets/Images/winEnd.png"))
	{
		std::cout << "winEnd  Art error" << std::endl;
	}
	m_winGameSprite.setTexture(m_winGameTexture);
	m_winGameSprite.setPosition(sf::Vector2f((screen.s_width / 2) - 550, screen.s_height*.121));


	if (!m_uiTexture.loadFromFile("Assets/Images/ui.png"))
	{
		std::cout << "ui  Art error" << std::endl;
	}
	if (!m_playerTexture.loadFromFile("Assets/Images/cube.png"))
	{
		std::cout << "player  Art ui error" << std::endl;
	}
	for (int i = 0; i < 4; i++)
	{
		m_uiSprite[i].setTexture(m_uiTexture);
		m_uiSprite[i].setScale(.5, .5);

		m_playerSprite[i].setTexture(m_playerTexture);
		m_playerSprite[i].setScale(.25, .25);

		m_winBar[i].setSize(m_winBarSize[0]);//bar for when the player wins a game (ui)

		m_pauseBar[i].setSize(sf::Vector2f(50 ,0));//bar for the pause screen 

		m_playerDamageText[i].setFont(m_font);
		m_playerDamageText[i].setString("");
		m_playerDamageText[i].setFillColor(sf::Color::Black);
		m_rankPlaced[i] = false;
		m_rankPlacedAgain[i] = false;
		
	}

	
	m_winBar[0].setPosition(sf::Vector2f((screen.s_width * .104), screen.s_height*.98));
	m_winBar[1].setPosition(sf::Vector2f((screen.s_width * .304), screen.s_height*.98));
	m_winBar[2].setPosition(sf::Vector2f((screen.s_width * .504), screen.s_height*.98));
	m_winBar[3].setPosition(sf::Vector2f((screen.s_width * .704), screen.s_height*.98));

	m_playerSprite[0].setPosition(sf::Vector2f((screen.s_width * .12), screen.s_height*.8));
	m_playerSprite[1].setPosition(sf::Vector2f((screen.s_width * .32), screen.s_height*.8));
	m_playerSprite[2].setPosition(sf::Vector2f((screen.s_width * .52), screen.s_height*.8));
	m_playerSprite[3].setPosition(sf::Vector2f((screen.s_width * .72), screen.s_height*.8));

	m_playerDamageText[0].setPosition(sf::Vector2f((screen.s_width *.17), screen.s_height*.955));
	m_playerDamageText[1].setPosition(sf::Vector2f((screen.s_width *.37), screen.s_height*.955));
	m_playerDamageText[2].setPosition(sf::Vector2f((screen.s_width *.57), screen.s_height*.955));
	m_playerDamageText[3].setPosition(sf::Vector2f((screen.s_width *.77), screen.s_height*.955));

	m_pauseBar[0].setPosition(sf::Vector2f(screen.s_width * .49, screen.s_height*.65));
	m_pauseBar[1].setPosition(sf::Vector2f(screen.s_width * .59, screen.s_height*.65));
	m_pauseBar[2].setPosition(sf::Vector2f(screen.s_width * .69, screen.s_height*.65));
	m_pauseBar[3].setPosition(sf::Vector2f(screen.s_width * .79, screen.s_height*.65));

	m_uiSprite[0].setPosition(sf::Vector2f((screen.s_width * .1), screen.s_height*.78));
	m_uiSprite[1].setPosition(sf::Vector2f((screen.s_width * .3), screen.s_height*.78));
	m_uiSprite[2].setPosition(sf::Vector2f((screen.s_width * .5), screen.s_height*.78));
	m_uiSprite[3].setPosition(sf::Vector2f((screen.s_width * .7), screen.s_height*.78));

	m_playerSprite[0].setColor(sf::Color(255, 255, 255, 200));
	m_playerSprite[1].setColor(sf::Color(255, 0, 0, 200));
	m_playerSprite[2].setColor(sf::Color(200, 0, 255, 200));
	m_playerSprite[3].setColor(sf::Color(255, 200, 0, 200));
	
	

}
void Gameplay::restartGame(int t_numPlayers )
{
	m_numberOfPlayers = t_numPlayers;

	int randomLv = rand() % 4;

	m_platforms[0].SetPosition(m_platformOne[randomLv]);
	m_platforms[1].SetPosition(m_platformTwo[randomLv]);
	m_platforms[2].SetPosition(m_platformThree[randomLv]);
	m_platforms[3].SetPosition(m_platformFour[randomLv]);

	std::cout << randomLv << std::endl;
	if (m_numberOfPlayers == 2)
	{
		
		if (randomLv == 0)
		{
			m_player[1].position(sf::Vector2f(m_platformFour[randomLv].x, m_platformFour[randomLv].y - 100));
			m_player[0].position(sf::Vector2f(m_platformOne[randomLv].x, m_platformOne[randomLv].y - 100));
		}
		else
		{

			m_player[1].position(sf::Vector2f(m_platformOne[randomLv].x + 350, m_platformOne[randomLv].y - 100));
			m_player[0].position(sf::Vector2f(m_platformOne[randomLv].x - 350, m_platformOne[randomLv].y - 100));
		}
	

		
		
	}
	else if (m_numberOfPlayers == 3)
	{
		if (randomLv == 2)
		{
			m_player[0].position(sf::Vector2f(m_platformFour[randomLv].x, m_platformFour[randomLv].y - 100));
		}
		else
		{
			m_player[0].position(sf::Vector2f(m_platformOne[randomLv].x, m_platformOne[randomLv].y - 100));
		}
		m_player[1].position(sf::Vector2f(m_platformTwo[randomLv].x, m_platformTwo[randomLv].y - 100));
		m_player[2].position(sf::Vector2f(m_platformThree[randomLv].x, m_platformThree[randomLv].y - 100));

	}
	else if (m_numberOfPlayers == 4)
	{
		
	
		if (randomLv == 3)
		{
			m_player[0].position(sf::Vector2f(m_platformOne[randomLv].x-200, m_platformOne[randomLv].y - 100));
			m_player[1].position(sf::Vector2f(m_platformOne[randomLv].x+200, m_platformOne[randomLv].y - 100));
		}
		else
		{
			m_player[0].position(sf::Vector2f(m_platformOne[randomLv].x, m_platformOne[randomLv].y - 100));
			m_player[1].position(sf::Vector2f(m_platformFour[randomLv].x, m_platformFour[randomLv].y - 100));
		}
		if (randomLv == 2)
		{
			m_player[0].position(sf::Vector2f(m_platformOne[randomLv].x, m_platformOne[randomLv].y - 60));
		}
	

		m_player[2].position(sf::Vector2f(m_platformThree[randomLv].x, m_platformThree[randomLv].y - 100));

		m_player[3].position(sf::Vector2f(m_platformTwo[randomLv].x, m_platformTwo[randomLv].y - 100));
	}

	m_platforms[0].SetSize(sf::Vector2f(1200, 20));
	m_platforms[0].SetDecay(.3f);

	m_platforms[1].SetSize(sf::Vector2f(500, 20));
	m_platforms[1].SetDecay(.2f);

	m_platforms[2].SetSize(sf::Vector2f(500, 20));
	m_platforms[2].SetDecay(.2f);

	m_platforms[3].SetSize(sf::Vector2f(500, 20));
	m_platforms[3].SetDecay(.4f);

	checkControllerConnect(m_controller);
	m_rankingDone = false;

	for (int i = 0; i < m_numberOfPlayers; i++)
	{
		m_player[i].velocity(sf::Vector2f(0, 0));
		m_player[i].size(sf::Vector2f(60, 100));
		m_player[i].speed(10);
		m_player[i].mass(5);
		m_player[i].setAlive(true);
		m_player[i].setHitCount(0);
	}
}

void Gameplay::setUpGame(int t_numPlayers)
{
	Platform m_plat(sf::Vector2f(0, 0), sf::Vector2f(0, 0), .2f);
	m_numberOfPlayers = t_numPlayers;

	for (int i = 0; i < m_numberOfPlatform; i++)
	{
		
		m_platforms.push_back(m_plat);

	}
	m_platforms[0].setColor(sf::Color::Yellow);
	m_platforms[1].setColor(sf::Color::Red);
	m_platforms[2].setColor(sf::Color::Blue);
	m_platforms[3].setColor(sf::Color::Green);

	for (int i = 0; i < m_numberOfPlayers; i++)
	{
		m_player.push_back(Player(m_controller[i]));
		m_player[i].loadContent();
		m_player[i].setScore(0);
	}
	if (t_numPlayers == 2)
	{
		m_player[0].setColour(sf::Color(255, 255, 255, 200));
		m_player[1].setColour(sf::Color(255, 0, 0, 200));
	}
	else if (t_numPlayers == 3)
	{
		m_player[0].setColour(sf::Color(255, 255, 255, 200));
		m_player[1].setColour(sf::Color(255, 0, 0, 200));
		m_player[2].setColour(sf::Color(200, 0, 255, 200));
	}
	else if (t_numPlayers == 4)
	{
		m_player[0].setColour(sf::Color(255, 255, 255, 200));
		m_player[1].setColour(sf::Color(255, 0, 0, 200));
		m_player[2].setColour(sf::Color(200, 0, 255, 200));
		m_player[3].setColour(sf::Color(255, 200, 0, 200));
	}
	

}




void Gameplay::render(sf::RenderWindow & t_window)
{
	
	if (m_gamestate == GameState::GAME_WIN)// if game paused 
	{
		t_window.draw(m_bgSprite);
		t_window.draw(m_winSprite);
		for (int i = 0; i < m_numberOfPlayers; i++)// for thenumber of players playing
		{
			m_player[i].render(t_window);//render a player 
		}
		t_window.draw(m_crownSprite);
	}
	if (m_gamestate == GameState::GAME_PAUSE)// if game paused 
	{
	
		t_window.draw(m_bgSprite);
		t_window.draw(m_pauseSprite);
		for (int i = 0; i < m_numberOfPlayers; i++)// for then umber of players playing
		{
			t_window.draw(m_pauseBar[i]);
			m_player[i].render(t_window);//render a player 
		}
		m_pause.render(t_window);//render
	}
	if (m_gamestate == GameState::GAME_RUNNING)
	{
		for (int i = 0; i < m_numberOfPlayers; i++)// for the number of players playing
		{
			m_player[i].render(t_window);//render a player 
			t_window.draw(m_winBar[i]);
			t_window.draw(m_playerSprite[i]);
			t_window.draw(m_uiSprite[i]);
			t_window.draw(m_playerDamageText[i]);
			
		}
		for (int i = 0; i < m_numberOfPlatform; i++)//render the amount of platforms in the game 
		{
			m_platforms[i].render(t_window);
		}
		t_window.draw(m_crownSprite);
	}
	if (m_gamestate == GameState::GAME_END)
	{
		t_window.draw(m_bgSprite);
		t_window.draw(m_winGameSprite);

		for (int i = 0; i < m_numberOfPlayers; i++)// for thenumber of players playing
		{
			m_player[i].render(t_window);//render a player 
		}
	}
}
void Gameplay::playMusic()
{
	CrowdBgMusic.play();
	m_fightStart.play();
}
void Gameplay::clearPlayers()
{
	m_player.clear();
	m_platforms.clear();
}
void Gameplay::getLeader()
{
	int topScore = 0;
	int score = 0;
	for (int i = 0; i < m_numberOfPlayers; i++)//loop through all the players 
	{
		m_winBar[i].setSize(m_winBarSize[m_player[i].getScore()]);
		m_winBar[i].setFillColor(m_screenColours[m_player[i].getScore()]);

		m_pauseBar[i].setSize(sf::Vector2f(50, -(100* m_player[i].getScore())));//bar for the pause screen 

		score = m_player[i].getScore();
		if (score > topScore)// check if player is alive
		{
			topScore = score;
			m_leaderId = m_player[i].getIndex();
		}

		if (m_player[i].getScore() >= 5)//if a players score at 5 wins 
		{
			for (int i = 0; i < m_numberOfPlayers; i++)//loop through players 
			{
				if (m_rankingDone == false)// only rank once
				{
					//sorting for placing players on  scale according to wins 
					if (m_player[i].getScore() == m_rank[0])
					{
						if (m_rankPlaced[0] == true)
						{
							if (m_rankPlacedAgain[0] == true)
							{
								m_player[i].position(sf::Vector2f(m_winPostion[0].x - 50, m_winPostion[0].y));
							}
							else
							{
								m_rankPlacedAgain[0] = true;
								m_player[i].position(sf::Vector2f(m_winPostion[0].x + 50, m_winPostion[0].y));
							}
						}
						else
						{
							m_rankPlaced[0] = true;
							m_player[i].position(m_winPostion[0]);
						}

					}
					else if (m_player[i].getScore() == m_rank[1])
					{
						if (m_rankPlaced[1] == true)
						{
							if (m_rankPlacedAgain[1] == true)
							{
								m_player[i].position(sf::Vector2f(m_winPostion[1].x - 50, m_winPostion[1].y));
							}
							else
							{
								m_rankPlacedAgain[1] = true;
								m_player[i].position(sf::Vector2f(m_winPostion[1].x + 50, m_winPostion[1].y));
							}
						}
						else
						{
							m_rankPlaced[1] = true;
							m_player[i].position(m_winPostion[1]);
						}
					}
					else if (m_player[i].getScore() == m_rank[2])
					{
						if (m_rankPlaced[2] == true)
						{
							if (m_rankPlacedAgain[2] == true)
							{
								m_player[i].position(sf::Vector2f(m_winPostion[2].x - 50, m_winPostion[2].y));
							}
							else
							{
								m_rankPlacedAgain[2] = true;
								m_player[i].position(sf::Vector2f(m_winPostion[2].x + 50, m_winPostion[2].y));
							}
						}
						else
						{
							m_rankPlaced[2] = true;
							m_player[i].position(m_winPostion[2]);
						}
					}
					else if (m_player[i].getScore() == m_rank[3])
					{
						if (m_rankPlaced[3] == true)
						{
							if (m_rankPlacedAgain[3] == true)
							{
								m_player[i].position(sf::Vector2f(m_winPostion[3].x - 50, m_winPostion[3].y));
							}
							else
							{
								m_rankPlacedAgain[3] = true;
								m_player[i].position(sf::Vector2f(m_winPostion[3].x + 50, m_winPostion[3].y));
							}
						}
						else
						{
							m_rankPlaced[3] = true;
							m_player[i].position(m_winPostion[3]);
						}
					}
					else if (m_player[i].getScore() == m_rank[4])
					{
						if (m_rankPlaced[4] == true)
						{
							if (m_rankPlacedAgain[4] == true)
							{
								m_player[i].position(sf::Vector2f(m_winPostion[4].x - 50, m_winPostion[4].y));
							}
							else
							{
								m_rankPlacedAgain[4] = true;
								m_player[i].position(sf::Vector2f(m_winPostion[4].x + 50, m_winPostion[4].y));
							}
						}
						else
						{
							m_rankPlaced[4] = true;
							m_player[i].position(m_winPostion[4]);
						}
					}
					m_winGameTimerStart = std::chrono::system_clock::now();//timer for how long the win game screen lasts 
					m_winGameTimerEnd = m_winGameTimerStart + std::chrono::milliseconds(3000);
				}

			}
			m_rankingDone = true;
			m_gamestate = GameState::GAME_END;
		}
	}
	
	

}
void Gameplay::checkControllerConnect(XBOXController controllers[])//check the controlers connected 
{
	for (int i = 0; i < m_numberOfPlayers; i++)// run for the amount of players in the game 
	{
		if (!controllers[i].isConnected())
		{
			if (controllers[i].connect(i))
			{
				std::cout << "Controller Connected: " << i << std::endl;
			}
		}
	}
}
bool Gameplay::checkPlayersAlive()
{
	
	int numAlive = m_numberOfPlayers;//set number to however many players there are 
	for (int i = 0; i < m_numberOfPlayers; i++)//loop through all the players 
	{
		if (m_player[i].checkAlive() == false)// check if player is alive
		{
			numAlive--;//if dead remove a player 
		}
	}
	if (numAlive <= 1)//if one player alive  end game 
	{
		CrowdBgMusic.stop();
		m_winSound.play();
		return true;
	}
	else
	{
		return false;
	}
}
