#pragma once

#include "Drawable3D.h"

class NPrimitivePlane3D : public Drawable3D
{
public:
	NPrimitivePlane3D() { Drawable3D::Drawable3D(); }
	~NPrimitivePlane3D() { Drawable3D::~Drawable3D(); }

	inline float GetSizeX() { return mSizeX; }
	inline float GetSizeY() { return mSizeY; }

	void SetColor(NColor color);

	void Initialize(float x, float y, float z, float sizeX, float sizeY);
	void Draw(float dt);

private:
	float mSizeX, mSizeY;
};

