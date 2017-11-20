#include "NBasicLight.h"

NBasicLight::NBasicLight(NLightManager* manager) 
	: NBaseLight(manager) {}
NBasicLight::~NBasicLight() {}

void NBasicLight::Initialize(std::string name, float x, float y, float z) {
	NBaseLight::Initialize(name, x, y, z);

	// set default values
	SetLightColor(NBasicLight::DEFAULT_LIGHT_COLOR);
	SetConeDirection(NBasicLight::DEFAULT_CONE_DIRECTION);
	SetAttenuation(NBasicLight::DEFAULT_ATTENUATION);
	SetAmbientCoefficient(NBasicLight::DEFAULT_AMBIENT_COEFFICIENT);
	SetConeAngle(NBasicLight::DEFAULT_CONE_ANGLE);
}
