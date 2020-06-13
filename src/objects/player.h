#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "objects.h"
#include "vector.h"
#include "collision.h"

typedef struct Player
{
	SDL_Rect col;
	SDL_Texture* texture;
	Vector2 vel;
} Player;

void init_players(SDL_Renderer* renderer);
void draw_players(SDL_Renderer* renderer);
void handle_player_input();
void move_player();
bool player_collides(Player player);
bool collides_with_player(SDL_Rect hit_box, Player** player);

#endif
