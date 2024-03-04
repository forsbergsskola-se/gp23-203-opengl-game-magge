#pragma once
#include <vector>
#include "Enemy.h"
#include "Projectile.h"
#include "Time.h"
#include <SDL.h>
#include <cstdlib>

class EnemyManager
{
public:
	std::vector<Enemy*> enemies;
	std::vector<Projectile*> bombs;

	const int bombCount = 20;
	const int minShootDelay = 20;
	const int maxShootDelay = 100;
	float shootDelay;
	Time shootTimer{};

	EnemyManager()
	{
		srand(SDL_GetTicks());
		shootTimer.Start();
		
		shootDelay = (std::rand() % (maxShootDelay - minShootDelay) + minShootDelay) * 0.01f;
	}
	~EnemyManager()
	{
	}

	void Update()
	{
		CheckWallEvent();

		if (shootTimer.GetTicks() >= shootDelay * 1000)
		{
			shootTimer.Stop();
			shootTimer.Start();

		}
	}
	
	void CheckWallEvent()
	{
		for (Enemy* enemy : enemies)
		{
			if (enemy->IsNearWall())
			{
				for (Enemy* enemy : enemies)
				{
					enemy->ReachWallEvent();
				}
				break;
			}
		}
	}

};