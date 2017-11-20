#include "NBaseLight.h"

void NBaseLight::Initialize(std::string name, float x, float y, float z) {
	mPosition = glm::vec4(x, y, z, 0.0f);
	mName = name;
}