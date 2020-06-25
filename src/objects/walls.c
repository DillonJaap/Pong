#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vector.h"
#include "collision.h"
#include "objects.h"
#include "walls.h"

#define NUM_WALLS 0
static Obj walls[NUM_WALLS];

Obj* get_walls()
{
	return walls;
}

void init_walls(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("assets/player.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	walls[0].col = (SDL_Rect){.x = 500,  .y = 500, .h = 16,  .w = 16};
	walls[1].col = (SDL_Rect){.x = 300, .y = 50,  .h = 300, .w = 300};

	for (int i = 0; i < NUM_WALLS; i++)
		walls[i].texture = texture;
}

bool collides_with_wall(SDL_Rect hit_box, Obj** wall)
{
	for (int i = 0; i < NUM_WALLS; i++)
	{
		if (collides(hit_box, (walls[i]).col))
		{
			*wall = &walls[i];
			return true;
		}
	}
	*wall = NULL;
	return NULL;
}

void draw_walls(SDL_Renderer* renderer)
{
	for (int i = 0; i < NUM_WALLS; i++)
		SDL_RenderCopyEx(renderer, walls[i].texture, NULL, &(walls[i].col), 0, NULL, SDL_FLIP_NONE);
}

