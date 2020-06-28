#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "objects.h"
#include "vector.h"
#include "collision.h"

typedef struct Player
{
	Hitbox hb;
	SDL_Texture* texture;
	Vector2 vel;
} Player;

Player* get_players();
Player* get_player1();
Player* get_player2();
void init_players(SDL_Renderer* renderer);
void draw_players(SDL_Renderer* renderer);
void handle_player_input(Player* p);
void player_handle_collisions(Player* p, SDL_Rect prev_col);
void move_player(Player* p);
bool collides_with_player(SDL_Rect hit_box, Player** player);

#endif
