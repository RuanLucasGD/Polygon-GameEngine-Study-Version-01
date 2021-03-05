#pragma once
#include <polygon/glm/glm.hpp>

class GameObject;

class Transform
{
protected:

	glm::vec3 pos;
	glm::mat3 rot;
	glm::vec3 scale;

public:

	GameObject* gameObject;		// gameObject owner

	Transform();

	/*
	* Set object position
	* @param pos: new oject position
	*/
	void SetPos(glm::vec3 pos);

	/*
	* Set object rotation
	* @param rot: new object rotation
	*/
	void SetRot(glm::vec3 rot);

	/*
	* Set object scale
	* @param scale: new object scale
	*/
	void SetScale(glm::vec3 scale);

	/*
	* Move object in some direction
	* @param dir: direction
	*/
	void Move(glm::vec3 dir);

	/*
	* Rotate object using euler angles
	* @param axis: angle axis for rotate
	* @param local: is local rotation
	*/
	void Rotate(glm::vec3 axis, bool local = false);

	/*
	* Look to target
	* @param target: some position in 3D space
	*/
	void LookAt(glm::vec3 target);

	/*
	* Get direction of object
	* @param axis: direction normalized whe whants to pick up
	*/
	glm::vec3 GetDir(glm::vec3 axis);

	/*
	* Get forward direction of object
	*/
	glm::vec3 GetForward();

	/*
	* Get backward direction of object
	*/
	glm::vec3 GetBackward();

	/*
	* Get right direction of object
	*/
	glm::vec3 GetRight();

	/*
	* Get left direction of object
	*/
	glm::vec3 GetLeft();

	/*
	* Get up direction of object
	*/
	glm::vec3 GetUp();

	/*
	* Get down direction of object
	*/
	glm::vec3 GetDown();

	/*
	* Get object position in world space
	*/
	glm::vec3 GetPos();

	/*
	* Get object rotation in world space
	*/
	glm::mat3 GetRot();

	/*
	* Get object scale in world space
	*/
	glm::vec3 GetScale();

	/*
	* Get object transformation matrix
	*/
	glm::mat4 GetModel();
};

