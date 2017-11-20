#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"

class PrimitiveShader3D : public BaseShader
{
public:
	PrimitiveShader3D() { BaseShader::BaseShader(); }
	~PrimitiveShader3D() { BaseShader::~BaseShader(); }

protected:
	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexNormal");
	}
};

