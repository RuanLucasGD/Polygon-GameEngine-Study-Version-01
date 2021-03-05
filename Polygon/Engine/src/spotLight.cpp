#include <polygon/spotLight.h>

#include <polygon/scene.h>
#include <polygon/gameObject.h>

void SpotLight::OnStart() {

	gameObject->GetSceneOwner()->AddLight(this);
}

void SpotLight::OnRemove() {

	gameObject->GetSceneOwner()->RemoveLight(this);
}

void SpotLight::OnDestroy() {

	gameObject->GetSceneOwner()->RemoveLight(this);
}

glm::vec3 SpotLight::GetLightDir() {

	return gameObject->transform->GetForward();
}