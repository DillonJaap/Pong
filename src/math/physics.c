#include <SDL.h>
#include "physics.h"
#include "vector.h"

void apply_velocity(SDL_Rect* col, Vector2 vel)
{
	col->x += vel.x;
	col->y += vel.y;
}

void apply_friction(Vector2* vel, double friction)
{
	*vel = vector_scale(*vel, friction);
}
