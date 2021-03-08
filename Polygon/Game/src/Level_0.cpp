#include <Level_0.h>

#include <iostream>

#include <polygon/mesh.h>
#include <polygon/camera.h>
#include <polygon/pointLight.h>
#include <polygon/meshRenderer.h>

#include <sampleMaterial.h>

GameObject* player;
GameObject* camera;
GameObject* enemy;

GameObject* light;
GameObject* spot;

void level_0::OnStart() {

	// environment settings

	scene->environment->backgroundColor = glm::vec3(0.9, 0.9, 1.0);
	scene->environment->ambientColor = glm::vec3(0.4f);

	scene->sun->color = glm::vec3(1);
	scene->sun->intensity = 1.0f;
	scene->sun->SetRot(glm::vec3(-45, -45, 0));

	// adding objects

	camera = scene->AddDefaultCamera(glm::vec3(), glm::vec3());

	player = scene->AddGameObject(glm::vec3(2, 0.5, 3), glm::vec3());
	enemy = scene->AddGameObject(glm::vec3(0, 0, 0), glm::vec3());
	spot = scene->AddGameObject(glm::vec3(2, 2, 3), glm::vec3());

	CameraController* cameraController = camera->AddComponent<CameraController>();
	MeshRenderer* playerRenderer = player->AddComponent<MeshRenderer>();
	MeshRenderer* enemyRenderer = enemy->AddComponent<MeshRenderer>();
	SpotLight* spotLight = spot->AddComponent<SpotLight>();

	// setting lights

	spotLight->color = glm::vec3(1.0f, 0, 0);
	spotLight->angle = 30;
	spotLight->maxDistance = 3;
	spotLight->intensity = 1;

	for (int i = 1; i < 5; i++) {

		GameObject* l = scene->AddGameObject(glm::vec3((i * i) * 2, 2, 3), glm::vec3());
		PointLight* lc = l->AddComponent<PointLight>();

		lc->color = glm::vec3(1.0f);
		lc->maxDistance = 5;
		light = l;
	}

	// setting objects

	SampleMaterial* playerMaterial = new SampleMaterial();
	SampleMaterial* enemyMaterial = new SampleMaterial();

	playerRenderer->SetMaterial(playerMaterial);
	enemyRenderer->SetMaterial(enemyMaterial);
	playerRenderer->SetMesh(&primitives->CUBE);
	enemyRenderer->SetMesh(&primitives->PLANE);

	cameraController->moveSpeed = 10;
	cameraController->rotSpeed = 0.3f;

	camera->transform->SetPos(glm::vec3(0, 3, 10));
	enemy->transform->SetScale(glm::vec3(50, 0.1, 50));
	spot->transform->SetRot(glm::vec3(-90, 0, 0));

	playerMaterial->SetVec3("material.color", glm::vec3(1));
	enemyMaterial->SetVec3("material.color", glm::vec3(0.5f));

	playerMaterial->SetTexture("assets/box.png", true);
	enemyMaterial->SetTexture("assets/ground_01.png", true);

	playerMaterial->EnableMipmapping(false);
	enemyMaterial->EnableMipmapping(false);

	playerMaterial->specular = 1;
	enemyMaterial->specular = 0.4f;
}

void level_0::OnUpdate(float delta) {

	player->transform->Rotate(glm::vec3(0, delta * 50, 0));
	//player->transform->Move(glm::vec3(delta * 2, 0, 0));

	spot->transform->Rotate(glm::vec3(delta * 50, 0, 0));

	if (glfwGetKey(screen->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {

		light->RemoveComponent<PointLight>();
	}
}