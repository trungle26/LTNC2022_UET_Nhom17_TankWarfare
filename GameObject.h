#pragma once
#include "Game.h"

class GameObject {
public:
	GameObject(const char* texturesheet,double x, double y);
	~GameObject();
	void Update();
	void UpdateX(double x);
	void UpdateY(double y);
	void Render();

private:
	double xpos;
	double ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, desRect;


};
