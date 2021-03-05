#include <polygon/DefaultLevelConfig.h>

DefaultLevelConfig::DefaultLevelConfig(const char* name, SceneScripting* script) {

	this->name = name;
	this->script = script;
}

const char* DefaultLevelConfig::GetLevelName() { return name; }

SceneScripting* DefaultLevelConfig::GetScript() { return script; }