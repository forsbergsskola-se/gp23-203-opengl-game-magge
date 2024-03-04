#pragma once
#include "Time.h"
#include <SDL.h>
#include <cstdlib>
#include <vector>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"


class EnemyManager
{
	const int minShootDelay = 80;
	const int maxShootDelay = 160;
	float shootDelay;
	Time shootTimer{};

	void CheckWallEvent();

public:
	std::vector<Enemy*> enemies;
	std::vector<Projectile*> bombs;
	int enemyRows[4]{ 10, 10, 10, 10 };
	int enemyCount = 40;
	const int bombCount = 20;

	EnemyManager(std::vector<GameObject*>* gameObjectList, Player* player);
	~EnemyManager();



	void Update();
};