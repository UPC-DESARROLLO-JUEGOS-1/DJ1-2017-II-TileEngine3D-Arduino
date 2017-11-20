#pragma once

#include <FrameworkUPC\BaseScene.h>
#include "TB3D_Game.h"
#include "TB3D_GameHud.h"

class GameTile3DEngineScene : public BaseScene
{
public:
	GameTile3DEngineScene(SceneGraph* sceneGraph) :
		BaseScene::BaseScene(sceneGraph) {

		mGame = new TB3D_Game(this);
		mGameHud = new TB3D_GameHud(this);
	}

	~GameTile3DEngineScene() {
		delete mGame;
		delete mGameHud;
	}

	TB3D_Game* GetGame() { return mGame; }
	TB3D_GameHud* GetGameHud() { return mGameHud; }

	void Initialize();
	void Update(float dt);
	void Draw(float dt);

	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);

private:
	TB3D_Game* mGame;
	TB3D_GameHud* mGameHud;
};

