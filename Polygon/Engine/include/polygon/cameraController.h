#pragma once

#include <polygon/component.h>

#include <polygon/glm/glm.hpp>

/*
* Component for move camera in the 3D space
*/
class CameraController : public Component
{
private:

	// for get mouse velocity
	double lastMousePosX;
	double lastMousePosY;

public:

	float moveSpeed;	// speed of movement
	float rotSpeed;		// rotation speed

	CameraController();

	void OnEditor();
	void OnStart();
	void OnUpdate(float delta);
};
