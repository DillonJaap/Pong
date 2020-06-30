#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vector.h"
#include "collision.h"
#include "objects.h"
#include "walls.h"

#define NUM_WALLS 1
static Obj walls[NUM_WALLS];

Obj* get_walls()
{
	return walls;
}

void init_walls(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("assets/player.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	walls[0].hb = init_hitbox(500, 500, 16, 16);
	walls[1].hb = init_hitbox(300, 50, 300, 300);

	for (int i = 0; i < NUM_WALLS; i++)
		walls[i].texture = texture;
}

bool collides_with_wall(Hitbox hb, Obj** wall)
{
	for (int i = 0; i < NUM_WALLS; i++)
	{
		if (collides(hb, (walls[i]).col))
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
		SDL_RenderCopyEx(renderer, walls[i].texture, NULL, &hitbox_to_SDLRect(walls[i].hb),, 0, NULL, SDL_FLIP_NONE);
}

