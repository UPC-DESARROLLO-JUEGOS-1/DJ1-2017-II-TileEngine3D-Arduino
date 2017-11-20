#pragma once

#include <vector>

class TB3D_World;
class TB3D_Actor;
class TB3D_Engine;

class TB3D_WorldPhysics
{
public:
	TB3D_WorldPhysics(TB3D_World* world);
	~TB3D_WorldPhysics()
	{
		delete mWorld;
		delete mEngine;
	}

	void Initialize(std::vector<std::vector<int>> collisionData);
	void GetCorners(float size, float x, float y, TB3D_Actor* actor);

private: 
	TB3D_World* mWorld;
	TB3D_Engine* mEngine;
	std::vector<std::vector<int>> mCollisionData;

	int mTileSize;
};

