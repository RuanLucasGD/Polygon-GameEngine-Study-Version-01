#pragma once

#include <polygon/glm/glm.hpp>

class Environment
{
public:
	glm::vec3 ambientColor;		// Environment light color
	glm::vec3 backgroundColor;	// sky color
};
