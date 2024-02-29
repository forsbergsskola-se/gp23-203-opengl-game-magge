/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"


int main( int argc, char* args[] )
{
	Window window{};

    SDL_Surface* imageSurface = SDL_LoadBMP("Resources/cat.bmp");
 
	window.RenderImage(imageSurface);


	window.Close();

	return 0;
}
