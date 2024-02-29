/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include "Input.h"
#include "String"
#include "Texture.h"
#include "Mesh.h"

//Event handler
SDL_Event e;

int main( int argc, char* args[] )
{
	Window window{};
	Input input{};



    //SDL_Surface* imageSurface = SDL_LoadBMP("Resources/cat.bmp");
	Texture texture{ "Resources/image.png", window.renderer};
	Mesh mesh1{100, 100, 50, 50};
	Mesh mesh2{ 30, 30, 30, 30 };




	bool quit = false;

	while (!quit)
	{
		window.Clear();
		mesh1.Render(window.renderer);


		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{

			Key key = input.KeyPressed(e.key.keysym.sym);



			if (key == Key::Up)
			{
				//texture.Render();
				mesh1.fillRect.y-=10;

			}
			else if (key == Key::Down)
			{
				mesh1.fillRect.y+=10;
			}
			else if (key == Key::Left)
			{
				mesh1.fillRect.x-=10;
				//mesh2.Render(window.renderer);
			}
			else if (key == Key::Right)
			{
				mesh1.fillRect.x+=10;
				//mesh2.Render(window.renderer);
			}
			//User requests quit
			if (e.type == SDL_QUIT || key == Key::Escape)
			{
				quit = true;
			}

			

			//Update screen
			SDL_RenderPresent(window.renderer);
		}

		
	}

	window.Close();

	return 0;
}
