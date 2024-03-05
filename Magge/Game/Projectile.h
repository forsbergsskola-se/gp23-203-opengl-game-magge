#pragma once
#include "GameObject.h"
#include "Window.h"

class Projectile : public GameObject
{
	int speed;
public:
	Projectile(int speed, std::string path) : GameObject{ -10, -10, 20, 25, path }
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

