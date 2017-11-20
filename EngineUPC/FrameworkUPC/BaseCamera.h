#pragma once

#include <SDL\SDL.h>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

class BaseCamera
{
public:
	BaseCamera() :
		resultMatrix(1.0f),
		worldMatrix(1.0f),
		viewMatrix(1.0f),
		projectionMatrix(1.0f),
		needMatrixUpdate(true),
		x(0), y(0), z(0),
		scaleX(1), scaleY(1), scaleZ(1),
		rotationX(0), rotationY(0), rotationZ(0)
	{}
	~BaseCamera() {}

	bool IsKeyboardEnabled = false;
	bool IsMouseEnabled = false;

	void SetX(float value)
	{
		if (x != value)
		{
			x = value;
			float* worldMatrixPtr = glm::value_ptr(worldMatrix);
			*(worldMatrixPtr + 12) = value;
			needMatrixUpdate = true;
		}
	}

	void SetY(float value)
	{
		if (y != value)
		{
			y = value;
			float* worldMatrixPtr = glm::value_ptr(worldMatrix);
			*(worldMatrixPtr + 13) = value;
			needMatrixUpdate = true;
		}
	}

	void SetZ(float value)
	{
		if (z != value)
		{
			z = value;
			float* worldMatrixPtr = glm::value_ptr(worldMatrix);
			*(worldMatrixPtr + 14) = value;
			needMatrixUpdate = true;
		}
	}

	void SetPosition(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;

		float* worldMatrixPtr = glm::value_ptr(worldMatrix);
		*(worldMatrixPtr + 12) = x;
		*(worldMatrixPtr + 13) = y;
		*(worldMatrixPtr + 14) = z;

		needMatrixUpdate = true;
	}

	void SetPosition(float x, float y, float z, bool transformed) {
		this->x = x;
		this->y = y;
		this->z = z;

		if (transformed) {
			float* worldMatrixPtr = glm::value_ptr(worldMatrix);
			*(worldMatrixPtr + 12) = x;
			*(worldMatrixPtr + 13) = y;
			*(worldMatrixPtr + 14) = z;

			needMatrixUpdate = true;
		}
	}

	void SetScaleX(float value)
	{
		if (scaleX != value)
		{
			scaleX = value;
			float* worldMatrixPtr = glm::value_ptr(worldMatrix);
			*(worldMatrixPtr + 0) = value;
			needMatrixUpdate = true;
		}
	}

	void SetScaleY(float value)
	{
		if (scaleY != value)
		{
			scaleY = value;
			float* worldMatrixPtr = glm::value_ptr(worldMatrix);
			*(worldMatrixPtr + 5) = value;
			needMatrixUpdate = true;
		}
	}

	void SetScaleZ(float value)
	{
		if (scaleZ != value)
		{
			scaleZ = value;
			float* worldMatrixPtr = glm::value_ptr(worldMatrix);
			*(worldMatrixPtr + 10) = value;
			needMatrixUpdate = true;
		}
	}

	void SetRotationX(float value)
	{
		rotationX = value;
		needMatrixUpdate = true;
	}

	void SetRotationY(float value)
	{
		rotationY = value;
		needMatrixUpdate = true;
	}

	void SetRotationZ(float value)
	{
		rotationZ = value;
		needMatrixUpdate = true;
	}

	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }
	float GetScaleX() { return scaleX; }
	float GetScaleY() { return scaleY; }
	float GetScaleZ() { return scaleZ; }
	float GetRotationX() { return rotationX; }
	float GetRotationY() { return rotationY; }
	float GetRotationZ() { return rotationZ; }
	glm::mat4 GetResultMatrix() { return resultMatrix; }

	virtual void Initialize(int screenWidth, int screenHeight)
	{
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
	}

	virtual void OnKeyDown(SDL_Keycode key) {}
	virtual void OnKeyUp(SDL_Keycode key) {}
	virtual void OnMouseButtonUp(SDL_MouseButtonEvent buttonEvent) {}
	virtual void OnMouseButtonDown(SDL_MouseButtonEvent buttonEvent) {}
	virtual void OnMouseMotion(SDL_MouseMotionEvent mouseMotionEvent) {}

	virtual void Update(float dt)
	{
		if (needMatrixUpdate)
		{
			//resultMatrix = (worldMatrix*viewMatrix)*projectionMatrix;

			glm::mat4 result(1.0f);
			glm::vec3 translate(x, y, z);
			glm::vec3 scale(scaleX, scaleY, scaleZ);

			
			
			result = glm::rotate(result, rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
			result = glm::rotate(result, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
			result = glm::rotate(result, rotationZ, glm::vec3(0.0f, 0.0f, 1.0f));
			result = glm::scale(result, scale);
			result = glm::translate(result, translate);


			worldMatrix = result;

			resultMatrix = projectionMatrix * viewMatrix * worldMatrix;
			needMatrixUpdate = false;
		}
	}

	glm::vec3 rightInWorldSpace()
	{
		return glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
	}
	
	glm::vec3 upInWorldSpace()
	{
		return glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
	}

protected:
	int screenWidth, screenHeight;
	bool needMatrixUpdate;

	glm::mat4 resultMatrix;
	glm::mat4 worldMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	float x, y, z;
	float scaleX, scaleY, scaleZ;
	float rotationX, rotationY, rotationZ; //radians
};