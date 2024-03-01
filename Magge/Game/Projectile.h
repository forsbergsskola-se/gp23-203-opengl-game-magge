#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:

	Projectile() : GameObject{ -10, -10, 30, 70 }
	{
		isActive = false;
	}

	virtual void Update() override
	{
		if (!isActive)
			return;

		if (mesh.rect.y < 0)
			isActive = false;

		Move(mesh.rect.x, mesh.rect.y - 1);

	}

};

