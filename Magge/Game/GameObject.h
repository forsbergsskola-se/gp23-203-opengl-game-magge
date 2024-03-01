#pragma once
#include "Mesh.h"

class GameObject
{
public:
	Mesh mesh;
	SDL_Rect collider;
	int moveSpeed = 10;

	int velX;
	int velY;

	GameObject(int posX, int posY, int width, int height) : mesh{posX, posY, width, height}
	{
		velX = 0;
		velY = 0;

		collider.x = posX;
		collider.y = posY;

		collider.w = width;
		collider.h = height;
	}

	void Move(int posX, int posY)
	{
		mesh.rect.x = posX;
		mesh.rect.y = posY;

		collider.x = posX;
		collider.y = posY;
	}

	bool IsColliding(SDL_Rect &otherRect)
	{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = collider.x;
		rightA = collider.x + collider.w;
		topA = collider.y;
		bottomA = collider.y + collider.h;

		//Calculate the sides of rect other.collider
		leftB = otherRect.x;
		rightB = otherRect.x + otherRect.w;
		topB = otherRect.y;
		bottomB = otherRect.y + otherRect.h;

		if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
		{
			return false;
		}

		return true;
	}

	void Render()
	{
		mesh.Render();
	}
};

