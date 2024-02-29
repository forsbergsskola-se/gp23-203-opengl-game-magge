#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "String"
#include "Texture.h"


class Window
{
	//Screen dimension constants
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;


	//The surface contained by the window
	SDL_Surface* imageSurface = NULL;


public:
	//The window we'll be rendering to
	SDL_Surface* screenSurface = NULL;
	SDL_Window* window = NULL;

	SDL_Renderer* renderer;

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
			window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					}
				}

				//Get window surface
				screenSurface = SDL_GetWindowSurface(window);

				//Fill the surface white
				SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			}
		}

	}

	~Window()
	{
		
	}



	//bool LoadMedia(std::string path)
	//{
	//	//Loading success flag
	//	bool success = true;

	//	//Load splash image
	//	Texture texture{ path, renderer};
	//	if (texture.texture == NULL)
	//	{
	//		printf("Unable to load texture %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
	//		success = false;
	//	}

	//	return success;
	//}

	//void RenderImage(std::string path)
	//{
	//	if (LoadMedia(path))
	//	{
	//		//Apply the image
	//		SDL_BlitSurface(imageSurface, NULL, screenSurface, NULL);

	//		//Update the surface
	//		SDL_UpdateWindowSurface(window);

	//	}
	//}



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

