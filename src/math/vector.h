#ifndef VECTOR_H
#define VECTOR_H

#include <SDL.h>
#include <stdbool.h>

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
Vector2 get_midpoint(SDL_Rect r);
bool lines_intersect(Vector2 v1_beg, Vector2 v1_end, Vector2 v2_beg, Vector2 v2_end);

#endif
