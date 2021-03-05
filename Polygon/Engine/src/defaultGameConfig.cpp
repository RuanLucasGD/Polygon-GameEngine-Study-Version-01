#include <polygon/defaultGameConfig.h>

DefaultGameConfig::DefaultGameConfig(const char* name, int width, int heigth) {

	this->name = name;
	this->width = width;
	this->heigth = heigth;
}

const char* DefaultGameConfig::GetName() { return name; }

int DefaultGameConfig::GetResolutionWidth() { return width; }

int DefaultGameConfig::GetResolutionHeight() { return heigth; }