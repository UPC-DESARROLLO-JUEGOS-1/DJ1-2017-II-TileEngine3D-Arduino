#pragma once

#include <FrameworkUPC\Camera3D.h>;
#include "TB3D_Actor.h"

class TB3D_Engine;

class TB3D_Camera
{
public:
	TB3D_Camera(TB3D_Engine* engine);
	~TB3D_Camera();

	Camera3D* GetRenderCamera() { return mRenderCamera; }

	void Initialize();
	void SetOffset(float x, float y, float z) {
		mOffsetX = x;
		mOffsetY = y;
		mOffsetZ = z;
	}
	void FollowActor(TB3D_Actor* actor) { mActor = actor; }
	void Update(float dt);

private:
	float mOffsetX, mOffsetY, mOffsetZ;

	TB3D_Actor* mActor;
	TB3D_Engine* mEngine;
	Camera3D* mRenderCamera;
};

