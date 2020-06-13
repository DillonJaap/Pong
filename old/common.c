#include <SDL.h>
#include <stdbool.h>
#include "vector.h"


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
Side find_side_of_collision(SDL_Rect a, Vector2 a_vel, SDL_Rect b, Vector2 b_vel)
{
	SDL_Rect a_after = a;
	a_after.x += a_vel.x;
	a_after.y += a_vel.y;

	SDL_Rect b_after = a;
	b_after.x += b_vel.x;
	b_after.y += b_vel.y;

	// the direction vector from a to b
	Vector2 dir = (Vector2){b.x - a.x, b.x - a.x};

	// distance from horizontal/vertical side of a to h/v side of b scaled by
	// the x/y of the direction
	double scaled_x_dist;
	double scaled_y_dist;

	if (dir.x > 0)
		scaled_x_dist = ((a_after.x + a_after.w) - b_after.x) * dir.x;
	else
		scaled_x_dist = ((b_after.x + b_after.w) - a_after.x) * dir.x;

	if (dir.y > 0)
		scaled_y_dist = ((a_after.y + a_after.w) - b_after.y) * dir.y;
	else
		scaled_y_dist = ((b_after.y + b_after.w) - a_after.y) * dir.y;

	if (scaled_x_dist < scaled_y_dist)
	{
		if (dir.x > 0)
			return RIGHT_SIDE;
		else
			return LEFT_SIDE;
	}
	else
	{
		if (dir.y > 0)
			return TOP_SIDE;
		else
			return BOTTOM_SIDE;
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

// snap edge of rec A to edge of rec B based on direcion that the vector is pointing
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

void snap_to_horizontal_edge(SDL_Rect* rec, double ydir)
{
		if (dir.y > 0)
			rec->y = SCREEN_HEIGHT - rec->h;
		else if (dir.y < 0)
			rec->y = 0;
}

void snap_to_vertical_edge(SDL_Rect* rec, double xdir)
{
		if (dir.x > 0)
			rec->x = SCREEN_LENGTH - rec->w;
		else if (dir.x < 0)
			rec->x = 0;
}
