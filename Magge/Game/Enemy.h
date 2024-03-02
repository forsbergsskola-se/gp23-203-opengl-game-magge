#pragma once
#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
	Player* player;

	float moveDelay;
	Time moveTimer{};

	Enemy(int xPos, int yPos, Player* p) : GameObject{ xPos, yPos, 50, 50 }
	{
		this->player = p;
		moveDelay = 1.0f;
		moveTimer.Start();

		velX = 25;
		velY = 25;
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
	}

	bool IsNearWall()
	{
		if (velX > 0 && mesh.rect.x >= Window::SCREEN_WIDTH - mesh.rect.w)
		{
			return true;
		}
		else if (velX < 0 && mesh.rect.x <= 0 + mesh.rect.w)
		{
			return true;
		}

		return false;

	}

};

