#pragma once

#include <GL\glew.h>

struct V2
{
	float x;
	float y;
};

struct V3
{
	float x;
	float y;
	float z;
};

struct V4
{
	float x;
	float y;
	float z;
	float w;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV
{
	float u;
	float v;
};
