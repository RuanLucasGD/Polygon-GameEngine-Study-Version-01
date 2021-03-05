#include <polygon/transform.h>
#include <polygon/glm/gtc/matrix_transform.hpp>
#include <polygon/glm/gtx/euler_angles.hpp>

Transform::Transform()
{
	gameObject = nullptr;

	pos = glm::vec3();
	rot = glm::mat3(1);
	scale = glm::vec3(1);
}

void Transform::SetPos(glm::vec3 pos) {

	this->pos = pos;
}

void Transform::SetRot(glm::vec3 rot) {

	rot = glm::radians(rot);

	this->rot = glm::eulerAngleXYZ(rot.x, rot.y, rot.z);
}

void Transform::SetScale(glm::vec3 scale) {

	this->scale = scale;
}

void Transform::Move(glm::vec3 dir) {

	this->pos += dir;
}
void Transform::Rotate(glm::vec3 axis, bool local) {

	axis = glm::radians(axis);

	glm::mat4 r;

	if (local) {

		r = glm::mat4(this->rot);
		r = glm::rotate(r, axis.x, glm::vec3(1, 0, 0));
		r = glm::rotate(r, axis.y, glm::vec3(0, 1, 0));
		r = glm::rotate(r, axis.z, glm::vec3(0, 0, 1));
		this->rot = r;
	}
	else {

		r = glm::mat4(1);
		r = glm::rotate(r, axis.x, glm::vec3(1, 0, 0));
		r = glm::rotate(r, axis.y, glm::vec3(0, 1, 0));
		r = glm::rotate(r, axis.z, glm::vec3(0, 0, 1));
		this->rot = glm::mat3(r) * this->rot;
	}
}

void Transform::LookAt(glm::vec3 target) {

	rot = glm::inverse(glm::mat3(glm::lookAt(pos, target, glm::vec3(0, 1, 0))));
}

glm::vec3 Transform::GetPos() { return pos; }

glm::mat3 Transform::GetRot() { return rot; }

glm::vec3 Transform::GetScale() { return scale; }

glm::vec3 Transform::GetDir(glm::vec3 axis) { return axis * glm::inverse(rot); }

glm::vec3 Transform::GetForward() { return GetDir(glm::vec3(0, 0, -1)); }

glm::vec3 Transform::GetBackward() { return GetDir(glm::vec3(0, 0, 1)); }

glm::vec3 Transform::GetRight() { return GetDir(glm::vec3(-1, 0, 0)); }

glm::vec3 Transform::GetLeft() { return GetDir(glm::vec3(1, 0, 0)); }

glm::vec3 Transform::GetUp() { return GetDir(glm::vec3(0, 1, 0)); }

glm::vec3 Transform::GetDown() { return GetDir(glm::vec3(0, -1, 0)); }

glm::mat4 Transform::GetModel() {

	glm::mat4 orientation = glm::mat4(this->rot);
	glm::mat4 scale = glm::scale(glm::mat4(1), this->scale);
	glm::mat4 translate = glm::translate(glm::mat4(1), this->pos);

	return translate * orientation * scale;
}