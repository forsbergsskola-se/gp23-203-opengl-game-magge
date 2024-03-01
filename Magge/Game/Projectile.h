#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile() : GameObject{ -10, -10, 10, 30 }
	{

	}
};

