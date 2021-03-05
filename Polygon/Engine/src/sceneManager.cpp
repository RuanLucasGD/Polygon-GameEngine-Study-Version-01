#include <polygon/sceneManager.h>

#include <iostream>

SceneManager* SceneManager::instance;

SceneManager::SceneManager() {

	currentScene = nullptr;
}

SceneManager* SceneManager::GetInstance() {

	if (!instance) instance = new SceneManager();
	return instance;
}

Scene* SceneManager::AddScene(const char* name, SceneScripting* script) {

	Scene* scene = new Scene(script);
	script->scene = scene;

	scene->name = name;

	scenes.push_back(scene);

	return scene;
}

void SceneManager::LoadScene(const char* name) {

	for (auto& s : scenes) {

		if (s->name == name) {

			currentScene = s;
			currentScene->GetSceneScript()->OnStart();
		}
	}
}

Scene* SceneManager::GetCurrenScene() { return currentScene; }