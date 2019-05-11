#include "Foundation.h"
#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"

#include "Snake.h"

#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
	std::shared_ptr<Foundations::Foundation> foundation = Foundations::Foundation::Init();
	std::shared_ptr<Foundations::Entity> player = foundation->AddEntity();
	std::shared_ptr<Foundations::Entity> camera = foundation->AddEntity();

	std::shared_ptr<Foundations::Camera> cam = camera->AddComponent<Foundations::Camera>();
	std::shared_ptr<Foundations::Transform> trans = camera->AddComponent<Foundations::Transform>();

	std::shared_ptr<Foundations::Transform> transform = player->AddComponent<Foundations::Transform>();
	std::shared_ptr<Game::Snake> snake = player->AddComponent<Game::Snake>();
	std::shared_ptr<Foundations::MeshRenderer> meshRenderer = player->AddComponent<Foundations::MeshRenderer>();

	foundation->Loop();

	return 0;
}