#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>
#include <SDL.h>

typedef struct Obj
{
	int x;
	int y;
	int w;
	int h;
	SDL_Texture* texture;
	SDL_Rect* hit_box;
} Obj;

Obj init_player(SDL_Renderer* renderer);
void draw_obj(SDL_Renderer* renderer, Obj obj);
void draw_objs(SDL_Renderer* renderer);

#endif
