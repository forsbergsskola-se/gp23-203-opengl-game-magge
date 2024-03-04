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

int enemyCount[4]{10, 10, 10, 10};

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
	Player player{};
	EnemyManager enemyManager{};
	std::vector<GameObject*> gameObjects;

	gameObjects.push_back(&player);
	for(int y = 0; y < sizeof(enemyCount) / sizeof(int); y++)
		for (int i = 0; i < enemyCount[y]; i++)
		{
			auto* enemy = new Enemy{ i * 80 + 100, y * 80 + 30, &player};
			gameObjects.push_back(enemy);
			enemyManager.enemies.push_back(enemy);
		}

	for (int i = 0; i < player.projectileCount; i++)
	{
		auto* projectile = new Projectile{10};
		projectile->isActive = false;
		gameObjects.push_back(projectile);
		player.projectiles.push_back(projectile);
	}

	for (int i = 0; i < enemyManager.bombCount; i++)
	{
		auto* projectile = new Projectile{ 10 };
		projectile->isActive = false;
		gameObjects.push_back(projectile);
		enemyManager.bombs.push_back(projectile);
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
