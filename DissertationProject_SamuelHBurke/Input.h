#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

namespace Foundations
{

class Input
{
public:
	void Update();
	bool isKeyPressed(SDL_Scancode _keyCode);

private:
	const Uint8* m_currentKey;
	
};

}
#endif // !INPUT_H
