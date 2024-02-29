#pragma once

#include <SDL.h>
#include <stdio.h>

class Window
{
	//Screen dimension constants
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;


	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;


public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	Window()
	{
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create window
			window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get window surface
				screenSurface = SDL_GetWindowSurface(window);

				//Fill the surface white
				SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

				//Update the surface
				SDL_UpdateWindowSurface(window);

				//Hack to get window to stay up
				SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
			}
		}


	}

	~Window()
	{
		
	}

	bool LoadMedia()
	{
		//Loading success flag
		bool success = true;

		//Load splash image
		screenSurface = SDL_LoadBMP("Resources/cat.bmp");
		if (screenSurface == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
			success = false;
		}

		return success;
	}

	void Close()
	{
		//Deallocate surface
		SDL_FreeSurface(screenSurface);
		screenSurface = NULL;

		//Destroy window
		SDL_DestroyWindow(window);
		window = NULL;

		//Quit SDL subsystems
		SDL_Quit();
	}

};

