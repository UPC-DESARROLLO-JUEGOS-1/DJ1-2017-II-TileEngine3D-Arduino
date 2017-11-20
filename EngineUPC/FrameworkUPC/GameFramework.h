#pragma once

#include <functional>
#include "GameWindow.h"
#include "ShaderManager.h"
#include "ContentManager.h"
#include "NCameraManagment.h"
#include "SceneGraph.h"
#include "NLightManager.h"
#include "NGraphicDevice.h"

enum FrameworkState
{
	Running,
	Exit
};

class GameFramework
{
public:
	static GameFramework* GET_FRAMEWORK();
	GameFramework();
	~GameFramework();

	ContentManager* GetContentManager() { return &contentManager; }
	ShaderManager* GetShaderManager() { return &shaderManager; }
	NCameraManagment* GetCameraManagement() { return &mCameraManagement; }
	SceneGraph* GetSceneGraph() { return sceneGraph; }
	NLightManager* GetLightManager() { return &mLightManager; }
	NGraphicDevice* GetGraphicDevice() { return &mGraphicDevice; }

	int GetScreenWidth() { return screenWidth; }
	int GetScreenHeight() { return screenHeight; }

	void Initialize(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags);
	void SetFrameworkState(FrameworkState state) { frameworkState = state; };
	void SetCustomSceneGraph(SceneGraph* sceneGraph)
	{
		this->sceneGraph = sceneGraph;
		sceneGraph->Initialize();
	}
	void OnInput(std::function<void(SDL_Event)> onInput) { this->onInput = onInput; }
	void MainLoop(std::function<void(float)> onUpdate, std::function<void(float)> onDraw);
	void Update(float dt);
	void Draw(float dt);

private:
	static GameFramework* FRAMEWORK;

	int screenWidth, screenHeight;
	FrameworkState frameworkState;
	GameWindow window;
	ShaderManager shaderManager;
	ContentManager contentManager;
	NCameraManagment mCameraManagement;
	SceneGraph* sceneGraph;
	NLightManager mLightManager;
	NGraphicDevice mGraphicDevice;

	std::function<void(SDL_Event)> onInput = nullptr;
	std::function<void(float)> onUpdate = nullptr;
	std::function<void(float)> onDraw = nullptr;

	float ComputeDeltaTime();
	void OnListenInputsFromWindow(SDL_Event evnt);
};

