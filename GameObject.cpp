#pragma once
#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, double x, double y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);
	
	xpos = x;
	ypos = y;
}

void GameObject::Update()
{
	srcRect.h = 56;
	srcRect.w = 56;
	srcRect.x = 0;
	srcRect.y = 0;
	desRect.h = srcRect.h ;
	desRect.w = srcRect.w ;
	desRect.x = xpos;
	desRect.y = ypos;
	
}
void GameObject::UpdateY(double y)
{
	ypos += y;
}

void GameObject::UpdateX(double x)
{
	xpos +=x;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &desRect);

}