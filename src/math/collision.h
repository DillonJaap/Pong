#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <stdbool.h>

typedef enum SIDE {
	NO_SIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	TOP = 3,
	BOTTOM = 4
} SIDE;

typedef struct Hitbox {
	int top;
	int bottom;
	int left;
	int right;
} Hitbox;

Hitbox init_hitbox(int x, int y, int w, int h);
SDL_Rect hitbox_to_SDLRect(Hitbox hb);

bool collides(Hitbox a, Hitbox b);
bool collides_with_right_edge(Hitbox hb);
bool collides_with_left_edge(Hitbox hb);
bool collides_with_bottom_edge(Hitbox hb);
bool collides_with_top_edge(Hitbox hb);
bool collides_with_edge(Hitbox hb);
int snap_to_rect(SDL_Rect a_prev, SDL_Rect* a_cur, SDL_Rect b_cur);
int resolve_collision(Hitbox* recta, Hitbox recta_prev, Hitbox rectb, Hitbox rectb_prev);
SIDE resolve_edge_collision(Hitbox* hb);
void move_hitbox(Hitbox* hb, int dx, int dy);
void set_hitbox(Hitbox* hb, int x, int y);

#endif
