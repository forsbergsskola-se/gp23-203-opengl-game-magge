#pragma once
#include <SDL.h>
#include "Window.h"

class Mesh
{
public:
	SDL_Rect rect;

	Mesh(int x, int y, int w, int h)
	{
		rect = { x, y, w, h};
		
	}

	void Render(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x99, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &rect);
	}
};

