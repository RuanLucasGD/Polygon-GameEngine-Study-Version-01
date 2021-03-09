#include <polygon/cameraController.h>

#include <iostream>

#include <polygon/GLFW/glfw3.h>
#include <polygon/glm/gtx/euler_angles.hpp>

#include <polygon/screen.h>
#include <polygon/transform.h>

#include <polygon/imgui/imgui.h>

CameraController::CameraController() {

	this->rotSpeed = 0;
	this->moveSpeed = 0;
	this->lastMousePosX = 0;
	this->lastMousePosY = 0;
}

void CameraController::OnStart() {}

void CameraController::OnUpdate(float delta) {

	GLFWwindow* window = screen->GetWindow();
	glm::vec3 moveVelocity = glm::vec3();


	// --- front, back, sides --- //

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) moveVelocity += transform->GetForward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) moveVelocity += transform->GetBackward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) moveVelocity += transform->GetRight();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) moveVelocity += transform->GetLeft();


	// --- up, down --- //

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) moveVelocity += glm::vec3(0, 1, 0);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) moveVelocity += glm::vec3(0, -1, 0);


	// -- apply camera moviment --- //

	moveVelocity *= moveSpeed * delta;
	transform->Move(moveVelocity);

	double mousePosX;
	double mousePosY;

	glfwGetCursorPos(window, &mousePosX, &mousePosY);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// --- get mouse speed --- //

		glm::vec3 mouseSpeed = glm::vec3();
		mouseSpeed.y = (float)(mousePosX - lastMousePosX);
		mouseSpeed.x = (float)(mousePosY - lastMousePosY);

		mouseSpeed.x *= rotSpeed;
		mouseSpeed.y *= -rotSpeed;

		// not use delta time
		transform->Rotate(glm::vec3(0, 1, 0) * rotSpeed * mouseSpeed.y);
		transform->Rotate(transform->GetRight() * rotSpeed * mouseSpeed.x);
	}

	lastMousePosX = mousePosX;
	lastMousePosY = mousePosY;
}