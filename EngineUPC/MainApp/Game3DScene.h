#pragma once

#include <FrameworkUPC\BaseScene.h>
#include <FrameworkUPC\NPrimitiveCube3D.h>
#include <FrameworkUPC\NStaticModel3D.h>
#include "GunboundGameApp.h"

class Game3DScene : public BaseScene
{
public:
	Game3DScene(SceneGraph* sceneGraph) :
		BaseScene::BaseScene(sceneGraph) {}
	~Game3DScene() {}

	void Initialize();
	void Update(float dt);
	void Draw(float dt);

	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);

private:
	NPrimitiveCube3D mCube;
	NStaticModel3D mStaticModel;
};

