#pragma once

class Transform;
class GameObject;

/*
* Base for add news behaviours in the gameObjects
*/

class Component abstract {

public:

	// own transform
	Transform* transform = nullptr;
	// owner
	GameObject* gameObject = nullptr;


	virtual void OnEditor() {}
	virtual void OnStart() {}
	virtual void OnUpdate(float delta) {}
	virtual void OnRender() {}
	virtual void OnDestroy() {}
	virtual void OnRemove() {}
};
