#include <SDL.h>
#include <stdbool.h>
#include "vector.h"

// TODO, make it apply result instead of returning result?
Vector2 vector_add(Vector2 v1, Vector2 v2)
{
	return (Vector2){v1.x + v2.x, v1.y + v2.y};
}

// TODO, make it apply result instead of returning result?
Vector2 vector_sub(Vector2 v1, Vector2 v2)
{
	return (Vector2){v1.x - v2.x, v1.y - v2.y};
}

// TODO, make it apply result instead of returning result?
Vector2 vector_scale(Vector2 v, double scalar)
{
	return (Vector2){v.x * scalar, v.y * scalar};
}

double vector_dot(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

// Psuedo cross product (can't do cross product of vectors in 2d space).
// treat vectors as if their Z cordinate is 0
double vector_cross(Vector2 v1, Vector2 v2)
{
	return (v1.x * v2.y) - (v1.y * v2.x);
}

Vector2 get_midpoint(SDL_Rect r)
{
	return (Vector2){(r.x + r.w) / 2, (r.y + r.h) / 2};
}

bool lines_intersect(Vector2 v1_beg, Vector2 v1_end, Vector2 v2_beg, Vector2 v2_end)
{
	Vector2 sub         = vector_sub(v2_beg, v1_beg);
	double divisor      = vector_cross(v1_end, v2_end);

	double v1_dividend  = vector_cross(sub, v1_end);
	double v1_intersect = v1_dividend/divisor;

	double v2_dividend  = vector_cross(sub, v2_end);
	double v2_intersect = v2_dividend/divisor;

	// if v2 X v4 = 0, then the two are collinear
	// don't count collinear as intersection
	// TODO maybe change this behavior
	if (divisor == 0 && v2_dividend == 0)
		return false;

	// lines are parallel and non-intersecting
	if (divisor == 0 && v2_dividend != 0)
		return false;

	if (divisor == 0 && 0 <= v1_intersect && v1_intersect <= 1 && 0 <= v2_intersect && v2_intersect <= 1)
		return true;

	// not parallel, but no intersection
	return false;
}
