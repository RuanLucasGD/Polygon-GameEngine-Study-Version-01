#include <polygon/screen.h>

Screen* Screen::instance = nullptr;

Screen::Screen() {

	window = nullptr;

	name = nullptr;
	width = 0;
	height = 0;
}

Screen* Screen::GetInstance() {

	if (!instance) instance = new Screen();
	return instance;
}

void Screen::CreateScreen(DefaultGameConfig* gameConfig) {

	name = gameConfig->GetName();
	width = gameConfig->GetResolutionWidth();
	height = gameConfig->GetResolutionHeight();

	window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	glfwSetWindowPos(window, width / 2, height / 8); // set screen position on center
}

GLFWwindow* Screen::GetWindow() { return window; }

int  Screen::GetResolutionWidth() { return width; }

int  Screen::GetResolutionHeight() { return height; }