#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <stdbool.h>

bool collides(SDL_Rect a, SDL_Rect b);
bool collides_with_right_edge(SDL_Rect rec);
bool collides_with_left_edge(SDL_Rect rec);
bool collides_with_bottom_edge(SDL_Rect rec);
bool collides_with_top_edge(SDL_Rect rec);
int snap_to_rect(SDL_Rect a_prev, SDL_Rect* a_cur, SDL_Rect b_cur);
bool collides_with_edge(SDL_Rect rec);
int snap_to_edge(SDL_Rect* rec);

#endif
