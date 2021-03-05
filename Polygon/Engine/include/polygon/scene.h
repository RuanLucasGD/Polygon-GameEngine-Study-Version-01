#pragma once

#include <vector>
#include <string>

#include <polygon/glm/glm.hpp>

#include <polygon/camera.h>
#include <polygon/sunLight.h>
#include <polygon/transform.h>
#include <polygon/spotLight.h>
#include <polygon/pointLight.h>
#include <polygon/gameObject.h>
#include <polygon/environment.h>
#include <polygon/sceneScripting.h>

/*
* Level of game, when the logics work and Environment is rendered
*/

class Scene
{
private:

	Camera* currentCamera;					// camera used to render
	std::vector <GameObject*> gameObjects;	// all gameObjects of scene
	SceneScripting* script;					// scene logic

	// --- all lights of scene --- //
	std::vector <PointLight*> pointLights;
	std::vector <SpotLight*> spotLights;

	const int MAX_POINT_LIGHTS = 32;
	const int MAX_SPOT_LIGHTS = 32;

public:

	std::string name;			// name of scene

	SunLight* sun;
	Environment* environment;


	/*
	* Create a empty scene
	* @param script: scene logic script
	*/
	Scene(SceneScripting* script);

	/*
	* Add new gameObject on scene
	* @param pos: position of object
	* @param rot: rotation of object
	*/
	GameObject* AddGameObject(glm::vec3 pos, glm::vec3 rot);

	/*
	* If scene not have default camera, is added a new
	*/
	GameObject* AddDefaultCamera(glm::vec3 pos, glm::vec3 rot);

	/*
	* Add new pointLight on scene
	* @param point: light
	*/
	void AddLight(PointLight* point);

	/*
	* Add new spotLight on scene
	*  @param spot: light
	*/
	void AddLight(SpotLight* spot);

	/*
	* Remove light from scene
	* @param light: light to remove
	*/
	void RemoveLight(PointLight* light);

	/*
	* Remove light from scene
	* @param light: light to remove
	*/
	void RemoveLight(SpotLight* light);

	/*
	* Destroy object of scene
	*/
	void Destroy(GameObject* gameObject);

	/*
	* Get number of gameObjects in scene
	*/
	int GetGameObjectsAmount();

	/*
	* Get object of scene using index position of list
	* @param i: index
	*/
	GameObject* GetObjectByIndex(int i);

	/*
	* Get current camera used
	*/
	Camera* GetCurrentCamera();

	/*
	* Get scene logic script
	*/
	SceneScripting* GetSceneScript();

	/*
	* Get point lights amount
	*/
	int GetPointLightsAmount();

	/*
	* Get spot lights amount
	*/
	int GetSpotLightsAmount();

	/*
	* Get point light of scene using index
	* @param i: index
	*/
	PointLight* GetPointLightByIndex(int i);

	/*
	* Get point light of scene using index
	* @param i: index
	*/
	SpotLight* GetSpotLightByIndex(int i);
};