/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include "Texture.h"
#include "Player.h"
#include "Input.h"
#include "Time.h"

//Event handler
SDL_Event e;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

int main( int argc, char* args[] )
{
	Window window{};
	Time time{};
	Time capTimer{};
	time.Start();
	int countedFrames = 0;


	Player player{};
	//Input input{ };

    //SDL_Surface* imageSurface = SDL_LoadBMP("Resources/cat.bmp");
	Texture texture{ "Resources/image.png", window.renderer};
	Mesh mesh1{100, 100, 50, 50};
	Mesh mesh2{ 30, 30, 30, 30 };




	bool quit = false;

	while (!quit)
	{
		window.Clear();
		capTimer.Start();

		player.mesh->Render(window.renderer);


		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			Key key = Input::KeyPressed(e.key.keysym.sym);

			player.PlayerInput(e, key);

			//User requests quit
			if (e.type == SDL_QUIT || key == Key::Escape)
				quit = true;
		}

		//Update screen
		SDL_RenderPresent(window.renderer);

		//Calculate and correct fps
		float avgFPS = countedFrames / (time.GetTicks() / 1000.f);
		if (avgFPS > 2000000)
			avgFPS = 0;
		
		player.Update();

		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.GetTicks();
		if (frameTicks < SCREEN_TICK_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
		}

	}

	window.Close();

	return 0;
}
