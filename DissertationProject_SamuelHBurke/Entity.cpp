#include "Entity.h"

using namespace Foundations;

void Entity::Update(float _deltaTime)
{
	for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin(); it != m_components.end(); it++)
	{
		(*it)->OnUpdate(_deltaTime);
	}
}

void Entity::Display()
{
	for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin(); it != m_components.end(); it++)
	{
		(*it)->OnDisplay();
	}
}

std::shared_ptr<Foundation> Entity::GetFoundation()
{
	return m_foundation.lock();
}