#include "Component.h"
#include "Entity.h"
#include "Transform.h"

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

std::shared_ptr<Transform> Component::GetTransform()
{
	return GetEntity()->GetComponent<Transform>();
}