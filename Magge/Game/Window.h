#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "String"


class Window
{
	//The surface contained by the window
	SDL_Surface* imageSurface = NULL;


public:
	//Screen dimension constants
	static const int SCREEN_WIDTH = 1920;
	static const int SCREEN_HEIGHT = 1080;
	//The window we'll be rendering to
	SDL_Surface* screenSurface = NULL;
	SDL_Window* window = NULL;

	Window();
	static SDL_Renderer* renderer;

	~Window()
	{
		
	}


	void Clear()
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
	}

	void Close()
	{
		//Deallocate surface
		SDL_FreeSurface(imageSurface);
		imageSurface = NULL;

		//Destroy window
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		window = NULL;
		renderer = NULL;

		//Quit SDL subsystems
		IMG_Quit();
		SDL_Quit();
	}

};

