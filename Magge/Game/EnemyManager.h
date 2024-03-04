#pragma once
#include <vector>
#include "Enemy.h"
#include "Projectile.h"
#include "Time.h"
#include <SDL.h>
#include <cstdlib>

class EnemyManager
{
	const int minShootDelay = 20;
	const int maxShootDelay = 100;
	float shootDelay;
	Time shootTimer{};

public:
	std::vector<Enemy*> enemies;
	std::vector<Projectile*> bombs;
	int enemyCount[4]{ 10, 10, 10, 10 };

	const int bombCount = 20;

	EnemyManager(std::vector<GameObject*>* gameObjectList, Player* player)
	{
		srand(SDL_GetTicks());
		shootTimer.Start();
		
		shootDelay = (std::rand() % (maxShootDelay - minShootDelay) + minShootDelay) * 0.01f;


		for (int y = 0; y < sizeof(enemyCount) / sizeof(int); y++)
			for (int i = 0; i < enemyCount[y]; i++)
			{
				auto* enemy = new Enemy{ i * 80 + 100, y * 80 + 30, player};
				gameObjectList->push_back(enemy);
				enemies.push_back(enemy);
			}

		for (int i = 0; i < bombCount; i++)
		{
			auto* projectile = new Projectile{ 10 };
			projectile->isActive = false;
			gameObjectList->push_back(projectile);
			bombs.push_back(projectile);
		}

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

			shootDelay = (std::rand() % (maxShootDelay - minShootDelay) + minShootDelay);

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