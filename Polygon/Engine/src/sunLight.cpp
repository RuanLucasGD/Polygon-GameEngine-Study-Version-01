#include <polygon/sunLight.h>

SunLight::SunLight() {

	transform = new Transform();
}

void SunLight::SetRot(glm::vec3 euler) { transform->SetRot(euler); }

glm::vec3 SunLight::GetSunDirection() { return -transform->GetForward(); }
