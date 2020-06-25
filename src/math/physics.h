#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL.h>
#include "vector.h"

void apply_velocity(SDL_Rect* col, Vector2 vel);
void apply_friction(Vector2* vel, double friction);

#endif
