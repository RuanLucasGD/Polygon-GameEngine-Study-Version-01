#pragma once

#include <string>
#include <vector>
#include <typeinfo>
#include <iostream>

#include <polygon/transform.h>
#include <polygon/component.h>

class Scene;

class GameObject
{
private:

	Scene* scene;
	std::vector<Component*> components;	// behaviours of object

public:

	std::string name;					// name of object

						// scene owner of object
	Transform* transform;				// transform of object

	GameObject();

	/*
	* Get scene used by the object
	*/
	Scene* GetSceneOwner();

	/*
	* Get component using index of position list
	* @param i: index
	*/
	Component* GetComponentByIndex(int i);

	/*
	* Get number of components on gameObject
	*/
	int GetComponentsAmount();

	/*
	* Add new genereic component to object
	* @param: type of component (based of Polygon Component)
	*/
	template <class T>
	T* AddComponent() {

		Component* c = new T();

		c->gameObject = this;
		c->transform = transform;

		components.push_back(c);
		components.back()->OnStart();

		return (T*)components.back();
	}

	/*
	* get component of specified type
	*/
	template <class T>
	T* GetComponent() {

		for (auto& c : components) {

			// check if component type of object is equal to type of parameter
			if (typeid(T).name() == typeid(*c).name()) {

				return (T*)c;
			}
		}

		std::cout << name << ": component " << typeid(T).name() << " not finded";
		return nullptr;
	}

	/*
	* remove component of object
	* @param: type of component
	*/
	template <class T>
	void RemoveComponent() {

		for (auto& c : components) {

			// when find component, the loop is not closed because 
			// there may be another components of equal type

			if (typeid(T).name() == typeid(*c).name()) {

				c->OnRemove();
				components.erase(std::remove(components.begin(), components.end(), c));
			}
		}
	}
};