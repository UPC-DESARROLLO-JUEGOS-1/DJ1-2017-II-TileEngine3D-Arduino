#include "TB3D_WorldPhysics.h"
#include "TB3D_World.h"
#include "TB3D_Actor.h"
#include "TB3D_Engine.h"

TB3D_WorldPhysics::TB3D_WorldPhysics(TB3D_World* world)
{
	mWorld = world;
}

void TB3D_WorldPhysics::Initialize(std::vector<std::vector<int>> collisionData) 
{
	mCollisionData = collisionData;

	mEngine = mWorld->GetEngine();
	mTileSize = mEngine->GetTileSize();
}

void TB3D_WorldPhysics::GetCorners(float size, float x, float y, TB3D_Actor* actor) {
	float cubeSize = size;
	float offsetSize = 0.1f; // don't move this, is a constant

	int tileX = (int)floorf(x / mTileSize);
	int tileY = (int)floorf(y / mTileSize);

	actor->TileDownY = (int)floorf((y + cubeSize - offsetSize) / mTileSize);
	actor->TileUpY = (int)floorf((y - cubeSize) / mTileSize);
	actor->TileLeftX = (int)floorf((x - cubeSize) / mTileSize);
	actor->TileRightX = (int)floorf((x + cubeSize - offsetSize) / mTileSize);

	if (actor->TileDownY < 0)	{ actor->TileDownY = 0; }
	if (actor->TileUpY < 0)		{ actor->TileUpY = 0; }
	if (actor->TileLeftX < 0)	{ actor->TileLeftX = 0; }
	if (actor->TileRightX < 0)	{ actor->TileRightX = 0; }
	
	//check if they are walls
	actor->CanGoUpLeft		= mCollisionData[actor->TileUpY][actor->TileLeftX] != 1;
	actor->CanGoDownLeft	= mCollisionData[actor->TileDownY][actor->TileLeftX] != 1;
	actor->CanGoUpRight		= mCollisionData[actor->TileUpY][actor->TileRightX] != 1;
	actor->CanGoDownRight	= mCollisionData[actor->TileDownY][actor->TileRightX] != 1;
}