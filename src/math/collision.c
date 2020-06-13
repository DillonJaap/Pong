#include <SDL.h>
#include <stdbool.h>
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

void snap_to_horizontal_edge(SDL_Rect* rec, Vector2 dir)
{
		if (dir.y > 0)
			rec->y = SCREEN_HEIGHT - rec->h;
		else if (dir.y < 0)
			rec->y = 0;
}

void snap_to_vertical_edge(SDL_Rect* rec, Vector2 dir)
{
		if (dir.x > 0)
			rec->x = SCREEN_LENGTH - rec->w;
		else if (dir.x < 0)
			rec->x = 0;
}

// snap edge of rec A to edge of rec B based on direcion that the vector is pointing
// vector should be zero in either y or x direction
void snap_to_rec(SDL_Rect* recA, SDL_Rect* recB, Vector2 dir)
{
		if (dir.x > 0)
			recA->x = recB->x - recA->w;
		else if (dir.x < 0)
			recA->x = recB->x + recB->w;
		else if (dir.y > 0)
			recA->y = recB->y - recA->w;
		else if (dir.y < 0)
			recA->y = recB->y + recB->w;
}
