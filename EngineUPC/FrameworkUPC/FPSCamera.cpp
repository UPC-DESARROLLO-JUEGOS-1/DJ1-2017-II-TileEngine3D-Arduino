#include "FPSCamera.h"

void FPSCamera::Initialize(int screenWidth, int screenHeight, float fov, float zNear, float zFar) {
	BaseCamera::IsKeyboardEnabled = true;
	BaseCamera::IsMouseEnabled = true;

	Camera3D::Initialize(screenWidth, screenHeight, fov, zNear, zFar);

	// Initialize
	mDirectionsSwitches = 0;
	mRotationSpeed = 0.005;
	mIsMouseUserPressed = false;
	LeftrightRot = 0;
	UpdownRot = 0;
	mOldMousePosition = Vector2::Zero;
}

void FPSCamera::OnKeyDown(SDL_Keycode key) {
	switch (key) {
	case SDLK_w: mDirectionsSwitches |= FPSCamera::Up;			break;
	case SDLK_s: mDirectionsSwitches |= FPSCamera::Down;		break;
	case SDLK_d: mDirectionsSwitches |= FPSCamera::Right;		break;
	case SDLK_a: mDirectionsSwitches |= FPSCamera::Left;		break;
	case SDLK_q: mDirectionsSwitches |= FPSCamera::Forward;		break;
	case SDLK_z: mDirectionsSwitches |= FPSCamera::Backward;	break;
	}
}

void FPSCamera::OnKeyUp(SDL_Keycode key) {
	switch (key) {
	case SDLK_w: mDirectionsSwitches ^= FPSCamera::Up;          break;
	case SDLK_s: mDirectionsSwitches ^= FPSCamera::Down;        break;
	case SDLK_d: mDirectionsSwitches ^= FPSCamera::Right;       break;
	case SDLK_a: mDirectionsSwitches ^= FPSCamera::Left;        break;
	case SDLK_q: mDirectionsSwitches ^= FPSCamera::Forward;     break;
	case SDLK_z: mDirectionsSwitches ^= FPSCamera::Backward;    break;
	}
}

void FPSCamera::OnMouseButtonUp(SDL_MouseButtonEvent buttonEvent) {
	mIsMouseUserPressed = false;
}

void FPSCamera::OnMouseButtonDown(SDL_MouseButtonEvent buttonEvent) {
	mIsMouseUserPressed = true;

	mOldMousePosition.x = buttonEvent.x;
	mOldMousePosition.y = buttonEvent.y;
}

void FPSCamera::OnMouseMotion(SDL_MouseMotionEvent mouseMotionEvent) {
	if (mIsMouseUserPressed) {
		
		float xDifference = mouseMotionEvent.x - mOldMousePosition.x;
		float yDifference = mouseMotionEvent.y - mOldMousePosition.y;

		LeftrightRot -= mRotationSpeed * xDifference;
		UpdownRot -= mRotationSpeed * yDifference;

		mOldMousePosition.x = mouseMotionEvent.x;
		mOldMousePosition.y = mouseMotionEvent.y;
	}
}

void FPSCamera::AddToCameraPosition(Vector3 vectorToAdd) {
	float moveSpeed = 0.5f;
	
	glm::mat4 cameraRotation(1.0f);
	cameraRotation = glm::rotate(cameraRotation, UpdownRot, glm::vec3(1.0f, 0.0f, 0.0f));
	cameraRotation = glm::rotate(cameraRotation, LeftrightRot, glm::vec3(0.0f, 1.0f, 0.0f));
	
	Vector3 rotatedVector = Vector3::Transform(vectorToAdd, cameraRotation);

	this->x += moveSpeed * rotatedVector.x;
	this->y += moveSpeed * rotatedVector.y;
	this->z += moveSpeed * rotatedVector.z;

	//SetPosition(this->x, this->y, this->z);
}

void FPSCamera::UpdateViewMatrix() {
	glm::mat4 cameraRotation(1.0f);
	cameraRotation = glm::rotate(cameraRotation, UpdownRot, glm::vec3(1.0f, 0.0f, 0.0f));
	cameraRotation = glm::rotate(cameraRotation, LeftrightRot, glm::vec3(0.0f, 1.0f, 0.0f));

	Vector3 cameraOriginalTarget = Vector3::Zero;
	cameraOriginalTarget.z = 1;

	Vector3 cameraOriginalUpVector = Vector3::UnitY;
	Vector3 cameraPosition = Vector3(x, y, z);

	Vector3 cameraRotatedTarget = Vector3::Transform(cameraOriginalTarget, cameraRotation);
	Vector3 cameraFinalTarget = cameraPosition + cameraRotatedTarget;

	Vector3 cameraRotatedUpVector = Vector3::Transform(cameraOriginalUpVector, cameraRotation);
	//Vector3 cameraFinalUpVector = cameraPosition + cameraRotatedUpVector;

	// Now convert to a format that GLM can read
	glm::vec3 glm_cameraPosition;
	glm_cameraPosition.x = cameraPosition.x;
	glm_cameraPosition.y = cameraPosition.y;
	glm_cameraPosition.z = cameraPosition.z;

	glm::vec3 glm_cameraFinalTarget;
	glm_cameraFinalTarget.x = cameraFinalTarget.x;
	glm_cameraFinalTarget.y = cameraFinalTarget.y;
	glm_cameraFinalTarget.z = cameraFinalTarget.z;

	glm::vec3 glm_cameraRotatedUpVector;
	glm_cameraRotatedUpVector.x = cameraRotatedUpVector.x;
	glm_cameraRotatedUpVector.y = cameraRotatedUpVector.y;
	glm_cameraRotatedUpVector.z = cameraRotatedUpVector.z;

	viewMatrix = glm::lookAt(glm_cameraPosition, glm_cameraFinalTarget, 
		glm_cameraRotatedUpVector);
}

void FPSCamera::Update(float dt) {
	if ((mDirectionsSwitches & FPSCamera::Up) == FPSCamera::Up) { this->AddToCameraPosition(Vector3::Up); }
	if ((mDirectionsSwitches & FPSCamera::Down) == FPSCamera::Down) { this->AddToCameraPosition(Vector3::Down); }
	if ((mDirectionsSwitches & FPSCamera::Left) == FPSCamera::Left) { this->AddToCameraPosition(Vector3::Left); }
	if ((mDirectionsSwitches & FPSCamera::Right) == FPSCamera::Right) { this->AddToCameraPosition(Vector3::Right); }
	if ((mDirectionsSwitches & FPSCamera::Forward) == FPSCamera::Forward) { this->AddToCameraPosition(Vector3::Forward); }
	if ((mDirectionsSwitches & FPSCamera::Backward) == FPSCamera::Backward) { this->AddToCameraPosition(Vector3::Backward); }

	UpdateViewMatrix();

	resultMatrix = projectionMatrix * viewMatrix * worldMatrix;

	/*if (needMatrixUpdate)
	{
		UpdateViewMatrix();

		resultMatrix = projectionMatrix * viewMatrix * worldMatrix;
		needMatrixUpdate = false;
	}*/
}