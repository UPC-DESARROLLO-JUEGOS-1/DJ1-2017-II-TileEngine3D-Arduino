#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "BaseShader.h"
#include "BaseCamera.h"
#include "Vector3.h"
#include "NColor.h"
#include "NBaseDrawable.h"

class Drawable3D : public NBaseDrawable
{
public:
	Drawable3D();
	~Drawable3D();

	virtual Vector3 GetPosition() { return position; }
	virtual Vector3 GetScale() { return scale; }
	virtual Vector3 GetRotation() { return rotation; }

	virtual void SetX(float value)
	{
		position.x = value;
		needMatrixUpdate = true;
	}

	virtual void SetY(float value)
	{
		position.y = value;
		needMatrixUpdate = true;
	}

	virtual void SetZ(float value)
	{
		position.z = value;
		needMatrixUpdate = true;
	}

	virtual void SetScaleX(float value)
	{
		scale.x = value;
		needMatrixUpdate = true;
	}

	virtual void SetScaleY(float value)
	{
		scale.y = value;
		needMatrixUpdate = true;
	}

	virtual void SetScaleZ(float value)
	{
		scale.z = value;
		needMatrixUpdate = true;
	}

	virtual void SetRotationX(float value)
	{
		rotation.x = value;
		needMatrixUpdate = true;
	}

	virtual void SetRotationY(float value)
	{
		rotation.y = value;
		needMatrixUpdate = true;
	}

	virtual void SetRotationZ(float value)
	{
		rotation.z = value;
		needMatrixUpdate = true;
	}

	virtual void SetPosition(float x, float y, float z) {
		position.x = x;
		position.y = y;
		position.z = z;

		needMatrixUpdate = true;
	}

	virtual void Translate(float dx, float dy, float dz)
	{
		position.x += dx;
		position.y += dy;
		position.z += dz;
		needMatrixUpdate = true;
	}

	virtual void SetColor(NColor color) {
		mColor = color;
	}

	void SetRenderCamera(BaseCamera* renderCamera) { mRenderCamera = renderCamera; }

	void Initialize(float x, float y, float z);

	void Update(float dt)
	{
		if (needMatrixUpdate)
		{
			glm::mat4 result(1.0f);
			glm::vec3 translate(position.x, position.y, position.z);
			glm::vec3 scale(scale.x, scale.y, scale.z);
			
			result = glm::translate(result, translate);
			result = glm::scale(result, scale);
			result = glm::rotate(result, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			result = glm::rotate(result, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			result = glm::rotate(result, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			worldMatrix = result;
			needMatrixUpdate = false;
		}
	}

	void Draw(float dt)
	{

	}

protected:
	Vector3 position, scale, rotation;
	int mIndicesCount;

	GLuint mVBO_ID;
	GLuint mIBO_ID;
	NColor mColor;
};