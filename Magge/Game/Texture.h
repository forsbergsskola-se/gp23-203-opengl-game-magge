#pragma once
#include "Window.h"
#include <SDL_image.h>
#include "String"


class Texture
{
	SDL_Renderer* renderer;
	static SDL_Texture* texture;
public:

	Texture(std::string path, SDL_Renderer* renderer)
	{
		this->renderer = renderer;
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			//Create texture from surface pixels
			texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (texture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);

			
		}
	}

	~Texture() 
	{
		if (texture != NULL)
		{
			SDL_DestroyTexture(texture);
			texture = NULL;
		}
	}


	// We may need params here to render a texture at a specific point
	// Render( int x, int y, SDL_Rect* clip) See "CLip rendering and Sprite Sheets"
	void Render()
	{
		//Clear screen
		SDL_RenderClear(renderer);

		//Render texture to screen
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		
	}

};

