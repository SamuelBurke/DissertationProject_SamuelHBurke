#ifndef ___WINDOW_H___
#define ___WINDOW_H___

#include <SDL2/SDL.h>

namespace Foundations
{

class Window
{
public:
	void InitWin();
	void ClearBuff();
	void SwapWin();

	SDL_Window* GetWindow();

	static int GetWidth();
	static int GetHeight();

private:
	bool InitGL();

	static int m_width;
	static int m_height;

	SDL_Window* m_window;
};

}

#endif // !___WINDOW_H___
