#pragma once

#include <string>
#include <map>
#include <glm\glm.hpp>

class GameFramework;
class NBasicLight;

class NLightManager
{
public:
	NLightManager(GameFramework* framework) { mFramework = framework; }
	~NLightManager() {}

	void Initialize();
	bool ExistsLight(std::string name);

	NBasicLight* CreateDirectionalLight(std::string name, float x, float y, float z);
	NBasicLight* CreateSpotLight(std::string name, glm::vec3 position,
		glm::vec3 coneDirection, float coneAngle);
	NBasicLight* GetLigth(const std::string name);

private:
	GameFramework* mFramework;
	std::map<std::string, NBasicLight*> mLights;
};

