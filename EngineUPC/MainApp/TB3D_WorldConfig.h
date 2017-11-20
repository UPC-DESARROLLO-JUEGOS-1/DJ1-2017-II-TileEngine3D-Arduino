#pragma once

#include <string>
#include <vector>

struct TB3D_WorldConfig {

public:
	std::string Identifier()						{ return mIdentifier; }
	float TileSize()								{ return mTileSize; }
	std::vector<std::vector<int>> WorldCollisions()	{ return mWorldCollisions; }

	void SetValues(std::string identifier, float tileSize, std::vector<std::vector<int>> worldCollisions) {
		mIdentifier = identifier;
		mTileSize = tileSize;
		mWorldCollisions = worldCollisions;
	}
private:
	std::string mIdentifier;
	float mTileSize;
	std::vector<std::vector<int>> mWorldCollisions;
};