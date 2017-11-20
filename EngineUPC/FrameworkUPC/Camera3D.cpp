#include "Camera3D.h"

#define PI 3.14159265
#define PiOver4 PI / 4.0f;

void Camera3D::Initialize(int screenWidth, int screenHeight, float fov, float zNear, float zFar)
{
	BaseCamera::Initialize(screenWidth, screenHeight);

	float aspectRatio = (float)screenWidth / (float)screenHeight;

	z = -5.0f;

	glm::vec3 lookAt(x, y, z);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
	viewMatrix = glm::lookAt(lookAt, center, up);
}

void Camera3D::Update(float dt)
{
	BaseCamera::Update(dt);
}
