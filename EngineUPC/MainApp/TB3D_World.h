#pragma once

#include <vector>

#include <FrameworkUPC\NPrimitiveCube3D.h>
#include <FrameworkUPC\NPrimitivePlane3D.h>

#include "TB3D_WorldPhysics.h"

class TB3D_Engine;

class TB3D_World
{
public:
	static const int TILE_EMPTY;
	static const int TILE_BLOCK;
	static const int TILE_PLAYER;
	static const int TB3D_World::TILE_HOUSE_3D;

	float GetTileSize() { return mTileSize; }
	TB3D_Engine* GetEngine() { return mEngine; }
	TB3D_WorldPhysics* GetWorldPhysics() { return mWorldPhysics; }

	TB3D_World(TB3D_Engine* engine);
	~TB3D_World();

	void Initialize();
	void Update(float dt);
	void Draw(float dt);

private:
	float mTileSize;

	TB3D_Engine* mEngine;
	TB3D_WorldPhysics* mWorldPhysics;

	NPrimitivePlane3D* mPlane;

	std::vector<NBaseDrawable*> mDrawables;

	void CreateObject(int tileID, int c, int r);
};

