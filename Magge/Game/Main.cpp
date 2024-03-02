/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include "Player.h"
#include "Enemy.h"
#include "Input.h"
#include "Time.h"
#include <vector>
#include "Enemy.h"

//Event handler
SDL_Event e;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

int enemyCount[4]{10, 10, 10, 10};
int projectilePoolCount = 20;

int main( int argc, char* args[] )
{
	Window window{};

	Texture background{ "Resources/Space.png", window.renderer };

	Time time{};
	Time capTimer{};
	time.Start();
	int countedFrames = 0;
	Player player{};


	std::vector<GameObject*> gameObjects;
	std::vector<Enemy*> enemies;

	gameObjects.push_back(&player);
	for(int y = 0; y < sizeof(enemyCount) / sizeof(int); y++)
		for (int i = 0; i < enemyCount[y]; i++)
		{
			auto* enemy = new Enemy{ i * 80 + 100, y * 80 + 30, &player};
			gameObjects.push_back(enemy);
			enemies.push_back(enemy);
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

		background.Render();

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
		for (Enemy* enemy : enemies)
		{
			if (enemy->IsNearWall())
			{
				for (Enemy* enemy : enemies)
				{
					enemy->ReachWallEvent();
				}
				break;
			}
		}
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
