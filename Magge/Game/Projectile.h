#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	int speed;
	Projectile() : GameObject{ -10, -10, 10, 25 }
	{
		isActive = false;
		speed = 10;
	}

	virtual void Update() override
	{
		if (!isActive)
			return;

		if (mesh.rect.y < 0)
			isActive = false;

		Move(mesh.rect.x, mesh.rect.y - speed);

	}

};

