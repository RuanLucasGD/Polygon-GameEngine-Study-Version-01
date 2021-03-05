#pragma once

#include <polygon/scene.h>

/*
* Management of all scenes
* add, remove, load...
*/
class SceneManager
{
private:

	Scene* currentScene;
	std::vector <Scene*> scenes;

	SceneManager();
	static SceneManager* instance;

public:

	static SceneManager* GetInstance();

	/*
	* Add new empty scene
	* @param name: name of scene
	* @param script: scene logic
	*/
	Scene* AddScene(const char* name, SceneScripting* script);

	/*
	* Load existing scene
	* @param name: name of scene
	*/
	void LoadScene(const char* name);

	/*
	* Get current loaded scene
	*/
	Scene* GetCurrenScene();
};

static SceneManager* sceneManager = SceneManager::GetInstance();