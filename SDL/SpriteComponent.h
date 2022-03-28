#pragma once
#include "Components.h"
#include <SDL.h>

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;

public:
	SpriteComponent();
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
		transform = &entity->getComponent<TransformComponent>(); // tao 1 entity bang ecs

		srcRect.x = srcRect.y = 0;
		srcRect.h = 40;
		srcRect.w = 36;
		desRect.h = srcRect.h;
		desRect.w = srcRect.w;
	}

	void update() override
	{
		desRect.x = transform->position.x;
		desRect.y = transform->position.y;
	}
	void draw() override
	{
		TextureManager::DrawTank(texture, srcRect, desRect, transform->angle);
	}
};