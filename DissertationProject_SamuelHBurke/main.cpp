#include "Foundation.h"

#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
	std::shared_ptr<Foundations::Foundation> foundation = Foundations::Foundation::Init();
	std::shared_ptr<Foundations::Entity> player = foundation->AddEntity();
	std::shared_ptr<Foundations::Component> test = player->AddComponent<Foundations::Component>();

	foundation->Loop();

	return 0;
}