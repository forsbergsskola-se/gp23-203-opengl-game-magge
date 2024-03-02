#pragma once
#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
	Player* player;

	float moveDelay = 1.0f;
	Time moveTimer{};
	const float delayMultiplier = 0.9f;

	Enemy(int xPos, int yPos, Player* p) : GameObject{ xPos, yPos, 50, 50 }
	{
		this->player = p;
		moveTimer.Start();

		velX = 25;
		velY = 25;
		moveDelay = 1.0f;
	}

	void CheckMove()
	{
		if (moveTimer.GetTicks() >= moveDelay * 1000)
		{
			moveTimer.Stop();
			moveTimer.Start();

			Move(mesh.rect.x + velX, mesh.rect.y);
		}
	}

	virtual void Update() override
	{
		CheckMove();

		for (Projectile* projectile : player->projectiles)
		{
			if (!projectile->isActive)
				continue;

			if (IsColliding(projectile->collider))
			{
				projectile->isActive = false;
				isActive = false;
			}
		}
	}


	void ReachWallEvent()
	{
		velX = -velX;
		Move(mesh.rect.x, mesh.rect.y + velY);
		moveDelay *= delayMultiplier;
	}

	bool IsNearWall()
	{
		if (velX > 0 && mesh.rect.x >= Window::SCREEN_WIDTH - mesh.rect.w - 30)
		{
			return true;
		}
		else if (velX < 0 && mesh.rect.x <= 0 + mesh.rect.w + 30)
		{
			return true;
		}

		return false;

	}

};

