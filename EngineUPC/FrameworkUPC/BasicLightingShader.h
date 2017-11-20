#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"
#include "NBasicLight.h"
#include "GameFramework.h"
#include "EnumLightType.h"

#include <glm\glm.hpp>
#include <vector>

struct BasicLightUniforms {
	GLuint LightPositionLocation;
	GLuint LightColorLocation;
	GLuint LightAttenuationLocation;
	GLuint LightAmbientCoefficientLocation;
	GLuint LightConeAngleLocation;
	GLuint LightConeDirectionLocation;
};

struct BasicLightContainer {
	BasicLightUniforms Uniforms;
	NBasicLight* BasicLight;
};

class BasicLightingShader : public BaseShader
{
public:
	BasicLightingShader() { BaseShader::BaseShader(); }
	~BasicLightingShader() { BaseShader::~BaseShader(); }

	NBasicLight* AddLight(std::string name, EnumLightType lightType) {
		NBasicLight* light = nullptr;
		GameFramework* framework = GameFramework::GET_FRAMEWORK();
		NLightManager* lightManagment = framework->GetLightManager();

		switch (lightType) {
		case EnumLightType::DIRECTIONAL_LIGHT:
			light = lightManagment->CreateDirectionalLight(name, 0, 0, 0);
			break;
		case EnumLightType::SPOT_LIGHT:
			glm::vec3 position;
			position.x = 0;
			position.y = 0;
			position.z = 0;

			glm::vec3 coneDirection;
			coneDirection.x = 0;
			coneDirection.y = 0;
			coneDirection.z = 0;

			float coneAngle = 0;

			light = lightManagment->CreateSpotLight(name, position,
				coneDirection, coneAngle);
			break;
		}

		if (light != nullptr) {
			std::string numLights = std::to_string(mLigths.size());

			BasicLightContainer container;
			container.BasicLight = light;

			container.Uniforms.LightPositionLocation = GetUniformLocation("allLights[" + numLights + "].position");
			container.Uniforms.LightColorLocation = GetUniformLocation("allLights[" + numLights + "].intensities");
			container.Uniforms.LightAttenuationLocation = GetUniformLocation("allLights[" + numLights + "].attenuation");
			container.Uniforms.LightAmbientCoefficientLocation = GetUniformLocation("allLights[" + numLights + "].ambientCoefficient");
			container.Uniforms.LightConeAngleLocation = GetUniformLocation("allLights[" + numLights + "].coneAngle");
			container.Uniforms.LightConeDirectionLocation = GetUniformLocation("allLights[" + numLights + "].coneDirection");
		
			mLigths.push_back(container);
		}

		return light;
	}

	void Use() {
		BaseShader::Use();

		// material
		glUniform1i(mNumLightsLocation, (int)mLigths.size());
		glUniform1f(mMaterialShininessLocation, 80.0f);
		glUniform3f(mMaterialSpecularColoeLocation, 1.0f, 1.0f, 1.0f);

		for (int i = 0; i < mLigths.size(); i++) {
			BasicLightContainer container = mLigths.at(i);
			
			// light
			if (container.BasicLight != nullptr) {
				glUniform4fv(container.Uniforms.LightPositionLocation, 1, 
					glm::value_ptr(container.BasicLight->GetPosition()));
				glUniform3fv(container.Uniforms.LightColorLocation, 1, 
					glm::value_ptr(container.BasicLight->GetLigthColor()));
				glUniform1f(container.Uniforms.LightAttenuationLocation, 
					container.BasicLight->GetAttenuation());
				glUniform1f(container.Uniforms.LightAmbientCoefficientLocation, 
					container.BasicLight->GetAmbientCoefficient());
				glUniform1f(container.Uniforms.LightConeAngleLocation, 
					container.BasicLight->GetConeAngle());
				glUniform3fv(container.Uniforms.LightConeDirectionLocation, 1, 
					glm::value_ptr(container.BasicLight->GetConeDirection()));
			}
		}
	}

protected:
	int mNumLightsLocation;
	// material
	GLuint mMaterialShininessLocation;
	GLuint mMaterialSpecularColoeLocation;

	std::vector<BasicLightContainer> mLigths;

	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexNormal");
		AddAttribute("vertexUV");
	}

	void OnReady() {
		BaseShader::OnReady();

		mNumLightsLocation = GetUniformLocation("numLights");

		// material
		mMaterialShininessLocation = GetUniformLocation("materialShininess");
		mMaterialSpecularColoeLocation = GetUniformLocation("materialSpecularColor");
	}
};
