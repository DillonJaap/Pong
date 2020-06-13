#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <stdbool.h>

#define SCALE 1
#define SCREEN_LENGTH 700
#define SCREEN_HEIGHT 500

typedef enum Side
{
	LEFT_SIDE    = 1,
	RIGHT_SIDE   = 2,
	TOP_SIDE     = 3,
	BOTTOM_SIDE  = 4,
} Side;

typedef struct Point
{
	int x;
	int y;
} Point;

typedef struct Vector2 
{
	double x;
	double y;
} Vector2;

Vector2 vector_add(Vector2 v1, Vector2 v2);
Vector2 vector_sub(Vector2 v1, Vector2 v2);
Vector2 vector_scale(Vector2 v, double scalar);
double vector_dot(Vector2 v1, Vector2 v2);
double vector_cross(Vector2 v1, Vector2 v2);
bool lines_intersect(Vector2 v1_beg, Vector2 v1_end, Vector2 v2_beg, Vector2 v2_end);

bool collides(SDL_Rect a, SDL_Rect b);
bool collides_with_right_edge(SDL_Rect rec);
bool collides_with_left_edge(SDL_Rect rec);
bool collides_with_bottom_edge(SDL_Rect rec);
bool collides_with_top_edge(SDL_Rect rec);
void snap_to_rec(SDL_Rect* recA, SDL_Rect* recB, Vector2 dir);
void snap_to_horizontal_edge(SDL_Rect* rec, double ydir);
void snap_to_vertical_edge(SDL_Rect* rec, double xdir);

#endif
