#include "Component.h"
#include "Entity.h"

#include <iostream>

using namespace Foundations;

Component::~Component()
{
}

void Component::OnInit()
{
}

void Component::OnUpdate(float _deltaTime)
{
	std::cout << "working" << std::endl;
}

void Component::OnDisplay()
{
}

std::shared_ptr<Entity> Component::GetEntity()
{
	return m_entity.lock();
}

std::shared_ptr<Foundation> Component::GetFoundation()
{
	return GetEntity()->GetFoundation();
}
