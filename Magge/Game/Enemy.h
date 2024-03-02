#pragma once
#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
	Player* player;


	Enemy(int xPos, int yPos, Player* p) : GameObject{ xPos, yPos, 50, 50 }
	{
		this->player = p;
		printf("Construct Enemy");
	}


	virtual void Update() override
	{
		for (Projectile* projectile : player->projectiles)
		{
			if (IsColliding(projectile->collider))
			{
				projectile->isActive = false;
				isActive = false;
			}
		}
	}

};

