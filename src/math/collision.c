#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "vector.h"
#include "collision.h"


bool collides(SDL_Rect a, SDL_Rect b)
{
	int leftA   = a.x;
	int rightA  = a.x + a.w;
	int topA    = a.y;
	int bottomA = a.y + a.h;

	int leftB   = b.x;
	int rightB  = b.x + b.w;
	int topB    = b.y;
	int bottomB = b.y + b.h;

	if (leftA >= rightB)
		return false;
	if (rightA <= leftB)
		return false;
	if (topA >= bottomB)
		return false;
	if (bottomA <= topB)
		return false;
	return true;
}

// return true if two rects will collide after updating their position based on
// their velocity
bool will_collide(SDL_Rect a, Vector2 a_vel, SDL_Rect b, Vector2 b_vel)
{
	SDL_Rect a_after = a;
	a_after.x += a_vel.x;
	a_after.y += a_vel.y;

	SDL_Rect b_after = a;
	b_after.x += b_vel.x;
	b_after.y += b_vel.y;

	return collides(a_after, b_after);
}

// find what side of b that a will collide with
// side that rect a hit (1 for vertical, 2 for horizontal)
int snap_to_rect(SDL_Rect a_prev, SDL_Rect* a_cur, SDL_Rect b_cur)
{
	
	// the direction vector from a_prev to a_cur
	Vector2 dir = (Vector2){a_cur->x - a_prev.x, a_cur->y - a_prev.y};

	// distance from horizontal/vertical side of a to h/v side of b scaled by
	// the x/y of the direction
	double x_dist = 0.0;
	double y_dist = 0.0;

	if (dir.x > 0)
		x_dist = ((a_cur->x + a_cur->w) - b_cur.x);
	else
		x_dist = ((b_cur.x + b_cur.w) - a_cur->x);

	if (dir.y > 0)
		y_dist = ((a_cur->y + a_cur->h) - b_cur.y);
	else
		y_dist = ((b_cur.y + b_cur.h) - a_cur->y);

	if ((abs(x_dist * dir.x) < abs(y_dist * dir.y) || dir.y == 0) && dir.x != 0)
	{
		if (dir.x > 0)
			x_dist *= -1;
		a_cur->x += x_dist;
		return 1;
	}
	else
	{
		if (dir.y > 0)
			y_dist *= -1;
		a_cur->y += y_dist;
		return 2;
	}

	//snap = (Vector2){x_dist, -1 * dir.y * (x_dist / dir.x)};
	//snap = (Vector2){dir.x * (y_dist / dir.y), y_dist};
}

// test if rec collides with right edge of game screen
bool collides_with_right_edge(SDL_Rect rec)
{
	return (rec.x + rec.w > SCREEN_LENGTH);
}

bool collides_with_left_edge(SDL_Rect rec)
{
	return (rec.x < 0);
}

bool collides_with_bottom_edge(SDL_Rect rec)
{
	return (rec.y + rec.h > SCREEN_HEIGHT);
}

bool collides_with_top_edge(SDL_Rect rec)
{
	return (rec.y < 0);
}
// test if rec collides with right edge of game screen

bool collides_with_edge(SDL_Rect rec)
{
	return (collides_with_right_edge(rec) 
			|| collides_with_left_edge(rec) 
			|| collides_with_bottom_edge(rec)
			|| collides_with_top_edge(rec));
}

int snap_to_edge(SDL_Rect* rec)
{
	int ret = 0;
	if (collides_with_right_edge(*rec))
	{
		rec->x = SCREEN_LENGTH - rec->w;
		ret += 1;
	}
	else if (collides_with_left_edge(*rec))
	{
		rec->x = 0;
		ret += 1;
	}
	if (collides_with_bottom_edge(*rec))
	{
		rec->y = SCREEN_HEIGHT - rec->h;
		ret += 2;
	}
	else if (collides_with_top_edge(*rec))
	{
		rec->y = 0;
		ret += 2;
	}

	return ret;
}
