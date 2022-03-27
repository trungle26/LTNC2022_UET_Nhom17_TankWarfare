#pragma once
#include "Components.h"
#include <SDL.h>

class SpriteComponent : public Component
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.h = 40;
		srcRect.w = 36;
		desRect.h = srcRect.h;
		desRect.w = srcRect.w;
	}

	void update() override
	{
		desRect.x = position->x();
		desRect.y = position->y();
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, desRect);
	}
};