#pragma once
#include "Mesh.h"
#include "Texture.h"
class Color;

class GameObject
{
	Color colors[7]{	Color{0, 255, 255}, Color{255, 255, 0},
						Color{255, 127, 0}, Color{0, 255, 127},
						Color{255, 0, 127}, Color{127, 0, 255}, Color{0, 127, 255} };

public:
	bool isActive;

	Mesh mesh;
	Texture texture;
	SDL_Rect collider;
	int moveSpeed = 10;

	int velX;
	int velY;

	GameObject(int posX, int posY, int width, int height, std::string path, bool randomColor) : mesh{posX, posY, width, height}, texture{ path, mesh.rect.w, mesh.rect.h, randomColor? &colors[rand()%7] : new Color(255, 255, 255)}
	{
		velX = 0;
		velY = 0;

		collider.x = posX;
		collider.y = posY;

		collider.w = width;
		collider.h = height;

		isActive = true;
		
	}
	~GameObject()
	{
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

	virtual void Update(){}

	void Render()
	{
		if (isActive)
		{
			texture.Render(mesh.rect);
		}
	}
};

