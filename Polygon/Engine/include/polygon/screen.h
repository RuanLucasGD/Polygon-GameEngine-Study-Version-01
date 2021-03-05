#pragma once

#include <polygon/GLFW/glfw3.h>

#include <polygon/defaultGameConfig.h>

/*
* Manage screen configurations
*/
class Screen
{
private:

	const char* name;
	int width;
	int height;

	GLFWwindow* window;

	static Screen* instance;

	Screen();
public:

	/*
	* Create game window
	* @param gameConfig: initial screen configurations
	*/
	void CreateScreen(DefaultGameConfig* gameConfig);

	/*
	* Get GLFW window
	*/
	GLFWwindow* GetWindow();

	/*
	* Get resolution width
	*/
	int GetResolutionWidth();

	/*
	* Get resolution height
	*/
	int GetResolutionHeight();

	static Screen* GetInstance();
};

static Screen* screen = Screen::GetInstance();