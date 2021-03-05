#pragma once

#include <polygon/glm/glm.hpp>

#include <polygon/component.h>

/*
* Illuminates objects with range
*
* When created, this component is added to a list in the scene that stores the lights.
* All lights separated by different types. The added lights are used to calculate the illumination of objects.
*
* When this light is destroyed, it is removed from the list
*/

class PointLight : public Component
{
public:

	glm::vec3 color;
	float intensity;
	float maxDistance;

	void OnStart();
	void OnUpdate();
	void OnRemove();
	void OnDestroy();
};

