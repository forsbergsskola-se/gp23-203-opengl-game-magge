#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
	int speed;
public:
	Projectile(int speed) : GameObject{ -10, -10, 10, 25 }
	{
		isActive = false;
		this->speed = speed;
	}

	virtual void Update() override
	{
		if (!isActive)
			return;

		if (speed < 0 && mesh.rect.y > 0 || speed > 0 && mesh.rect.y < 0)
			isActive = false;

		Move(mesh.rect.x, mesh.rect.y - speed);

	}

};

