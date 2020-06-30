#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "vector.h"
#include "collision.h"

Hitbox init_hitbox(int x, int y, int w, int h)
{
	return (Hitbox){.top = y, .left = x, .right = x + w, .bottom = y + h};
}

SDL_Rect hitbox_to_SDLRect(Hitbox hb)
{
	return (SDL_Rect){
		.x = hb.left,
		.y = hb.top,
	   	.w = hb.right - hb.left,
		.h = hb.bottom - hb.top
	}
}

bool collides(Hitbox a, Hitbox b)
{
	if (a.left >= b.right)
		return false;
	if (a.right <= b.left)
		return false;
	if (a.top >= b.bottom)
		return false;
	if (a.bottom <= b.top)
		return false;
	return true;
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

// repel rectangle and return the side of b that a hit
SIDE repel_rect(SDL_Rect* recta, SDL_Rect recta_prev, SDL_Rect rectb)
{
	int horizontal_dist = 0;
	int vertical_dist = 0;
	SIDE horizontal_side = NO_SIDE;
	SIDE vertical_side   = NO_SIDE;

	if (recta_prev.x > rectb.x + rectb.w)
	{
		horizontal_dist = recta->x - (rectb.x + rectb.w);
		horizontal_side = RIGHT;
	}
	else if (recta_prev.x + recta_prev.w < rectb.x)
	{
		horizontal_dist = (recta->x + recta->w) - rectb.x;
		horizontal_side = LEFT;
	}
	printf("horizontal dist: %d\n", horizontal_dist);

	if (recta_prev.y > rectb.y + rectb.h)
	{
		vertical_dist = recta->y - (rectb.y + rectb.h);
		vertical_side = BOTTOM;
	}
	else if (recta_prev.y + recta_prev.h < rectb.y)
	{
		vertical_dist = (recta_prev.y + recta_prev.h) - rectb.y;
		vertical_side = TOP;
	}
	printf("vertical dist: %d\n", vertical_dist);

	if (abs(vertical_dist) < abs(horizontal_dist))
	{
		recta->y += vertical_dist;
		return vertical_side;
	}
	else
	{
		recta->x += horizontal_dist;
		return horizontal_side;
	}
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
