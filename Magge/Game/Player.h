#pragma once
#include "Mesh.h"
#include "Input.h"
#include "Window.h"
#include "GameObject.h"
#include "Projectile.h"
#include <vector>
#include "ProjectilePool.h"
#include "Time.h"
#include "Sound.h"

class Color;
class Sound;

class Player : public GameObject
{
	float shootCooldown;
	Time shootTimer{};
	int projectileCount;
	bool isShooting;
	Sound* shootSound;

public:
	ProjectilePool* projectiles;
	ProjectilePool* bombs;

	int hp;
	bool isTakingDamage;
	Time damageTimer{};
	float damageDuration;

	Player(std::vector<GameObject*>* gameObjectList, ProjectilePool* projectiles, ProjectilePool* bombs) : GameObject{ Window::SCREEN_WIDTH / 2, Window::SCREEN_HEIGHT - 100, 50, 50, "Resources/spaceship.png", false}
	{
		shootCooldown = 0.8f;
		hp = 3;
		damageDuration = 1.0f;
		isShooting = false;
		projectileCount = projectiles->count;
		isTakingDamage = false;

		gameObjectList->push_back(this);

		this->projectiles = projectiles;
		this->bombs = bombs;

		shootSound = new Sound{"Resources/pewpew.wav", false};
	}


	void PlayerInput(const Uint8* currentKeyStates)
	{
		isShooting = currentKeyStates[SDL_SCANCODE_SPACE];


		if (currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_RIGHT])
			velX = 0;
		else if (currentKeyStates[SDL_SCANCODE_LEFT])
			velX = -moveSpeed;
		else if (currentKeyStates[SDL_SCANCODE_RIGHT])
			velX = moveSpeed;
		else
			velX = 0;
	}


	void Shoot()
	{
		shootTimer.Stop();
		shootTimer.Start();

		shootSound->Play();

		//Object Pooling
		for (Projectile* projectile : projectiles->pooledObjects)
		{
			if (!projectile->isActive)
			{
				projectile->isActive = true;
				projectile->Move(mesh.rect.x, mesh.rect.y);
				break;
			}
		}
	}



	virtual void Update() override
	{
		if (isShooting)
			if (!shootTimer.IsStarted() || shootTimer.GetTicks() >= shootCooldown * 1000)
				Shoot();


		int mPosX = mesh.rect.x + velX;
		int mPosY = mesh.rect.y + velY;

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


		for (Projectile* bomb : bombs->pooledObjects)
		{
			if (!bomb->isActive)
				continue;

			if (IsColliding(bomb->collider))
			{
				bomb->isActive = false;
				TakeDamage();
			}
		}
	}

	void TakeDamage()
	{
		hp--;
		isTakingDamage = true;
		damageTimer.Start();

		if (hp <= 0)
			isActive = false;
	}


};

