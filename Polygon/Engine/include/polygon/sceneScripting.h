#pragma once

class Scene;

/*
* Base for create custom scene logics
*/
class SceneScripting
{
public:

	Scene* scene;	// own scene

	virtual void OnStart() {}
	virtual void OnUpdate(float delta) {}
};
