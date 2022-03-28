//TransformComponent la de xu ly cac di chuyen cua xe tank, vat the, ...

#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;
	double angle = 90;

	int speed = 2;

	bool blocked = false;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.Zero();
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}
	void update() override
	{
		position.x += static_cast<int>(velocity.x * speed);
		position.y += static_cast<int>(velocity.y * speed);
	}

	void rePhai()
	{
		angle += 3;
		//if (angle < 0) angle = 360;
	}

	void reTrai()
	{
		angle -= 3;
		//if (angle > 359) angle = 0;
	}

	void diThang(double velocity)
	{
		double x_movement = cos(0.0174532925 * (angle)) * velocity;
		double y_movement = sin(0.0174532925 * (angle)) * velocity;
		position.x += x_movement;
		position.y += y_movement;
	}
};