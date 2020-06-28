#ifndef OBJECTS_H
#define OBJECTS_H

#define NUM_OBJS 1

#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>

typedef struct Obj
{
	SDL_Rect col;
	SDL_Texture* texture;
} Obj;

Obj init_objs(SDL_Renderer* renderer);
void draw_obj(SDL_Renderer* renderer, Obj obj);
void draw_objs(SDL_Renderer* renderer, Obj* objs);
bool collides(SDL_Rect a, SDL_Rect b);
Obj* collides_with_obj(SDL_Rect hit_box, Obj* objs);


#endif
