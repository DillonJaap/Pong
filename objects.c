#include <SDL2/SDL.h>
#include <stdbool.h>
#include "objects.h"
#include "screen.h"

#define NUM_OBJS 24
#define SCALE 4

Obj objs[NUM_OBJS];


Obj init_player(SDL_Renderer* renderer)
{
	Obj player = {.x = 0, .y = 0, .h = 15, .w = 7};
	SDL_Surface* surface = SDL_LoadBMP("./player.bmp");
	player.texture = SDL_CreateTextureFromSurface(renderer, surface);
	player.hit_box = NULL;
	return player;
}

void draw_obj(SDL_Renderer* renderer, Obj obj)
{
	SDL_Rect renderer_rect = {obj.x * SCALE, obj.y * SCALE, obj.w * SCALE, obj.h * SCALE};
	SDL_RenderCopyEx(renderer, obj.texture, NULL, &renderer_rect, 0, NULL, SDL_FLIP_NONE);
}

void draw_objs(SDL_Renderer* renderer)
{
	for (int i = 0; i < 1; i++)
		draw_obj(renderer, objs[i]);
}
