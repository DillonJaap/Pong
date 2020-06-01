#include <SDL2/SDL.h>
#include <stdbool.h>
#include "objects.h"
#include "screen.h"

#define NUM_OBJS 24
#define SCALE 4

Obj objs[NUM_OBJS];

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
