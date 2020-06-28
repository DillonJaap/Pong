#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <stdbool.h>

typedef enum SIDE {
	NO_SIDE,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
} SIDE;

typedef struct Hitbox {
	int top;
	int bottom;
	int left;
	int right
} Hitbox;

bool collides(SDL_Rect a, SDL_Rect b);
bool collides_with_right_edge(SDL_Rect rec);
bool collides_with_left_edge(SDL_Rect rec);
bool collides_with_bottom_edge(SDL_Rect rec);
bool collides_with_top_edge(SDL_Rect rec);
int snap_to_rect(SDL_Rect a_prev, SDL_Rect* a_cur, SDL_Rect b_cur);
SIDE repel_rect(SDL_Rect* recta, SDL_Rect recta_prev, SDL_Rect rectb);
bool collides_with_edge(SDL_Rect rec);
int snap_to_edge(SDL_Rect* rec);

#endif
