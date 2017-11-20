#pragma once

#include <FrameworkUPC\NPrimitiveCube3D.h>
#include <FrameworkUPC\Vector2.h>

class TB3D_Engine;

class TB3D_Actor
{
public:
	bool CanGoUpLeft;
	bool CanGoDownLeft;
	bool CanGoUpRight;
	bool CanGoDownRight;

	int TileDownY;
	int TileUpY;
	int TileLeftX;
	int TileRightX;

	virtual float GetX() { return mX; }
	virtual void SetX(float val) { mX = val; }

	virtual float GetY() { return mY; }
	virtual void SetY(float val) { mY = val; }

	virtual float GetZ() { return mZ; }
	virtual void SetZ(float val) { mZ = val; }

	void SetPosition(float x, float y, float z) {
		mX = x;
		mY = y;
		mZ = z;
	}

	inline TB3D_Engine* GetEngine() { return mEngine; }
	inline NPrimitiveCube3D* GetCollisionCube() { return mCollisionCube; }

	TB3D_Actor() {}
	TB3D_Actor(TB3D_Engine* engine);
	~TB3D_Actor();

	virtual void Initialize();
	virtual void CreateCollision(float size);
	Vector2 ComputeNewPosition(float speed, float directionX, float directionY);
	virtual void Update(float dt);
	virtual void Draw(float dt);

protected:
	float mX;
	float mY;
	float mZ;
	float mOffsetX;
	float mOffsetY;
	float mOffsetZ;
	float mTileWidth;
	float mTileHeight;

	bool mDebugMode;

	TB3D_Engine* mEngine;
	NPrimitiveCube3D* mCollisionCube;
};

