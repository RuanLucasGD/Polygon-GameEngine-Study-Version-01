#include <polygon/camera.h>

#include <polygon/GLFW/glfw3.h>
#include <polygon/glm/gtc/matrix_transform.hpp>

#include <polygon/screen.h>
#include <polygon/transform.h>
#include <polygon/gameObject.h>

Camera::Camera() {

	fov = 45;
	nearZ = 0.001f;
	renderDistance = 1000;
}

glm::mat4 Camera::GetViewProjection() {

	float screenAspect = (float)screen->GetResolutionWidth() / (float)screen->GetResolutionHeight();
	glm::mat4 projection = glm::perspective(fov, screenAspect, nearZ, renderDistance);

	glm::vec3 lookAtTarget = transform->GetPos() + transform->GetForward();
	glm::mat4 view = glm::lookAt(transform->GetPos(), lookAtTarget, transform->GetUp());

	return projection * view;
}