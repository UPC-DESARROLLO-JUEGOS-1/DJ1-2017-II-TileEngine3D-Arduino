#pragma once

#include "VertexData.h"

struct dtPositionTextureColor {
	V2 Vertex;
	V2 UV;
	Color Color;

	void SetVertex(float x, float y) {
		Vertex.x = x;
		Vertex.y = y;
	}

	void SetUV(float u, float v) {
		UV.x = u;
		UV.y = v;
	}

	void SetColor(NColor color) {
		Color.r = color.r;
		Color.g = color.g;
		Color.b = color.b;
		Color.a = color.a;
	}

	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		Color.r = r;
		Color.g = g;
		Color.b = b;
		Color.a = a;
	}
};