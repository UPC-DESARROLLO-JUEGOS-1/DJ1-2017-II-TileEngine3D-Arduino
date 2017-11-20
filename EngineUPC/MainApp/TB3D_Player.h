#pragma once

#include "TB3D_Actor.h"
#include "TB3D_PlayerControl.h"

#include <SDL\SDL_keycode.h>

class TB3D_Engine;

class TB3D_Player : public TB3D_Actor
{
public:
	TB3D_Player(TB3D_Engine* engine);
	~TB3D_Player();

	void CreateCollision(float size);

	virtual void Initialize();

	virtual void OnKeyDown(SDL_Keycode key) { mPlayerControl->OnKeyDown(key); }
	virtual void OnKeyUp(SDL_Keycode key) { mPlayerControl->OnKeyUp(key); }

	virtual void Update(float dt);
	virtual void Draw(float dt);

private:
	TB3D_PlayerControl* mPlayerControl;
};

