#pragma once

#include "TB3D_Engine.h"

class BaseScene;

class TB3D_Game
{
public:
	TB3D_Game(BaseScene* scene);
	~TB3D_Game();

	void Initialize();
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);
	void Update(float dt);
	void Draw(float dt);

private:
	TB3D_Engine* mEngine;
	BaseScene* mScene;
};

