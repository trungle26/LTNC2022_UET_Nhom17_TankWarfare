#pragma once
#include <string>
#include <SDL.h>
#include "ECS.h"
#include "Components.h"

class CollisionComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;


	TransformComponent* transform;
	CollisionComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{	// kiem tra xem da tao tranformcomponent chua, neu roi se co loi runtime
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		Game::colliders.push_back(this);
	}

	void update() override
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.w = transform->width * transform->scale;
		collider.y = static_cast<int>(transform->position.y);
		collider.h = transform->height * transform->scale;
	}

};