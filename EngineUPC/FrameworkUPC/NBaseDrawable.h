#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "BaseShader.h"
#include "BaseCamera.h"

class NBaseDrawable
{
public:
	NBaseDrawable();
	~NBaseDrawable();

	virtual void Update(float dt) {}
	virtual void Draw(float dt) {}

protected:
	glm::mat4 worldMatrix;
	bool needMatrixUpdate;

	BaseShader* mCurrentShader;
	BaseCamera* mRenderCamera;
};

