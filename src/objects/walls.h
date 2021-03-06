#ifndef WALLS_H
#define WALLS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "objects.h"
#include "vector.h"
#include "collision.h"

Obj* get_walls();
void init_walls(SDL_Renderer* renderer);
bool collides_with_wall(Hitbox hb, Obj** wall);
void draw_walls(SDL_Renderer* renderer);

#endif
