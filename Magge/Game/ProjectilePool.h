#pragma once
#include "Projectile.h"
#include <vector>

class ProjectilePool
{
public:
	int count;
	std::vector<Projectile*> pooledObjects;

	ProjectilePool(int count, int speed, std::string path, std::vector<GameObject*>* gameObjectList)
	{
		this->count = count;

		for (int i = 0; i < count; i++)
		{
			auto* projectile = new Projectile{ speed, path };
			projectile->isActive = false;
			gameObjectList->push_back(projectile);
			pooledObjects.push_back(projectile);
		}

	}

};

