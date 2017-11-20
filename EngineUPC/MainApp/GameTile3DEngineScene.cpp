#include "GameTile3DEngineScene.h"
#include <FrameworkUPC\GameFramework.h>

void GameTile3DEngineScene::Initialize()
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();

	// inicializamos en 3D
	framework->GetGraphicDevice()->ChangeTo3D();
	mGame->Initialize();

	// inicializamos 2D
	framework->GetGraphicDevice()->ChangeTo2D();
	mGameHud->Initialize();
}

void GameTile3DEngineScene::OnKeyDown(SDL_Keycode key)
{
	mGame->OnKeyDown(key);
	mGameHud->OnKeyDown(key);
}

void GameTile3DEngineScene::OnKeyUp(SDL_Keycode key)
{
	mGame->OnKeyUp(key);
	mGameHud->OnKeyUp(key);
}

void GameTile3DEngineScene::Update(float dt)
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	
	// actualizamos 3D
	framework->GetGraphicDevice()->ChangeTo3D();
	mGame->Update(dt);

	// actualizamos 2D
	framework->GetGraphicDevice()->ChangeTo2D();
	mGameHud->Update(dt);
}

void GameTile3DEngineScene::Draw(float dt)
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();

	// dibujamos 3D
	framework->GetGraphicDevice()->ChangeTo3D();
	mGame->Draw(dt);

	// dibujamos 2D
	framework->GetGraphicDevice()->ChangeTo2D();
	mGameHud->Draw(dt);
}
