#pragma once
#include "Mesh.h"
#include "Input.h"
#include "Window.h"
#include "GameObject.h"
#include "Projectile.h"
#include <vector>
#include "Time.h"

class Player : public GameObject
{
public:

	std::vector<Projectile*> projectiles;
	float shootCooldown;
	Time shootTimer{};
	int projectileCount = 20;


	Player(std::vector<GameObject*>* gameObjectList) : GameObject{ Window::SCREEN_WIDTH / 2, Window::SCREEN_HEIGHT - 100, 50, 50 }
	{
		shootCooldown = 0.5f;

		gameObjectList->push_back(this);


		for (int i = 0; i < projectileCount; i++)
		{
			auto* projectile = new Projectile{ 10 };
			projectile->isActive = false;
			gameObjectList->push_back(projectile);
			projectiles.push_back(projectile);
		}
	}


	void PlayerInput(const Uint8* currentKeyStates)
	{


		if (currentKeyStates[SDL_SCANCODE_SPACE])
		{

			if (!shootTimer.IsStarted() || shootTimer.GetTicks() >= shootCooldown * 1000)
			{
				shootTimer.Stop();
				shootTimer.Start();

				//Object Pooling
				for (Projectile* projectile : projectiles)
				{
					if (!projectile->isActive)
					{
						projectile->isActive = true;
						projectile->Move(mesh.rect.x, mesh.rect.y);
						break;
					}
				}
			}

			
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


	

	virtual void Update() override
	{
		int mPosX = mesh.rect.x + velX;
		int mPosY = mesh.rect.y + velY;
		//printf("%d\n", mPosX);

		if ((mPosX < 0) || (mPosX + mesh.rect.w > Window::SCREEN_WIDTH))
		{
			//Move back
			mPosX -= velX;
		}

		if ((mPosY < 0) || (mPosY + mesh.rect.h > Window::SCREEN_HEIGHT))
		{
			//Move back
			mPosY -= velY;
		}
		Move(mPosX, mPosY);
	}

};

