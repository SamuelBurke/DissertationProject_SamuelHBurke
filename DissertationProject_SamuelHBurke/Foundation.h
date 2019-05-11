#ifndef FOUNDATION_H
#define FOUNDATION_H

#include <memory>
#include <vector>

#include "Entity.h"
#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "Snake.h"

namespace Foundations
{

class Foundation
{
public:
	static std::shared_ptr<Foundation> Init();

	void Loop();
	void CleanUp();

	std::shared_ptr<Entity> AddEntity();

	template <typename T>
	std::shared_ptr<T> GetComponent();

private:
	bool m_quit;
	float m_deltaTime;
	float m_lastTime;
	float CalcDeltaTime();

	std::vector<std::shared_ptr<Entity>> m_entities;
	std::weak_ptr<Foundation> m_self;

	Window m_window;
	Input m_input;
};

template <typename T>
inline std::shared_ptr<T> Foundation::GetComponent()
{
	for (std::shared_ptr<Entity> e : m_entities)
	{
		if (e->GetComponent<T>())
		{
			return e->GetComponent<T>();
		}
	}

	throw std::exception();

}

}

#endif // !FOUNDATION_H
