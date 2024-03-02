/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include "Texture.h"
#include "Player.h"
#include "Enemy.h"
#include "Input.h"
#include "Time.h"
#include <vector>

//Event handler
SDL_Event e;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

int enemyCount = 20;
int projectilePoolCount = 20;

int main( int argc, char* args[] )
{
	Window window{};
	Time time{};
	Time capTimer{};
	time.Start();
	int countedFrames = 0;
	Player player{};

	std::vector<GameObject*> gameObjects;

	gameObjects.push_back(&player);

	for (int i = 0; i < enemyCount; i++)
	{
		auto* enemy = new Enemy{ i * 80, 30, &player};
		gameObjects.push_back(enemy);
	}

	for (int i = 0; i < projectilePoolCount; i++)
	{
		auto* projectile = new Projectile{};
		projectile->isActive = false;
		gameObjects.push_back(projectile);
		player.projectiles.push_back(projectile);
	}

	bool quit = false;

	while (!quit)
	{
		window.Clear();
		capTimer.Start();

		for (GameObject* go : gameObjects)
		{
			go->Render();
		}

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
		//player.Update();
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
