#pragma once

#include <polygon/component.h>
#include <polygon/glm/glm.hpp>

class SpotLight : public Component
{
public:

	glm::vec3 color;
	float intensity;
	float maxDistance;

	float angle;

	void OnStart();
	void OnRemove();
	void OnDestroy();

	glm::vec3 GetLightDir();
};

