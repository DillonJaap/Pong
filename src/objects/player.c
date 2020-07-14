#include <SDL.h>
#include "vector.h"
#include "collision.h"
#include "player.h"
#include "objects.h"
#include "walls.h"
#include "physics.h"
#include "common.h"


#define NUM_PLAYERS 2
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

Player* get_player2()
{
	return &players[1];
}

void init_players(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("assets/player.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

   	players[0].hb = init_hitbox(0,   0, 10, 75);
   	players[1].hb = init_hitbox(700, 0, 10, 75);

	for (int i = 0; i < NUM_PLAYERS; i++)
		players[i].texture = texture;
}

void draw_players(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		rect = hitbox_to_SDLRect(players[i].hb);
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderFillRect(renderer, &rect);
		//SDL_RenderCopyEx(renderer, players[i].texture, NULL, &rect, 1, NULL, SDL_FLIP_NONE);
	}
}

void update_player(Player* p)
{
	p->prev_hb = p->hb;

	apply_velocity(&p->hb, p->vel);
	player_handle_collisions(p);
	apply_friction(&p->vel, PLAYER_FRICTION);
}

void handle_player_input(Player* p)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
		p->vel.y += -1.0;
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
		p->vel.y += 1.0;
	/*
	if (currentKeyStates[SDL_SCANCODE_LEFT])
		p->vel.x += -1.0;
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		p->vel.x += 1.0;
	*/
}


void player_handle_collisions(Player* p)
{
	Obj* wall;
	Vector2 zero_vel = (Vector2){0.0, 0.0};
	if (collides_with_wall(p->hb, &wall))
	{
		SIDE side = resolve_collision(&p->hb, p->prev_hb, wall->hb, wall->hb);
		if (side == LEFT || side == RIGHT)
			p->vel.x = 0;
		else if (side == TOP || side == BOTTOM)
			p->vel.y = 0;
	}

	if (collides_with_edge(p->hb))
	{
		SIDE side = resolve_edge_collision(&p->hb);
		if (side == LEFT || side == RIGHT)
			p->vel.x = 0;
		else if (side == TOP || side == BOTTOM)
			p->vel.y = 0;
	}
}

bool collides_with_player(Hitbox hb, Player** player)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (collides(hb, players[i].hb))
		{
			*player = &players[i];
			return true;
		}
	}
	*player = NULL;
	return false;
}
