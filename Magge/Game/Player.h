#pragma once
#include "Mesh.h"
#include "Input.h"

class Player
{
public:

	Mesh* mesh;
	int moveSpeed = 10;

	int velX;
	int velY;

	Player()
	{
		mesh = new Mesh{600, 600, 50, 50};
		velX = 0;
		velY = 0;
	}


	void PlayerInput(SDL_Event& e, Key& key)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{

			if (key == Key::Up)
			{
				velY = -moveSpeed;
				printf("Men hallå?");

			}
			else if (key == Key::Down)
			{
				velY = moveSpeed;
			}

			if (key == Key::Left)
			{
				velX = -moveSpeed;
			}
			else if (key == Key::Right)
			{
				velX = moveSpeed;
			}
				
		}
		////If a key was released
		//else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		//{
		//	velX = 0;
		//	velY = 0;
		//}

	}

	void Update()
	{
		mesh->rect.x += velX;
		mesh->rect.y += velY;
	}

};

