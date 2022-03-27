#pragma once
#include "Components.h"

class PositionComponent : public Component
{
private:
	int xpos;
	int ypos;
	double angle = 90;
public:

	PositionComponent(int x=0, int y=0)
	{
		xpos = x;
		ypos = y;
	}

	/*void update() override
	{
		xpos++;
		ypos++;
	}*/

	int x() { return xpos; }
	void x(int x) { xpos = x; }
	int y() { return ypos; }
	void y(int y) { ypos = y; }
	void setPos(int x, int y) { xpos = x; ypos = y; }

	void rePhai()
	{
		angle += 3;
		//if (angle < 0) angle = 360;
		std::cout << angle << std::endl;
	}

	void reTrai()
	{
		angle -= 3;
		//if (angle > 359) angle = 0;
		std::cout << angle << std::endl;
	}

	void diThang(double velocity)
	{
		double x_movement = cos(0.0174532925 * (angle)) * velocity;
		double y_movement = sin(0.0174532925 * (angle)) * velocity;
		xpos += x_movement;
		ypos += y_movement;
	}
};