#pragma once

#include <polygon/glm/glm.hpp>

#include <polygon/component.h>

/*
* 3D camera component
*/
class Camera : public Component
{
public:



	float fov;				// field of view
	float nearZ;			// frustum start (never = 0)
	float renderDistance;	// max distance of camera

	Camera();

	// Get perspective matrix projection of models
	glm::mat4 GetViewProjection();
};

