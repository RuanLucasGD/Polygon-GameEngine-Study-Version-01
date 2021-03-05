#pragma once

#include <polygon/sceneScripting.h>

/*
* Caracterstics of first game level
*/

class DefaultLevelConfig
{
private:

	const char* name;
	SceneScripting* script;

public:



	/*
	* @param name: name of scene
	* @param script: script that will run in first level
	*/
	DefaultLevelConfig(const char* name, SceneScripting* script);

	const char* GetLevelName();

	SceneScripting* GetScript();
};