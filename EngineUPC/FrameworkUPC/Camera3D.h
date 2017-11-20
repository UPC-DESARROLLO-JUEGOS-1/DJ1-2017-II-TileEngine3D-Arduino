#pragma once

#include "BaseCamera.h"

class Camera3D : public BaseCamera
{
public:
	Camera3D() { BaseCamera::BaseCamera(); }
	~Camera3D() { BaseCamera::~BaseCamera(); }

	void Initialize(int screenWidth, int screenHeight, float fov, float zNear, float zFar);
	void Update(float dt);

private:
	glm::vec3 mCameraPosition;
};

