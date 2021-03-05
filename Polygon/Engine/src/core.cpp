#include <polygon/core.h>

#include <iostream>

#include <polygon/glad/glad.h>
#include <polygon/GLFW/glfw3.h>

#include <polygon/screen.h>
#include <polygon/gizmos.h>
#include <polygon/editorGrid.h>
#include <polygon/sceneManager.h>

Core::Core(DefaultGameConfig* gameConfig, DefaultLevelConfig* levelConfig) {

	// --- initialize glfw --- //
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// --- creating window --- //
	screen->CreateScreen(gameConfig);
	window = screen->GetWindow();


	// --- initialize opengl --- //
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glEnable(GL_DEPTH_TEST);	// enable depth buffer for create perspective vision


	// --- create debug gizmos --- //
	gizmos = Gizmos::GetInstance();
	gizmos->CreateGizmos();

	editorGrid = new EditorGrid(EDITOR_GRID_SIZE, EDITOR_GRID_SPACE);


	// --- create first level for start game --- //
	currentScene = sceneManager->AddScene("level 0", levelConfig->GetScript());
}

void Core::UpdateGame() {

	// start game
	Start();


	// --- initialize delta time and fps count --- //
	int fpsCount = 0;

	double lastTimeFps = glfwGetTime();
	double lastTimeDelta = glfwGetTime();

	// game loop
	while (!glfwWindowShouldClose(window))
	{
		// --- calculate fps and delta time ---
		fpsCount++;

		double currentTimeFps = glfwGetTime();
		double currentTimeDelta = glfwGetTime();
		float delta = (float)(currentTimeDelta - lastTimeDelta);

		lastTimeDelta = glfwGetTime();

		if (currentTimeFps - lastTimeFps >= 1.0f) {

			if (PRINT_FPS) {

				std::cout << "fps: " << fpsCount << std::endl;
			}

			fpsCount = 0;
			lastTimeFps = glfwGetTime();
		}


		// --- clear --- //
		float bgColor[] = {

			currentScene->environment->backgroundColor.x,
			currentScene->environment->backgroundColor.y,
			currentScene->environment->backgroundColor.z
		};

		glClearColor(bgColor[0], bgColor[1], bgColor[2], 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// --- update game and render --- //
		Update(delta);
		Render();
	}
}

Core::~Core() {}

void Core::Start() {

	// --- load fist scene --- //
	sceneManager->LoadScene("level 0");
}

void Core::Update(float delta) {

	if (USE_EDITOR_GRID) editorGrid->DrawEditorGrid();


	// --- update game logic --- //
	currentScene->GetSceneScript()->OnUpdate(delta);

	int gameObjectsAmount = currentScene->GetGameObjectsAmount();

	for (int i = 0; i < gameObjectsAmount; i++) {

		GameObject* gameObject = currentScene->GetObjectByIndex(i);
		int componentsAmount = gameObject->GetComponentsAmount();

		for (int x = 0; x < componentsAmount; x++) {

			Component* component = gameObject->GetComponentByIndex(x);
			component->OnUpdate(delta);
		}
	}
}

void Core::Render() {

	// --- render all elements --- //
	int gameObjectsAmount = currentScene->GetGameObjectsAmount();

	for (int i = 0; i < gameObjectsAmount; i++) {

		GameObject* gameObject = currentScene->GetObjectByIndex(i);
		int componentsAmount = gameObject->GetComponentsAmount();

		for (int x = 0; x < componentsAmount; x++) {

			Component* component = gameObject->GetComponentByIndex(x);
			component->OnRender();
		}
	}

	gizmos->OnRender();

	glfwSwapBuffers(window);
	glfwPollEvents();
}