#pragma once

#include "Camera3D.h"
#include "Vector2.h"
#include "Vector3.h"

class FPSCamera : public Camera3D
{
public:
	FPSCamera() { Camera3D::Camera3D(); }
	~FPSCamera() { Camera3D::~Camera3D(); }

	float LeftrightRot;
	float UpdownRot;

	void Initialize(int screenWidth, int screenHeight, float fov, float zNear, float zFar);
	
	void AddToCameraPosition(Vector3 vectorToAdd);
	void UpdateViewMatrix();

	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);
	void OnMouseButtonUp(SDL_MouseButtonEvent buttonEvent);
	void OnMouseButtonDown(SDL_MouseButtonEvent buttonEvent);
	void OnMouseMotion(SDL_MouseMotionEvent mouseMotionEvent);

	void Update(float dt);

private:
	const unsigned int Up = 0x00000001;
	const unsigned int Down = 0x00000010;
	const unsigned int Right = 0x00000100;
	const unsigned int Left = 0x00001000;
	const unsigned int Forward = 0x00010000;
	const unsigned int Backward = 0x00100000;

	Vector2 mOldMousePosition;
	float mRotationSpeed;
	bool mIsMouseUserPressed;
	unsigned int mDirectionsSwitches;
};

