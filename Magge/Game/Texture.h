#pragma once
#include <SDL_image.h>
#include "String"
#include <SDL.h>
#include "Window.h"
#include "Color.h"
#include <SDL_ttf.h>

class Texture
{
	SDL_Texture* texture;
	Color* color;

	TTF_Font* font;
public:

	Texture(std::string path, int w, int h, Color* c)
	{
		color = c;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			//Create texture from surface pixels
			texture = SDL_CreateTextureFromSurface(Window::renderer, loadedSurface);

			if (texture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	}

	Texture(std::string textureText, Color* c)
	{
		TTF_Init();


		//Set Font
		font = TTF_OpenFont("Resources/pixel.ttf", 10);
		color = c;

		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), SDL_Color{ c->r, c->g, c->b });
		if (textSurface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			//Create texture from surface pixels
			texture = SDL_CreateTextureFromSurface(Window::renderer, textSurface);
			if (texture == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			
			//Get rid of old surface
			SDL_FreeSurface(textSurface);
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
	void Render(SDL_Rect currentRect)
	{
		//Render texture to screen
		SDL_RenderCopy(Window::renderer, texture, NULL, &currentRect);
		SDL_SetTextureColorMod(texture, color->r, color->g, color->b);
	}

};

