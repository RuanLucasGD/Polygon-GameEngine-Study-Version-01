#pragma once

#include <polygon/glad/glad.h>
#include <polygon/GLFW/glfw3.h>

#include <polygon/editorGrid.h>
#include <polygon/defaultGameConfig.h>
#include <polygon/defaultLevelConfig.h>

class Core
{
private:

	GLFWwindow* window;
	Scene* currentScene;
	EditorGrid* editorGrid;


	// --- 3D grid --- //

	const int EDITOR_GRID_SIZE = 10;
	const int EDITOR_GRID_SPACE = 1;


	// --- used in game loop --- //
	void Start();
	void Update(float delta);
	void Render();
public:

	const bool USE_EDITOR_GRID = false;
	const bool PRINT_FPS = true;

	/* Create the game
	*
	* @param: gameConfig is structure with settings default of game
	* @param: levelConfig is data of first level of game
	*/
	Core(DefaultGameConfig* gameConfig, DefaultLevelConfig* levelConfig);

	/*
	* Run main game loop
	*/
	void UpdateGame();

	/*
	* Close the game
	*/
	~Core();
};

