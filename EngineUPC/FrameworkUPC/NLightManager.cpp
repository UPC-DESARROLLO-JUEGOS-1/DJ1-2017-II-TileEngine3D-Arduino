#include "NLightManager.h"

#include "NBasicLight.h"
#include "EnumLightType.h"

void NLightManager::Initialize() {
	CreateDirectionalLight("default", 0, 0, 0);
}

NBasicLight* NLightManager::CreateDirectionalLight(std::string name, float x, float y, float z) {
	NBasicLight* result = nullptr;

	if (!ExistsLight(name)) {
		result = new NBasicLight(this);
		result->Initialize(name, x, y, z);
		result->SetLightType(EnumLightType::DIRECTIONAL_LIGHT);

		mLights.insert(std::make_pair(name, result));
	}
	else {
		result = GetLigth(name);
	}
	
	return result;
}

NBasicLight* NLightManager::CreateSpotLight(std::string name, glm::vec3 position,
	glm::vec3 coneDirection, float coneAngle) {

	NBasicLight* result = nullptr;

	if (!ExistsLight(name)) {
		result = new NBasicLight(this);
		result->Initialize(name, position.x, position.y, position.z);
		result->SetConeDirection(coneDirection);
		result->SetConeAngle(coneAngle);
		result->SetLightType(EnumLightType::SPOT_LIGHT);

		mLights.insert(std::make_pair(name, result));
	}
	else {
		result = GetLigth(name);
	}

	return result;
}

bool NLightManager::ExistsLight(std::string name) {
	bool result = false;

	std::map<std::string, NBasicLight*>::iterator it = mLights.find(name);
	NBasicLight* light = it != mLights.end() ? it->second : nullptr;
	result = light != nullptr;

	return result;
}

NBasicLight* NLightManager::GetLigth(const std::string name) {
	std::map<std::string, NBasicLight*>::iterator it = mLights.find(name);
	NBasicLight* result = it != mLights.end() ? it->second : nullptr;
	return result;
}