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
	GameObject gameObject{ 50, Window::SCREEN_HEIGHT + 100, 50, 50 };


	bool quit = false;

	while (!quit)
	{
		window.Clear();
		capTimer.Start();

		player.Render();
		gameObject.Render();

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			Key key = Input::KeyPressed(e.key.keysym.sym);

			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			player.PlayerInput(currentKeyStates);

			//User requests quit
			if (e.type == SDL_QUIT || key == Key::Escape)
				quit = true;

		}
		player.Update();

		//Update screen
		SDL_RenderPresent(window.renderer);


		++countedFrames;
		capTimer.CapFPS(SCREEN_TICK_PER_FRAME);
	}

	window.Close();

	return 0;
}
