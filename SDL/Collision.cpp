#include "Collision.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	SDL_bool collide = SDL_HasIntersection(&rectA, &rectB);
	return collide;
}