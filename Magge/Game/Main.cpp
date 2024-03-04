/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include <vector>
#include "Input.h"
#include "Time.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"


//Event handler
SDL_Event e;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

class EnemyManager;
class Player;


int main( int argc, char* args[] )
{
	Window window{};
	Texture background{ "Resources/Space.png", window.renderer };

	//Time
	Time time{};
	Time capTimer{};
	time.Start();
	int countedFrames = 0;

	//Game Objects
	std::vector<GameObject*> gameObjects;
	Player player{&gameObjects};
	EnemyManager enemyManager{&gameObjects, &player};


	bool quit = false;

	while (!quit)
	{
		window.Clear();
		capTimer.Start();

		background.Render();

		for (GameObject* go : gameObjects)
		{
			go->Render();
		}

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			player.PlayerInput(currentKeyStates);

			//User requests quit
			if (e.type == SDL_QUIT || currentKeyStates[SDL_SCANCODE_ESCAPE])
				quit = true;

		}

		enemyManager.Update();
		for (GameObject* go : gameObjects)
		{
			if(go->isActive)
				go->Update();

		}


		//Update screen
		SDL_RenderPresent(window.renderer);

		++countedFrames;
		capTimer.CapFPS(SCREEN_TICK_PER_FRAME);
	}

	window.Close();

	return 0;
}
