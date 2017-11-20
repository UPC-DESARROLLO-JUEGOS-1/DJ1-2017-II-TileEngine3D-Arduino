#pragma once

#include <FrameworkUPC\BaseScene.h>
#include <FrameworkUPC\NTextfield2D.h>

class GameFontSystemScene : public BaseScene
{
public:
	GameFontSystemScene(SceneGraph* sceneGraph) :
		BaseScene::BaseScene(sceneGraph) {}
	~GameFontSystemScene() { BaseScene::~BaseScene(); }

	void Initialize();
	void Update(float dt);
	void Draw(float dt);

	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);

private:
	NTextfield2D mTextfield;
};

