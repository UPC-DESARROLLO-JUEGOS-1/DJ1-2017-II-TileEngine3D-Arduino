#pragma once

#include <SDL\SDL.h>
#include <FrameworkUPC\Quad.h>

class BaseScene;

class TB3D_GameHud
{
public:
	TB3D_GameHud(BaseScene* scene);
	~TB3D_GameHud() {
		delete mScene;
	}

	void Initialize();
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);
	void Update(float dt);
	void Draw(float dt);
private:
	BaseScene* mScene;

	Quad* mQuad;

};

