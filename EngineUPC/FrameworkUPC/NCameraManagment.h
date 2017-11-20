#pragma once

#include "BaseCamera.h"
#include "Camera2D.h"
#include "Camera3D.h"
#include "FPSCamera.h"
#include <map>
#include <string>

class GameFramework;

class NCameraManagment
{
public:
	NCameraManagment(GameFramework* framework) :
		mCurrentCamera(nullptr)
	{
		mFramework = framework;
	}
	~NCameraManagment();

	BaseCamera* GetCurrentCamera() { return mCurrentCamera; }

	Camera2D* CreateCamera2D(int screenWidth, int screenHeight);
	Camera3D* CreateCamera3D(int screenWidth, int screenHeight, float fov, float zNear, float zFar);
	FPSCamera* CreateFPSCamera(int screenWidth, int screenHeight, float fov, float zNear, float zFar);

	void Initialize();

	void OnKeyDown(SDL_Keycode key) {
		if (mCurrentCamera != nullptr && mCurrentCamera->IsKeyboardEnabled) {
			mCurrentCamera->OnKeyDown(key);
		}
	}

	void OnKeyUp(SDL_Keycode key) {
		if (mCurrentCamera != nullptr && mCurrentCamera->IsKeyboardEnabled) {
			mCurrentCamera->OnKeyUp(key);
		}
	}

	void OnMouseEvent(Uint32 eventType, SDL_MouseButtonEvent buttonEvent,
		SDL_MouseMotionEvent mouseMotionEvent) {

		if (mCurrentCamera != nullptr && mCurrentCamera->IsMouseEnabled) {
			switch (eventType)
			{
			case SDL_MOUSEMOTION:
				mCurrentCamera->OnMouseMotion(mouseMotionEvent);
				break;
			case SDL_MOUSEBUTTONUP:
				mCurrentCamera->OnMouseButtonUp(buttonEvent);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mCurrentCamera->OnMouseButtonDown(buttonEvent);
				break;
			}
		}
	}

	void SaveCamera(std::string name, BaseCamera* camera);
	BaseCamera* GetCamera(std::string name);
	void SetCurrentCamera(BaseCamera* camera) { mCurrentCamera = camera; }
	void Update(float dt);

private:
	std::map<std::string, BaseCamera*> mCameras;

	BaseCamera* mCurrentCamera;
	GameFramework* mFramework;
};