#ifndef XBOX_CONTROLLER_
#define XBOX_CONTROLLER_

#include <SFML/Graphics.hpp>
#include <iostream>

/// <summary>
/// data to store the current state of the controller
/// </summary>
struct GamePadState
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadLeft;
	bool DpadRight;
	bool Start;
	bool Back;
	bool Xbox;
	float Rtrigger;
	float Ltrigger;
	
	sf::Vector2f RightThumbStick;
	sf::Vector2f LeftThumbStick;

};

/// <summary>
/// Xbox controller class to query current state of the controller
/// to mimic the controller states like XNA
/// </summary>
class XBOXController
{
private:
	

public:

	//deadzone for the dpad
	const int dPadThreshold = 50;
	//index count for multiple controllers if connected
	int sf_Joystick_index;
	//the current state of all the buttons
	GamePadState m_currentState;
	//the previous state to use to check for the moment a button is pressed
	GamePadState m_previousState;

	
	XBOXController();
	~XBOXController();
	void update();
	bool isConnected();
	bool connect(int t_index);
};

#endif