#include "Foundation.h"

using namespace Foundations;

std::shared_ptr<Foundation> Foundation::Init()
{
	std::shared_ptr<Foundation> rtn = std::make_shared<Foundation>();

	rtn->m_quit = true;

	rtn->m_window.InitWin();

	return rtn;
}

void Foundation::Loop()
{
	m_quit = false;

	while (!m_quit)
	{
		//m_input.Update();

		SDL_Event e = { 0 };

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				CleanUp();
			}
		}

		float deltaTime = 0;

		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		{
			(*it)->Update(deltaTime);
		}

		m_window.ClearBuff();

		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		{
			(*it)->Display();
		}

		m_window.SwapWin();

		//if (m_input.isKeyPressed(SDL_SCANCODE_ESCAPE))
		//{
		//	CleanUp();
		//}

	}
}

void Foundation::CleanUp()
{
	m_quit = true;
}

std::shared_ptr<Entity> Foundation::AddEntity()
{
	std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
	m_entities.push_back(rtn);
	rtn->m_self = rtn;
	rtn->m_foundation = m_self;

	return rtn;
}