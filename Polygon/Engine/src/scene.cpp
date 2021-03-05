#include <polygon/scene.h>

#include <string>
#include <sstream>
#include <iostream>

Scene::Scene(SceneScripting* script) {

	this->name = "scene";
	this->script = nullptr;
	this->currentCamera = nullptr;
	this->script = script;
	this->sun = new SunLight();
	this->environment = new Environment();
}

GameObject* Scene::AddGameObject(glm::vec3 pos, glm::vec3 rot) {

	GameObject* gameObject = new GameObject();

	gameObject->transform->SetPos(pos);
	gameObject->transform->SetRot(rot);

	gameObjects.push_back(gameObject);

	return gameObject;
}

GameObject* Scene::AddDefaultCamera(glm::vec3 pos, glm::vec3 rot) {

	if (currentCamera) {

		std::cout << "defaut camer exist" << std::endl;
		return currentCamera->gameObject;
	}

	std::ostringstream index;
	index << gameObjects.size();

	GameObject* camera = AddGameObject(pos, rot);
	camera->name = "camera" + index.str();
	currentCamera = camera->AddComponent<Camera>();

	return camera;
}

void Scene::Destroy(GameObject* gameObject) {

	for (int i = 0; i < gameObject->GetComponentsAmount(); i++) {

		Component* component = gameObject->GetComponentByIndex(i);
		component->OnDestroy();
	}

	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject));
}

void Scene::AddLight(PointLight* light) {

	pointLights.push_back(light);
}

void Scene::AddLight(SpotLight* light) {

	spotLights.push_back(light);
}

void Scene::RemoveLight(PointLight* light) {

	pointLights.erase(std::remove(pointLights.begin(), pointLights.end(), light));
}

void Scene::RemoveLight(SpotLight* light) {

	spotLights.erase(std::remove(spotLights.begin(), spotLights.end(), light));
}

int Scene::GetPointLightsAmount() {

	int amount = pointLights.size();
	if (amount > MAX_POINT_LIGHTS) amount = MAX_POINT_LIGHTS;

	return amount;
}

int Scene::GetSpotLightsAmount() {

	int amount = spotLights.size();
	if (amount > MAX_SPOT_LIGHTS) amount = MAX_SPOT_LIGHTS;

	return amount;
}

int Scene::GetGameObjectsAmount() { return gameObjects.size(); }

GameObject* Scene::GetObjectByIndex(int i) { return gameObjects[i]; }

PointLight* Scene::GetPointLightByIndex(int i) { return pointLights[i]; }

SpotLight* Scene::GetSpotLightByIndex(int i) { return spotLights[i]; }

Camera* Scene::GetCurrentCamera() { return currentCamera; }

SceneScripting* Scene::GetSceneScript() { return script; }