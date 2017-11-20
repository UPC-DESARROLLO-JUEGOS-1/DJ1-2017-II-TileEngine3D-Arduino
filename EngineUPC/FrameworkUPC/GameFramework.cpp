#include "GameFramework.h"
#include "Camera2D.h"
#include <SDL\SDL.h>
#include <iostream>
#include <time.h>

GameFramework* GameFramework::FRAMEWORK;
GameFramework* GameFramework::GET_FRAMEWORK() { return FRAMEWORK; }

GameFramework::GameFramework():
	screenWidth(0),
	screenHeight(0),
	frameworkState(FrameworkState::Running),
	shaderManager(this),
	contentManager(this),
	mCameraManagement(this),
	mLightManager(this),
	mGraphicDevice(this)
{
	GameFramework::FRAMEWORK = this;
	srand(time(NULL));
}

GameFramework::~GameFramework(){}

void GameFramework::Initialize(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	window.Create(windowName, screenWidth, screenHeight, windowFlags);
	window.AddInputListener(std::bind(&GameFramework::OnListenInputsFromWindow, 
		this, std::placeholders::_1));

	mGraphicDevice.Initialize(screenWidth, screenHeight);
	shaderManager.Initialize();
	contentManager.Initialize();
	mCameraManagement.Initialize();
	mLightManager.Initialize();

	sceneGraph = new SceneGraph();
	sceneGraph->Initialize();
}

void GameFramework::MainLoop(std::function<void(float)> onUpdate, std::function<void(float)> onDraw)
{
	this->onUpdate = onUpdate;
	this->onDraw = onDraw;

	while (frameworkState != FrameworkState::Exit)
	{
		float deltaTime = ComputeDeltaTime();
		window.Update(deltaTime);
		Update(deltaTime);
		Draw(deltaTime);
	}
}

void GameFramework::Update(float dt)
{
	mGraphicDevice.Update(dt);
	mCameraManagement.Update(dt);
	sceneGraph->Update(dt);
	onUpdate(dt);
}

void GameFramework::Draw(float dt)
{
	mGraphicDevice.Draw(dt);
	sceneGraph->Draw(dt);
	onDraw(dt);
	window.Present();
}

float GameFramework::ComputeDeltaTime()
{
	float deltaTime = 0.0f;

	static float previousTick = SDL_GetTicks();
	float currentTick = SDL_GetTicks();

	deltaTime = currentTick - previousTick;
	previousTick = currentTick;

	return deltaTime*0.001f;
}

void GameFramework::OnListenInputsFromWindow(SDL_Event evnt)
{
	if (onInput != nullptr)
	{
		onInput(evnt);
	}

	switch (evnt.type)
	{
		case SDL_QUIT:
			frameworkState = FrameworkState::Exit;
			break;
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			mCameraManagement.OnMouseEvent(evnt.type, evnt.button, evnt.motion);
			break;
		case SDL_KEYDOWN:
			mCameraManagement.OnKeyDown(evnt.key.keysym.sym);
			sceneGraph->OnKeyDown(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			mCameraManagement.OnKeyUp(evnt.key.keysym.sym);
			sceneGraph->OnKeyUp(evnt.key.keysym.sym);
			break;
		default:
			break;
	}
}
