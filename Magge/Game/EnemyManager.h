#pragma once
#include "Time.h"
#include <SDL.h>
#include <cstdlib>
#include <vector>
#include "Enemy.h"

class EnemyManager
{
	const int minShootDelay = 80;
	const int maxShootDelay = 160;
	float shootDelay;
	Time shootTimer{};

	void CheckWallEvent();
	ProjectilePool* bombs;

public:
	ProjectilePool* projectiles;
	std::vector<Enemy*> enemies;
	int enemyRows[4]{ 10, 10, 10, 10 };
	int enemyCount = 40;
	const int bombCount = 20;

	EnemyManager(std::vector<GameObject*>* gameObjectList, ProjectilePool* projectilePool, ProjectilePool* bombs);
	~EnemyManager();



	void Update();
};