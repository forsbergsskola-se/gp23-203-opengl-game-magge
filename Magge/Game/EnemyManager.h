#pragma once
#include "Time.h"
#include <SDL.h>
#include <cstdlib>
#include <vector>
#include "String"

class Enemy;
class GameObject;
class ProjectilePool;

class EnemyManager
{

	const int minShootDelay = 80;
	const int maxShootDelay = 160;

	float shootDelay;
	Time shootTimer{};

	void CheckWallEvent();
	ProjectilePool* bombs;

public:
	std::string enemySprites[10]{	"Resources/enemy1.png", "Resources/enemy2.png", "Resources/enemy3.png",
									"Resources/enemy4.png", "Resources/enemy5.png", "Resources/enemy6.png",
									"Resources/enemy7.png", "Resources/enemy8.png", "Resources/enemy9.png",
									"Resources/enemy10.png"};
	//ProjectilePool* projectiles;
	std::vector<Enemy*> enemies;
	int enemyRows[4]{ 10, 10, 10, 10 };
	int enemyCount = 40;
	const int bombCount = 20;

	EnemyManager(std::vector<GameObject*>* gameObjectList, ProjectilePool* projectilePool, ProjectilePool* bombs);
	~EnemyManager();

	void Update();

	void OnEnemyDeath();
};