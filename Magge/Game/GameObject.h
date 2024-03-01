#pragma once
#include "Mesh.h"

class GameObject
{
public:
	Mesh* mesh;
	int moveSpeed = 10;

	int velX;
	int velY;

};

