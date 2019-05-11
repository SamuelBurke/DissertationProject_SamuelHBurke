#include "Foundation.h"
//#include "AudioMaster.h"

using namespace Foundations;

std::shared_ptr<Foundation> Foundation::Init()
{
	std::shared_ptr<Foundation> rtn = std::make_shared<Foundation>();
	rtn->m_quit = true;
	rtn->m_self = rtn;


	rtn->m_deltaTime = 0;
	rtn->m_lastTime = SDL_GetTicks();

	rtn->m_window.InitWin();

	return rtn;
}

void Foundation::Loop()
{
	m_quit = false;

	while (!m_quit)
	{
		m_input.Update();

		SDL_Event e = { 0 };

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				CleanUp();
			}
		}

		float deltaTime = CalcDeltaTime();

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

		if (m_input.isKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			CleanUp();
		}

	}
}

void Foundation::CleanUp()
{
	m_quit = true;
}

float Foundation::CalcDeltaTime()
{
	float time = SDL_GetTicks();
	float difference = time - m_lastTime;
	m_deltaTime = difference / 1000.0f;
	m_lastTime = time;

	return m_deltaTime;
}

std::shared_ptr<Entity> Foundation::AddEntity()
{
	std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
	m_entities.push_back(rtn);
	rtn->m_self = rtn;
	rtn->m_foundation = m_self;

	return rtn;
}