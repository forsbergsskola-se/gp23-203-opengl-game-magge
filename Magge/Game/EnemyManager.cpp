#include "EnemyManager.h"
#include "Enemy.h"


EnemyManager::EnemyManager(std::vector<GameObject*>* gameObjectList, ProjectilePool* projectiles, ProjectilePool* bombs)
{
	srand(SDL_GetTicks());
	EnemyManager::shootTimer.Start();
	EnemyManager::shootDelay = (std::rand() % (EnemyManager::maxShootDelay - EnemyManager::minShootDelay) + EnemyManager::minShootDelay) * 0.01f;
	EnemyManager::bombs = bombs;

	for (int y = 0; y < sizeof(EnemyManager::enemyRows) / sizeof(int); y++)
		for (int i = 0; i < EnemyManager::enemyRows[y]; i++)
		{
			int spriteIndex = std::rand() % sizeof(EnemyManager::enemySprites) / sizeof(EnemyManager::enemySprites[0]);
			std::string enemySpritePath = EnemyManager::enemySprites[spriteIndex];

			auto* enemy = new Enemy{ i * 80 + 100, y * 80 + 30, projectiles, this, enemySpritePath};
			gameObjectList->push_back(enemy);
			EnemyManager::enemies.push_back(enemy);
		}

}
EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	CheckWallEvent();

	if (shootTimer.GetTicks() >= EnemyManager::shootDelay * 1000)
	{
		EnemyManager::shootTimer.Stop();
		EnemyManager::shootTimer.Start();



		int index = (std::rand() % EnemyManager::enemyCount);

		//Object Pooling
		for (Projectile* bomb : bombs->pooledObjects)
		{
			if (!bomb->isActive)
			{
				bomb->isActive = true;
				bomb->Move(EnemyManager::enemies[index]->mesh.rect.x, EnemyManager::enemies[index]->mesh.rect.y);

				break;
			}
		}
	}
}

void EnemyManager::OnEnemyDeath()
{
	for (int i = 0; i < enemyCount; i++)
	{
		if (!enemies[i]->isActive)
		{
			enemies.erase(enemies.begin() + i);
			enemyCount--;

			return;
		}
	}
}
	
void EnemyManager::CheckWallEvent()
{
	for (Enemy* enemy : EnemyManager::enemies)
	{
		if (enemy->IsNearWall())
		{
			for (Enemy* enemy : EnemyManager::enemies)
			{
				enemy->ReachWallEvent();
			}
			break;
		}
	}
}
