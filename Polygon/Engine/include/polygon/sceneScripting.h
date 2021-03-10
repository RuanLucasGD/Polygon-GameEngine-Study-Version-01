#pragma once

class Scene;

/*
* Base for create custom scene logics
*/
class SceneScripting
{
public:

	Scene* scene;	// own scene

	/*
	* Create ImGui windows
	*/
	virtual void OnEditor() {}

	/*
	* Start of scene
	*/
	virtual void OnStart() {}

	/*
	* Update scene logic
	*/
	virtual void OnUpdate(float delta) {}
};
