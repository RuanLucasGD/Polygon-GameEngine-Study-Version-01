#pragma once

#include <polygon/transform.h>

class SunLight
{
private:

	Transform* transform;

public:

	glm::vec3 color;
	float intensity;

	SunLight();

	void SetRot(glm::vec3 euler);
	glm::vec3  GetSunDirection();
};

