#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(int xPos, int yPos) : GameObject{ xPos, yPos, 50, 50 }
	{

	}
};

