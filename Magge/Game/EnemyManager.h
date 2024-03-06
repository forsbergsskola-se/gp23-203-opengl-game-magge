#pragma once
#include <SDL.h>
#include <vector>
#include <String>
#include "Time.h"

class Enemy;
class GameObject;
class ProjectilePool;

class EnemyManager
{
	int minShootDelay = 70;
	int maxShootDelay = 130;
	float shootDelay;
	const float delayMultiplier = 0.85f;

	const int bombCount = 20;
	ProjectilePool* bombs;
	Time shootTimer{};
	std::string enemySprites[10]{	"Resources/enemy1.png", "Resources/enemy2.png", "Resources/enemy3.png",
									"Resources/enemy4.png", "Resources/enemy5.png", "Resources/enemy6.png",
									"Resources/enemy7.png", "Resources/enemy8.png", "Resources/enemy9.png", "Resources/enemy10.png"};
	void CheckWallEvent();

public:
	bool hasReachedBottom;
	int score = 0;
	int enemyRows[5]{ 14, 14, 14, 14, 14};
	int enemyCount;
	std::vector<Enemy*> enemies;

	EnemyManager(std::vector<GameObject*>* gameObjectList, ProjectilePool* projectilePool, ProjectilePool* bombs);
	~EnemyManager();

	void Update();
	void OnEnemyDeath();
};