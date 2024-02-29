/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include "Input.h"
#include "String"
#include "Texture.h"


//Event handler
SDL_Event e;

int main( int argc, char* args[] )
{
	Window window{};
	Input input{};



    //SDL_Surface* imageSurface = SDL_LoadBMP("Resources/cat.bmp");
	Texture texture{ "Resources/image.png", window.renderer};


	bool quit = false;

	while (!quit)
	{
		

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			Key key = input.KeyPressed(e.key.keysym.sym);

			if (key == Key::Up)
			{
				//window.RenderImage("Resources/image.png");
				texture.Render();
			}
			else if (key == Key::Down)
			{
			}
			//User requests quit
			if (e.type == SDL_QUIT || key == Key::Escape)
			{
				quit = true;
			}
		}

		
	}

	window.Close();

	return 0;
}
