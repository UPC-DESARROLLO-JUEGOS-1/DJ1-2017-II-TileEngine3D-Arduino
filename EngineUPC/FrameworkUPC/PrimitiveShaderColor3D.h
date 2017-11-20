#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"

class PrimitiveShaderColor3D : public BaseShader
{
public:
	PrimitiveShaderColor3D() { BaseShader::BaseShader(); }
	~PrimitiveShaderColor3D() { BaseShader::~BaseShader(); }

protected:
	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexColor");
	}
};

