#ifndef PLAYER_
#define PLAYER_

#include "XBOXController.h"
#include "ScreenSize.h"
#include <chrono>
#include <thread>
#include <math.h>

class Player
{
	
public:


	Player(XBOXController&t_controller);
	ScreenSize screen;

	int getIndex();

	void update(sf::Time t_dTime);
	void render(sf::RenderWindow &t_window);	

	void position(sf::Vector2f t_pos);
	sf::Vector2f position();

	sf::Vector2f previousPostion();

	void velocity(sf::Vector2f t_vel);
	sf::Vector2f velocity();

	void FistVelocity(sf::Vector2f t_velocity);
	sf::Vector2f FistVelocity();

	void size(sf::Vector2f t_size);
	sf::Vector2f size();

	void mass(float t_mass);
	void speed(float t_speed);

	bool getPunch();
	void setPunch(bool t_state);

	void setHit(int t_state);
	int GetHit();
	
	void setHitCount(int t_timesHit);

	void HitDectionPlatform(sf::Time t_dTime, sf::Vector2f m_platformPosition, sf::Vector2f m_platformSize);
	int HitDectionPlayer(sf::Time t_dTime, sf::Vector2f m_PlayerPosition, sf::Vector2f m_PlayerSize);
	void startHitTimer();

	void setAlive(bool tState);
	bool checkAlive();
	
	void setColour(sf::Color t_color);

	void addScore(int t_point);
	void setScore(int t_score);
	int getScore();
	int getdDameage();


	void loadContent();

	void checkForEmote();
	void moveEmote();
	void emote(sf::RenderWindow & t_window);
	void drawEmote(sf::RenderWindow & t_window);


	void Punch();

	void jump(sf::Time t_dTime);

	
private:

	int m_score;
	float gravity = 19.8f; 
	int JumpCount;


	int m_emote;

	bool HitDetectV = false;
	bool HitDetectH = false;

	XBOXController * m_controller;

	bool DirectionLR;//direction bool for fist 

	sf::Texture m_bodyTexture;
	sf::Sprite m_bodySprite;

	std::chrono::time_point<std::chrono::system_clock> m_jumpStart;
	std::chrono::time_point<std::chrono::system_clock> m_jumpEnd;


	std::chrono::time_point<std::chrono::system_clock> m_hitStart;
	std::chrono::time_point<std::chrono::system_clock> m_hitEnd;

	//**variabules to do with emotes 

	sf::Texture m_angerEmoteTexture;
	sf::Texture m_loveEmoteTexture;
	sf::Texture m_curesEmoteTexture;
	sf::Texture m_skullEmotetexture;

	sf::Sprite m_angerEmoteSprite;
	sf::Sprite m_loveEmoteSprite;
	sf::Sprite m_curesEmoteSprite;
	sf::Sprite m_skullEmoteSprite;

	std::chrono::time_point<std::chrono::system_clock> m_emoteStart;
	std::chrono::time_point<std::chrono::system_clock> m_emoteEnd;
	bool m_emoteUsed;

	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	sf::Vector2f m_previousPosition;
	sf::Vector2f m_size;
	float m_speed;
	float m_mass;

	int playerHit;
	bool PunchThrown;


	bool FistHitDetectV;
	bool FistHitDetectH;

	sf::Texture m_fistTexture;
	sf::Sprite m_fistSprite;
	

	sf::Vector2f m_FistPosition;
	sf::Vector2f m_FistVelocity;
	sf::Vector2f m_FistSize;
	sf::Vector2f m_FistForce;
	sf::Vector2f m_HitForce;
	

	std::chrono::time_point<std::chrono::system_clock> m_punchStart;
	std::chrono::time_point<std::chrono::system_clock> m_punchEnd;

	float m_timesHit;

	bool m_playerAlive;
	float distance;
	sf::Vector2f direction;

	void checkInBounds();





};

#endif