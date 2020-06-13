#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <stdbool.h>

bool collides(SDL_Rect a, SDL_Rect b);
bool collides_with_right_edge(SDL_Rect rec);
bool collides_with_left_edge(SDL_Rect rec);
bool collides_with_bottom_edge(SDL_Rect rec);
bool collides_with_top_edge(SDL_Rect rec);
void snap_to_horizontal_edge(SDL_Rect* rec, Vector2 dir);
void snap_to_vertical_edge(SDL_Rect* rec, Vector2 dir);
void snap_to_rec(SDL_Rect* recA, SDL_Rect* recB, Vector2 dir);

#endif
