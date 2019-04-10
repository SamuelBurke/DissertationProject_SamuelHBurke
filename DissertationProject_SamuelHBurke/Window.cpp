#include "Window.h"

#include <iostream>

#include <GL/glew.h>

using namespace Foundations;

int Window::m_width = 920;
int Window::m_height = 920;

bool Window::InitGL()
{
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: Glew failed to initalise: " << glewGetErrorString(err) << std::endl;
		return false;
	}

	return true;
}

void Window::InitWin()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Error: Cannot initialise SDL" << std::endl;

		throw std::exception();
	}

	//Major version number 4
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	//Minor version number 3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	m_window = SDL_CreateWindow("Dissertation Project - Samuel H. Burke",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		m_width, m_height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(m_window))
	{
		throw std::exception();
	}

	if (!InitGL())
	{
		throw std::exception();
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void Window::ClearBuff()
{
	SDL_GetWindowSize(m_window, &m_width, &m_height);
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapWin()
{
	SDL_GL_SwapWindow(m_window);
}

int Window::GetWidth()
{
	return m_width;
}

int Window::GetHeight()
{
	return m_height;
}

SDL_Window* Window::GetWindow()
{
	return m_window;
}