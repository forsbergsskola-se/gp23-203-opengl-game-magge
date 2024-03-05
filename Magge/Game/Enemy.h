#pragma once
#include "GameObject.h"
#include "Time.h"
#include "Projectile.h"
#include "ProjectilePool.h"
#include "EnemyManager.h"

class EnemyManager;
class Color;

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
	ProjectilePool* projectiles;
	EnemyManager* enemyManager;
public:

	Enemy(int xPos, int yPos, ProjectilePool* projectiles, EnemyManager* em, std::string path) : GameObject{ xPos, yPos, 50, 50, path, true}
	{
		moveTimer.Start();

		velX = 35;
		velY = 65;
		moveDelay = 1.0f;

		this->projectiles = projectiles;
		enemyManager = em;

	}


	virtual void Update() override
	{
		if(IsTimeToMove())
			Move(mesh.rect.x + velX, mesh.rect.y);

		for (Projectile* projectile : projectiles->pooledObjects)
		{
			if (!projectile->isActive)
				continue;

			if (IsColliding(projectile->collider))
			{
				projectile->isActive = false;
				isActive = false;
				enemyManager->OnEnemyDeath();
			}
		}
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

	bool ReachBottomEvent()
	{
		if (mesh.rect.y > Window::SCREEN_HEIGHT - 170)
			return true;

		return false;
	}

	
};

