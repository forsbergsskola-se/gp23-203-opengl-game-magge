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
	int minShootDelay = 70;
	int maxShootDelay = 130;

	float shootDelay;
	const float delayMultiplier = 0.85f;

	Time shootTimer{};

	void CheckWallEvent();
	ProjectilePool* bombs;
	std::string enemySprites[10]{	"Resources/enemy1.png", "Resources/enemy2.png", "Resources/enemy3.png",
									"Resources/enemy4.png", "Resources/enemy5.png", "Resources/enemy6.png",
									"Resources/enemy7.png", "Resources/enemy8.png", "Resources/enemy9.png",
									"Resources/enemy10.png"};
public:
	int score = 0;
	//ProjectilePool* projectiles;
	std::vector<Enemy*> enemies;
	int enemyRows[5]{ 14, 14, 14, 14, 14};
	int enemyCount;
	const int bombCount = 20;

	EnemyManager(std::vector<GameObject*>* gameObjectList, ProjectilePool* projectilePool, ProjectilePool* bombs);
	~EnemyManager();

	void Update();

	void OnEnemyDeath();
};