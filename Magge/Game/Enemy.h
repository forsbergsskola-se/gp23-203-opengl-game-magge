#pragma once
#include "GameObject.h"
#include "Time.h"
#include "Projectile.h"
#include "ProjectilePool.h"

class EnemyManager;

class Enemy : public GameObject
{
	bool IsTimeToMove()
	{
		if (moveTimer.GetTicks() >= moveDelay * 1000)
		{
			moveTimer.Stop();
			moveTimer.Start();

			return true;
		}

		return false;
	}

	float moveDelay = 1.0f;
	Time moveTimer{};
	const float delayMultiplier = 0.8f;
	EnemyManager* enemyManager;

public:

	Enemy(int xPos, int yPos, EnemyManager* em) : GameObject{ xPos, yPos, 50, 50 }
	{
		moveTimer.Start();

		velX = 25;
		velY = 25;
		moveDelay = 1.0f;

		enemyManager = em;
	}


	virtual void Update() override
	{
		if(IsTimeToMove())
			Move(mesh.rect.x + velX, mesh.rect.y);

		//printf("%d", enemyManager->bombCount);

		//for (Projectile* projectile : enemyManager->projectiles->pooledObjects)
		//{
		//	if (!projectile->isActive)
		//		continue;

		//	if (IsColliding(projectile->collider))
		//	{
		//		projectile->isActive = false;
		//		isActive = false;
		//	}
		//}
	}

	

	bool IsNearWall() const
	{
		if (velX > 0 && mesh.rect.x >= Window::SCREEN_WIDTH - mesh.rect.w - 20)
		{
			return true;
		}
		else if (velX < 0 && mesh.rect.x <= 0 + mesh.rect.w + 20)
		{
			return true;
		}

		return false;

	}

	void ReachWallEvent()
	{
		if (!IsTimeToMove())
			return;

		velX = -velX;

		Move(mesh.rect.x, mesh.rect.y + velY);
		moveDelay *= delayMultiplier;

		moveTimer.Stop();
		moveTimer.Start();
	}

	
};

