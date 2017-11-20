#include "Drawable3D.h"

Drawable3D::Drawable3D() :
	mVBO_ID(0), mIBO_ID(0),
	mIndicesCount(0),
	position(0.0f, 0.0f, 0.0f),
	scale(1.0f, 1.0f, 1.0f),
	rotation(0.0f, 0.0f, 0.0f),
	mColor(NColor::White) { }

Drawable3D::~Drawable3D()
{
	if (mVBO_ID != 0) {
		glDeleteBuffers(1, &mVBO_ID);
	}

	if (mIBO_ID != 0) {
		glDeleteBuffers(1, &mIBO_ID);
	}
}

void Drawable3D::Initialize(float x, float y, float z)
{
	position = Vector3(x, y, z);

	if (mVBO_ID == 0)
	{
		glGenBuffers(1, &mVBO_ID);
	}

	if (mIBO_ID == 0) {
		glGenBuffers(1, &mIBO_ID);
	}
}
