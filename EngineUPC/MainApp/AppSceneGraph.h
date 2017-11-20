#pragma once

#include <FrameworkUPC\SceneGraph.h>

#include "EnumAppScenes.h"
#include "GameScene.h"
#include "Game3DScene.h"
#include "GameFontSystemScene.h"
#include "GameTile3DEngineScene.h"

class AppSceneGraph : public SceneGraph
{
public:
	AppSceneGraph() { SceneGraph::SceneGraph(); }
	~AppSceneGraph() { SceneGraph::~SceneGraph(); }

	void GoToScene(int sceneId)
	{
		if (currentScene != nullptr) {
			delete currentScene;
		}

		BaseScene* result = nullptr;

		switch (sceneId)
		{
			case EnumAppScenes::MainMenu:
				break;
			case EnumAppScenes::Game:
				result = new GameScene(this);
				break;
			case EnumAppScenes::GameOver:
				break;
			case EnumAppScenes::Game3D:
				result = new Game3DScene(this);
				break;
			case EnumAppScenes::GameFontSystem:
				result = new GameFontSystemScene(this);
				break;
			case EnumAppScenes::GameTile3DEngine:
				result = new GameTile3DEngineScene(this);
				break;
		}

		if (result != nullptr)
		{
			SceneGraph::GoToScene(sceneId);
			result->Initialize();
		}

		currentScene = result;
	}
};

