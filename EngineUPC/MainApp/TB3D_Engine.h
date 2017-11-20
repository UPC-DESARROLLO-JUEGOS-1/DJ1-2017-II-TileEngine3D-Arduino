#pragma once

#include "TB3D_World.h"
#include "TB3D_Camera.h"
#include "TB3D_Player.h"
#include "TB3D_WorldConfig.h"

#include <SDL\SDL_keycode.h>

class TB3D_Game;

class TB3D_Engine
{
public:
	TB3D_Engine(TB3D_Game* game, std::string identifier);
	~TB3D_Engine();

	TB3D_Camera* GetCamera() { return mCamera; }
	TB3D_Player* GetPlayer() { return mPlayer; }
	TB3D_World* GetWorld() { return mWorld; }
	TB3D_WorldConfig* GetWorldConfig() { return mWorldConfig; }

	float GetTileSize() { return mTileSize; }

	void Initialize();
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);
	void Update(float dt);
	void Draw(float dt);

private:
	TB3D_Game* mGame;
	TB3D_World* mWorld;
	TB3D_Camera* mCamera;
	TB3D_Player* mPlayer;

	TB3D_WorldConfig* mWorldConfig;

	float mTileSize;
};

