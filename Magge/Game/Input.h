#pragma once
#include <SDL.h>


//Key press surfaces constants
enum Key
{
	Up,
	Down,
	Left,
	Right,
	Space,
	Escape,

	Null

};

class Input
{
public:
	Key KeyPressed(SDL_Keycode input) const
	{
		switch (input)
		{
			case SDLK_LEFT: return Left;
			case SDLK_RIGHT: return Right;
			case SDLK_UP: return Up;
			case SDLK_DOWN: return Down;
			case SDLK_SPACE: return Space;
			case SDLK_ESCAPE: return Escape;

			default: return Null;
		}
	}
};

// May need to add a constructor initialising all keys?

