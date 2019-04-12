#include "Input.h"

using namespace Foundations;

void Input::Update()
{
	m_currentKey = SDL_GetKeyboardState(NULL);
}

bool Input::isKeyPressed(SDL_Scancode _keyCode)
{
	if (m_currentKey[_keyCode])
	{
		return true; 
	}
	else
	{ 
		return false;
	}
}