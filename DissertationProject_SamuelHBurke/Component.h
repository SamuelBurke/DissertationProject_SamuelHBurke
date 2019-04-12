#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

namespace Foundations
{
class Entity;
class Foundation;
class Transform;
	
class Component
{
	friend class Entity;

public:
	virtual ~Component();

	std::shared_ptr<Foundation> GetFoundation();
	std::shared_ptr<Entity> GetEntity();
	std::shared_ptr<Transform> GetTransform();

private:
	std::weak_ptr<Entity> m_entity; // parent entity

	virtual void OnInit();
	virtual void OnUpdate(float _deltaTime);
	virtual void OnDisplay();
};
}

#endif // !COMPONENT_H
