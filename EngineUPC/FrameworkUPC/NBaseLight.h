#pragma once

#include "EnumLightType.h"

#include <string>
#include <glm\glm.hpp>

class NLightManager;

class NBaseLight
{
public:
	NBaseLight(NLightManager* manager) { mManager = manager; }
	~NBaseLight() {}

	inline float GetX() { return mPosition.x; }
	inline float GetY() { return mPosition.y; }
	inline float GetZ() { return mPosition.z; }
	inline void SetX(float value) { mPosition.x = value; }
	inline void SetY(float value) { mPosition.y = value; }
	inline void SetZ(float value) { mPosition.z = value; }

	virtual void Initialize(std::string name, float x, float y, float z);
	virtual void SetLightType(EnumLightType type) {
		mLightType = type;

		switch (type)
		{
		case EnumLightType::DIRECTIONAL_LIGHT:
			mPosition.w = 0.0f;
			break;
		case EnumLightType::SPOT_LIGHT:
			mPosition.w = 1.0f;
			break;
		}
	}

	void SetPosition(float x, float y, float z) {
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
	}
	inline glm::vec4 GetPosition() { return mPosition; };

protected:
	NLightManager* mManager;
	std::string mName;
	glm::vec4 mPosition;

	EnumLightType mLightType;
};

