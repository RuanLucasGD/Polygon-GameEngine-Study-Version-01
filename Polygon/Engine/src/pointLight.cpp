#include <polygon/pointLight.h>

#include <iostream>

#include <polygon/scene.h>
#include <polygon/gameObject.h>

void PointLight::OnStart() {

	// adding light in the light list of scene
	gameObject->GetSceneOwner()->AddLight(this);
}

void PointLight::OnUpdate() {}

void PointLight::OnRemove() {

	gameObject->GetSceneOwner()->RemoveLight(this);
}

void PointLight::OnDestroy() {

	gameObject->GetSceneOwner()->RemoveLight(this);
}
