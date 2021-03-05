#include <polygon/gameObject.h>

#include <polygon/component.h>
#include <polygon/sceneManager.h>

#include <string>
#include <sstream>

GameObject::GameObject() {

	// create name
	size_t index = sceneManager->GetCurrenScene()->GetGameObjectsAmount();
	std::ostringstream indexStream;
	indexStream << index;
	std::string name = "object " + indexStream.str();

	// create object
	this->name = name;
	this->transform = new Transform();
	this->transform->gameObject = this;
	this->scene = sceneManager->GetCurrenScene();
}

int GameObject::GetComponentsAmount() { return components.size(); }

Component* GameObject::GetComponentByIndex(int i) { return components[i]; }

Scene* GameObject::GetSceneOwner() { return scene; }