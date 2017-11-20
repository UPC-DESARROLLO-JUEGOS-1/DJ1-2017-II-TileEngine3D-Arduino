#pragma once

#include <SDL\SDL_keycode.h>
#include "TB3D_Camera.h"

#include <FrameworkUPC\ArduinoSerial.h>

class TB3D_Player;

class TB3D_PlayerControl
{
public:
	TB3D_PlayerControl(TB3D_Player* player);
	~TB3D_PlayerControl();

	void Initialize();
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);
	void OnJoystickEvent(dtArduinoJoystick data);
	void Update(float dt);

private:
	TB3D_Player* mPlayer;

	bool mCanGoLeft;
	bool mCanGoRight;
	bool mCanGoForward;
	bool mCanGoBackward;

	float mPlayerSpeed;

	int mDirectionX;
	int mDirectionY;

	Vector3 mDebugRotation;

	ArduinoSerial* mArduinoSerial;
};

