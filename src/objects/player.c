#include <SDL.h>
#include "vector.h"
#include "collision.h"
#include "player.h"
#include "objects.h"
#include "walls.h"


#define NUM_PLAYERS 1
#define PLAYER_FRICTION 0.85
static Player players[NUM_PLAYERS];

void init_players(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("assets/player.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

   	players[0].col = (SDL_Rect){.x = 0, .y = 0, .h = 50, .w = 7};
   	players[1].col = (SDL_Rect){.x = 400, .y = 0, .h = 30, .w = 7};

	for (int i = 0; i < NUM_PLAYERS; i++)
		players[i].texture = texture;
}
void draw_players(SDL_Renderer* renderer)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
		SDL_RenderCopyEx(renderer, players[i].texture, NULL, &(players[i].col), 1, NULL, SDL_FLIP_NONE);
}

void handle_player_input()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
		players[0].vel.y += -1.4;
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
		players[0].vel.y += 1.4;

	if (currentKeyStates[SDL_SCANCODE_LEFT])
		players[0].vel.x += -1.4;
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		players[0].vel.x += 1.4;
	else
	{
		if (players[0].vel.x < 0.5 && players[0].vel.x > -0.5)
			players[0].vel.x = 0.0;
		if (players[0].vel.y < 0.5 && players[0].vel.y > -0.5)
			players[0].vel.y = 0.0;
	}
}

void player_update_xpos()
{
	Obj* wall;
	players[0].col.x += players[0].vel.x;

	if (collides_with_wall(players[0].col, &wall))
	{
		Vector2 xvel = (Vector2){players[0].vel.x, 0};
		snap_to_rec(&players[0].col, &wall->col, xvel);
		players[0].vel.x == 0.0;
	}
}

void player_update_ypos()
{
	Obj* wall;
	players[0].col.y += players[0].vel.y;

	if (collides_with_wall(players[0].col, &wall))
	{
		Vector2 yvel = (Vector2){0, players[0].vel.y};
		snap_to_rec(&players[0].col, &wall->col, yvel);
		players[0].vel.y == 0.0;
	}
}

void move_player()
{
	player_update_xpos();
	player_update_ypos();
	players[0].vel.x *= PLAYER_FRICTION;
	players[0].vel.y *= PLAYER_FRICTION;
}

bool collides_with_player(SDL_Rect hit_box, Player** player)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (collides(hit_box, (players[i]).col))
		{
			*player = &players[i];
			return true;
		}
	}
	*player = NULL;
	return false;
}
