#pragma once
#include <SDL.h>
#include "Vector2D.h"
class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AABB(const SDL_Rect& rect, const Vector2D& point);

};
