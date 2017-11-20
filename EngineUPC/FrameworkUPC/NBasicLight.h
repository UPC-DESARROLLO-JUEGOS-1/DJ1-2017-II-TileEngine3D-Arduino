#pragma once

#include "NBaseLight.h"
#include "NColor.h"
#include "NLightManager.h"

class NBasicLight : public NBaseLight
{
public:
	const float DEFAULT_ATTENUATION = 0.01f;
	const float DEFAULT_AMBIENT_COEFFICIENT = 0.06f;
	const float DEFAULT_CONE_ANGLE = 0.0f;
	const NColor DEFAULT_LIGHT_COLOR = NColor::White;
	const glm::vec3 DEFAULT_CONE_DIRECTION = glm::vec3(0,0,0);

	inline NColor GetLightColorRaw() { return mLightColorRaw; }

	inline glm::vec3 GetLigthColor() { return mLightColor; }
	inline glm::vec3 GetConeDirection() { return mConeDirection; }
	inline float GetAttenuation() { return mAttenuation; }
	inline float GetAmbientCoefficient() { return mAmbientCoefficient; }
	inline float GetConeAngle() { return mConeAngle; }

	void SetLightColor(NColor color) {
		mLightColorRaw = color;
		mLightColor.x = ((float)color.r) / 255.0f;
		mLightColor.y = ((float)color.g) / 255.0f;
		mLightColor.z = ((float)color.b) / 255.0f;
	}
	void SetConeDirection(glm::vec3 value) {
		mConeDirection = value;
	}
	void SetConeDirection(float x, float y, float z) {
		mConeDirection.x = x;
		mConeDirection.y = y;
		mConeDirection.z = z;
	}
	inline void SetAttenuation(float value) { mAttenuation = value; }
	inline void SetAmbientCoefficient(float value) { mAmbientCoefficient = value; }
	inline void SetConeAngle(float value) { mConeAngle = value; }

	NBasicLight(NLightManager* manager);
	~NBasicLight();

	void Initialize(std::string name, float x, float y, float z);

protected:
	NColor mLightColorRaw;

	glm::vec3 mLightColor;
	glm::vec3 mConeDirection;
	float mAttenuation;
	float mAmbientCoefficient;
	float mConeAngle;
};

