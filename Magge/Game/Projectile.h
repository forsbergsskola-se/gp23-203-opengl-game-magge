#pragma once
#include "GameObject.h"
#include "Window.h"

class Projectile : public GameObject
{
	int speed;
public:
	Projectile(int speed, std::string path, int w, int h, bool randomColor) : GameObject{ -10, -10, w, h, path, randomColor }
	{
		isActive = false;
		this->speed = speed;
	}

	virtual void Update() override
	{
		if (!isActive)
			return;

		if (speed < 0 && mesh.rect.y > Window::SCREEN_HEIGHT || speed > 0 && mesh.rect.y < 0)
			isActive = false;

		Move(mesh.rect.x, mesh.rect.y - speed);
	}

};

