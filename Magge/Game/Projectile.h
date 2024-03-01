#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
	Projectile(int xPos, int yPos) : GameObject{ xPos, yPos, 10, 30 }
	{

	}
};

