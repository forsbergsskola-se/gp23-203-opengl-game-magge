#pragma once
#include "Mesh.h"

class GameObject
{
public:
	Mesh mesh;
	int moveSpeed = 10;

	int velX;
	int velY;

	GameObject(int posX, int posY, int width, int height) : mesh{posX, posY, width, height}
	{
		velX = 0;
		velY = 0;
	}
};

