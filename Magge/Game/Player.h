#pragma once
#include "Mesh.h"
#include "Input.h"
#include "Window.h"
#include "GameObject.h"

class Player : public GameObject
{
public:

	Player() : GameObject{ Window::SCREEN_WIDTH / 2, Window::SCREEN_HEIGHT - 100, 50, 50 }
	{

	}


	void PlayerInput(const Uint8* currentKeyStates)
	{

		if (currentKeyStates[SDL_SCANCODE_SPACE])
		{
			//Shoot
			printf("PEW PEW!");
		}

		if (currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			velX = 0;
			return;
		}

		if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			velX = -moveSpeed;
			return;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			velX = moveSpeed;
			return;
		}


		velX = 0;
	}


	void Move(int posX, int posY)
	{
		mesh.rect.x = posX;
		mesh.rect.y = posY;
	}

	void Update()
	{
		int mPosX = mesh.rect.x + velX;
		int mPosY = mesh.rect.y + velY;

		if ((mPosX < 0) || (mPosX + mesh.rect.w > Window::SCREEN_WIDTH))
		{
			//Move back
			mPosX -= velX;
		}

		//If the dot went too far up or down
		if ((mPosY < 0) || (mPosY + mesh.rect.h > Window::SCREEN_HEIGHT))
		{
			//Move back
			mPosY -= velY;
		}
		Move(mPosX, mPosY);
	}

};

