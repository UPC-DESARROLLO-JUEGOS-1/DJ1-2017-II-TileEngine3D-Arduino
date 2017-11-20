#pragma once

#include "VertexData.h"

struct dtPositionNormalColorVertex
{
	V3 Position;
	V3 Normal;
	Color Color;

	void SetPosition(float x, float y, float z) {
		Position.x = x;
		Position.y = y;
		Position.z = z;
	}

	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		Color.r = r;
		Color.g = g;
		Color.b = b;
		Color.a = a;
	}

	void SetNormal(float x, float y, float z) {
		Normal.x = x;
		Normal.y = y;
		Normal.z = z;
	}

	void SetPositionAndColor(float x, float y, float z, GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		Position.x = x;
		Position.y = y;
		Position.z = z;
		Color.r = r;
		Color.g = g;
		Color.b = b;
		Color.a = a;
	}

	void static ProcessNormal(dtPositionNormalColorVertex* v1, dtPositionNormalColorVertex* v2, dtPositionNormalColorVertex* v3) {
		glm::vec3 vertex1 = glm::vec3(v1->Position.x, v1->Position.y, v1->Position.z);
		glm::vec3 vertex2 = glm::vec3(v2->Position.x, v2->Position.y, v2->Position.z);
		glm::vec3 vertex3 = glm::vec3(v3->Position.x, v3->Position.y, v3->Position.z);

		glm::vec3 edge1 = vertex2 - vertex1;
		glm::vec3 edge2 = vertex3 - vertex1;
		glm::vec3 cross = glm::cross(edge1, edge2);
		glm::vec3 normal = glm::normalize(cross);

		v1->SetNormal(normal.x, normal.y, normal.z);
		v2->SetNormal(normal.x, normal.y, normal.z);
		v3->SetNormal(normal.x, normal.y, normal.z);
	}
};