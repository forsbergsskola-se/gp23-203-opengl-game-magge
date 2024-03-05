#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include <vector>
#include "Time.h"
#include "Player.h"
#include "Enemy.h"
#include "Texture.h"

//Event handler
SDL_Event e;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

class EnemyManager;
class Player;
class Enemy;
class Projectile;
class GameObject;

int main( int argc, char* args[] )
{
	Window window{};
	SDL_Rect* rect = new SDL_Rect{ 0, 0, Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT };
	Texture background{ "Resources/Space.png", Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT, new Color{255, 255, 255} };

	//Time
	Time time{};
	Time capTimer{};
	time.Start();
	int countedFrames = 0;

	//Game Objects
	std::vector<GameObject*> gameObjects;

	ProjectilePool* projectilePool = new ProjectilePool(20, 10, "Resources/projectile.png", 15, 45, true, &gameObjects);
	ProjectilePool* bombPool = new ProjectilePool(20, -7, "Resources/bomb.png", 25, 25, false, &gameObjects);

	Player player{&gameObjects, projectilePool, bombPool};
	EnemyManager enemyManager{&gameObjects, projectilePool, bombPool};


	bool quit = false;

	while (!quit)
	{
		window.Clear();
		capTimer.Start();

		background.Render(*rect);

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
