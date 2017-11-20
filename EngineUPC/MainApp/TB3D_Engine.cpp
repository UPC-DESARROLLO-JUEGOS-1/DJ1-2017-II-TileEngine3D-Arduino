#include "TB3D_Engine.h"
#include "TB3D_Game.h"
#include "TB3D_Configuration.h"

TB3D_Engine::TB3D_Engine(TB3D_Game* game, std::string identifier)
{
	mGame = game;
	mWorldConfig = TB3D_Configuration::GetInstance()->GetWorld(identifier);
	mTileSize = mWorldConfig->TileSize();

	mCamera = new TB3D_Camera(this);
	mPlayer = new TB3D_Player(this);
	mWorld = new TB3D_World(this);
}

TB3D_Engine::~TB3D_Engine()
{
	delete mCamera;
	delete mWorld;
	delete mPlayer;
}

void TB3D_Engine::Initialize() {
	mCamera->Initialize();
	mPlayer->Initialize();
	mWorld->Initialize();

	mCamera->FollowActor(mPlayer);
	// Set camera hard coded values for looking at player
	mCamera->GetRenderCamera()->SetRotationX(-0.8f);
	mCamera->SetOffset(0, -15.0f, 20.0f);
}

void TB3D_Engine::OnKeyDown(SDL_Keycode key) {
	mPlayer->OnKeyDown(key);
}

void TB3D_Engine::OnKeyUp(SDL_Keycode key) {
	mPlayer->OnKeyUp(key);
}

void TB3D_Engine::Update(float dt) {
	mCamera->Update(dt);
	mPlayer->Update(dt);
	mWorld->Update(dt);
}

void TB3D_Engine::Draw(float dt) {
	mPlayer->Draw(dt);
	mWorld->Draw(dt);
}
