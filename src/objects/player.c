#include <SDL.h>
#include "vector.h"
#include "collision.h"
#include "player.h"
#include "objects.h"
#include "walls.h"
#include "physics.h"


#define NUM_PLAYERS 1
#define PLAYER_FRICTION 0.85
static Player players[NUM_PLAYERS];

Player* get_players()
{
	return players;
}

Player* get_player1()
{
	return &players[0];
}

void init_players(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("assets/player.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

   	players[0].col = (SDL_Rect){.x = 0, .y = 0, .h = 65, .w = 20};
   	players[1].col = (SDL_Rect){.x = 400, .y = 0, .h = 30, .w = 7};

	for (int i = 0; i < NUM_PLAYERS; i++)
		players[i].texture = texture;
}

void draw_players(SDL_Renderer* renderer)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
		SDL_RenderCopyEx(renderer, players[i].texture, NULL, &(players[i].col), 1, NULL, SDL_FLIP_NONE);
}

void handle_player_input(Player* p)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
		p->vel.y += -1.4;
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
		p->vel.y += 1.4;

	if (currentKeyStates[SDL_SCANCODE_LEFT])
		p->vel.x += -1.4;
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		p->vel.x += 1.4;
	else
	{
		if (p->vel.x < 0.5 && p->vel.x > -0.5)
			p->vel.x = 0.0;
		if (p->vel.y < 0.5 && p->vel.y > -0.5)
			p->vel.y = 0.0;
	}
}


// parameter is previous collision box before applying velocity
void player_handle_collisions(Player* p, SDL_Rect prev_col)
{
	Obj* wall;
	if (collides_with_wall(p->col, &wall))
	{
		int side = snap_to_rect(prev_col, &p->col,  wall->col);
		if (side == 1)
			p->vel.x = 0;
		else if (side == 2)
			p->vel.y = 0;
	}

	if (collides_with_edge(p->col))
	{
		snap_to_edge(&p->col);
	}
}

void move_player(Player* p)
{
	SDL_Rect prev_col = p->col;

	apply_velocity(&p->col, p->vel);
	player_handle_collisions(p, prev_col);
	apply_friction(&p->vel, PLAYER_FRICTION);
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
