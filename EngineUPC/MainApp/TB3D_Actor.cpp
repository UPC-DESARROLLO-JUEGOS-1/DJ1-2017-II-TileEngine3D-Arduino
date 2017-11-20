#include "TB3D_Actor.h"
#include "TB3D_Engine.h"
#include "TB3D_WorldPhysics.h"

TB3D_Actor::TB3D_Actor(TB3D_Engine* engine) :
	mX(0), mY(0), mZ(0), mOffsetX(0), mOffsetY(0), mOffsetZ(0),
	mTileWidth(0), mTileHeight(0), mDebugMode(false)
{
	mEngine = engine;
}

TB3D_Actor::~TB3D_Actor()
{
}

void TB3D_Actor::Initialize() {
	CanGoUpLeft = false;
	CanGoDownLeft = false;
	CanGoUpRight = false;
	CanGoDownRight = false;
	
	mTileWidth = mEngine->GetTileSize();
	mTileHeight = mEngine->GetTileSize();
}

void TB3D_Actor::CreateCollision(float size) {
	mCollisionCube = new NPrimitiveCube3D();
	mCollisionCube->Initialize(0, 0, 0, size, size, size);
	mCollisionCube->SetRenderCamera((BaseCamera*)mEngine->GetCamera()->GetRenderCamera());
}

Vector2 TB3D_Actor::ComputeNewPosition(float speed, float directionX, float directionY) {
	float size = mCollisionCube->GetSizeX() / 2.0;
	float newX = mX;
	float newY = mZ;
	float tileSize = mEngine->GetTileSize();
	int tileX = (int)floorf(newX / tileSize);
	int tileY = (int)floorf(newY / tileSize);
	TB3D_WorldPhysics* physics = mEngine->GetWorld()->GetWorldPhysics();

	// vertical
	physics->GetCorners(size, newX, newY + (speed * directionY), this);

	if (directionY == -1) {
		if (CanGoUpLeft && CanGoUpRight) {
			newY += speed * directionY;
		}
		else {
			newY = tileY * tileSize + size;
		}
	}

	if (directionY == 1) {
		if (CanGoDownLeft && CanGoDownRight) {
			newY += speed * directionY;
		}
		else {
			newY = (tileY + 1) * tileSize - size;
		}
	}

	// horizontal
	physics->GetCorners(size, newX + (speed * directionX), newY, this);

	if (directionX == -1) {
		if (CanGoDownLeft && CanGoUpLeft) {
			newX += speed * directionX;
		}
		else {
			newX = tileX * tileSize + size;
		}
	}

	if (directionX == 1) {
		if (CanGoUpRight && CanGoDownRight) {
			newX += speed * directionX;
		}
		else {
			newX = (tileX + 1) * tileSize - size;
		}
	}

	Vector2 result;
	result.x = newX;
	result.y = newY;

	return result;
}

void TB3D_Actor::Update(float dt) {
	if (mCollisionCube != nullptr) {
		mCollisionCube->SetPosition(mX + mOffsetX, mY + mOffsetY, mZ + mOffsetZ);

		if (mDebugMode) {
			mCollisionCube->Update(dt);
		}

		int px = (int)floorf(mX / mTileWidth);
		int pz = (int)floorf(mZ / mTileHeight);
	}
}

void TB3D_Actor::Draw(float dt) {
	if (mDebugMode) {
		mCollisionCube->Draw(dt);
	}
}