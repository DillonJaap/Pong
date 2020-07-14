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

void print_hitbox(Hitbox hb, char* name)
{
	printf("\n");
	printf("Hitbox (%s):\n", name);
	printf("\tleft: %d\n", hb.left);
	printf("\tright: %d\n", hb.right);
	printf("\ttop: %d\n", hb.top);
	printf("\tbottom: %d\n", hb.bottom);
}

SDL_Rect hitbox_to_SDLRect(Hitbox hb)
{
	return (SDL_Rect){
		.x = hb.left,
		.y = hb.top,
	   	.w = hb.right - hb.left,
		.h = hb.bottom - hb.top
	};
}

void move_hitbox(Hitbox* hb, int dx, int dy)
{
	hb->left   += dx;
	hb->right  += dx;
	hb->top    += dy;
	hb->bottom += dy;
}

void set_hitbox(Hitbox* hb, int x, int y)
{
	hb->right  = x + (hb->right - hb->left);
	hb->left   = x;
	hb->bottom = y + (hb->bottom - hb->top);
	hb->top    = y;
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

bool collides_with_edge(Hitbox hb)
{
	return (collides_with_right_edge(hb) 
			|| collides_with_left_edge(hb) 
			|| collides_with_bottom_edge(hb)
			|| collides_with_top_edge(hb));
}

bool collides_with_right_edge(Hitbox hb)
{
	return (hb.right > SCREEN_LENGTH);
}

bool collides_with_left_edge(Hitbox hb)
{
	return (hb.left < 0);
}

bool collides_with_bottom_edge(Hitbox hb)
{
	return (hb.bottom > SCREEN_HEIGHT);
}

bool collides_with_top_edge(Hitbox hb)
{
	return (hb.top < 0);
}

// resolve rectangle and return the side of b that a hit
int resolve_collision(Hitbox* recta, Hitbox recta_prev, Hitbox rectb, Hitbox rectb_prev)
{
	int horizontal_dist = 0;
	int vertical_dist = 0;
	SIDE horizontal_side = NO_SIDE;
	SIDE vertical_side   = NO_SIDE;

	if (recta_prev.left >= rectb_prev.right)
	{
		horizontal_dist = rectb.right - recta->left;
		horizontal_dist++;
		horizontal_side = RIGHT;
	}
	else if (recta_prev.right <= rectb_prev.left)
	{
		horizontal_dist =  rectb.left - recta->right;
		horizontal_dist--;
		horizontal_side = LEFT;
	}

	if (recta_prev.top >= rectb_prev.bottom)
	{
		vertical_dist = rectb.bottom - recta->top;
		vertical_dist++;
		vertical_side = BOTTOM;
	}
	else if (recta_prev.bottom <= rectb_prev.top)
	{
		vertical_dist = rectb.top - recta->bottom;
		vertical_dist--;
		vertical_side = TOP;
	}

	if (abs(vertical_dist) < abs(horizontal_dist) || vertical_dist == 0)
	{
		move_hitbox(recta, horizontal_dist, 0);
		return horizontal_side;
	}
	else
	{
		move_hitbox(recta, 0, vertical_dist);
		return vertical_side;
	}
}

SIDE resolve_edge_collision(Hitbox* hb)
{
	int ret = 0;
	if (collides_with_right_edge(*hb))
	{
		set_hitbox(hb, SCREEN_LENGTH - (hb->right - hb->left), hb->top);
		return LEFT;
	}
	else if (collides_with_left_edge(*hb))
	{
		set_hitbox(hb, 0, hb->top);
		return RIGHT;
	}
	if (collides_with_bottom_edge(*hb))
	{
		set_hitbox(hb, hb->left, SCREEN_HEIGHT - (hb->bottom - hb->top));
		return TOP;
	}
	else if (collides_with_top_edge(*hb))
	{
		set_hitbox(hb, hb->left, 0);
		return BOTTOM;
	}
}
