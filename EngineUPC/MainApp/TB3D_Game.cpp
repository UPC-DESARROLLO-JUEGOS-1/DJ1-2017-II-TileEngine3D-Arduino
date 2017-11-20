#include "TB3D_Game.h"
#include "TB3D_Configuration.h"
#include <FrameworkUPC\BaseScene.h>

TB3D_Game::TB3D_Game(BaseScene* scene)
{
	mScene = scene;

	mEngine = new TB3D_Engine(this, "0");
}

TB3D_Game::~TB3D_Game()
{
	delete mEngine;
}

void TB3D_Game::Initialize() {
	mEngine->Initialize();
}

void TB3D_Game::OnKeyDown(SDL_Keycode key) {
	mEngine->OnKeyDown(key);
}

void TB3D_Game::OnKeyUp(SDL_Keycode key) {
	mEngine->OnKeyUp(key);
}

void TB3D_Game::Update(float dt) {
	mEngine->Update(dt);
}

void TB3D_Game::Draw(float dt) {
	mEngine->Draw(dt);
}
