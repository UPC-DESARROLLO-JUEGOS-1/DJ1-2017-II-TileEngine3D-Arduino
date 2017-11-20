#pragma once

#pragma once

#include "BaseShader.h"

class FontShader : public BaseShader
{
public:
	FontShader() { BaseShader::BaseShader(); }
	~FontShader() { BaseShader::~BaseShader(); }

protected:
	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexUV");
		AddAttribute("vertexColor");
	}
};