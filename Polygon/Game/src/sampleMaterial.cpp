#include <sampleMaterial.h>

#include <vector>
#include <string>
#include <sstream>
#include <typeinfo>
#include <iostream>

#include <polygon/sceneManager.h>

void SampleMaterial::OnStart() {

	SetShader("shaders/sampleShader.vert", "shaders/sampleShader.frag");

	Use();
	SetBool(textureIsNull, true);

	SetVec3("material.color", glm::vec3(1.0f));
}

void SampleMaterial::OnUpdate() {

	Use();
	Scene* scene = gameObject->GetSceneOwner();

	SetVec3("cameraPos", scene->GetCurrentCamera()->transform->GetPos());
	SetFloat("material.specular", specular);

	SetVec3("ambient.color", scene->environment->ambientColor);
	SetVec3("sunLight.color", scene->sun->color);
	SetVec3("sunLight.dir", scene->sun->GetSunDirection());

	SetInt("pointLightsAmount", scene->GetPointLightsAmount());
	SetInt("spotLightsAmount", scene->GetSpotLightsAmount());

	for (int i = 0; i < scene->GetPointLightsAmount(); i++) {

		std::ostringstream stream;
		stream << i;

		std::string index = stream.str();
		std::string pos = "pointLights[" + index + "].pos";
		std::string color = "pointLights[" + index + "].color";
		std::string maxDistance = "pointLights[" + index + "].maxDistance";

		PointLight* light = scene->GetPointLightByIndex(i);

		SetVec3(pos.c_str(), light->transform->GetPos());
		SetFloat(maxDistance.c_str(), light->maxDistance);
		SetVec3(color.c_str(), light->color);
	}

	for (int i = 0; i < scene->GetSpotLightsAmount(); i++) {

		std::ostringstream stream;
		stream << i;
		std::string index = stream.str();
		std::string pos = "spotLights[" + index + "].pos";
		std::string dir = "spotLights[" + index + "].dir";
		std::string color = "spotLights[" + index + "].color";
		std::string angle = "spotLights[" + index + "].angle";
		std::string maxDist = "spotLights[" + index + "].maxDistance";

		SpotLight* light = scene->GetSpotLightByIndex(i);

		SetVec3(pos.c_str(), light->transform->GetPos());
		SetVec3(color.c_str(), light->color);
		SetVec3(dir.c_str(), light->GetLightDir());
		SetFloat(angle.c_str(), light->angle);
		SetFloat(maxDist.c_str(), light->maxDistance);
	}
}
