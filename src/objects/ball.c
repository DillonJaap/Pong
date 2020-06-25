#include <SDL.h>
#include <math.h>
#include "vector.h"
#include "physics.h"
#include "collision.h"
#include "player.h"
#include "objects.h"
#include "walls.h"
#include "ball.h"

#define BALL_MAX_VEL 10
#define NUM_BALLS 1

static Ball balls[NUM_BALLS];

void init_balls(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("./assets/player.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   	balls[0].col = (SDL_Rect){.x = 50, .y = 50, .h = 10, .w = 10};

	for (int i = 0; i < NUM_BALLS; i++)
	{
		balls[i].texture = texture;
		balls[i].vel.x = 3.0;
		balls[i].vel.y = 0.5;
	}
}

Ball* get_balls()
{
	return balls;
}

void draw_balls(SDL_Renderer* renderer)
{
	for (int i = 0; i < NUM_BALLS; i++)
		SDL_RenderCopyEx(renderer, balls[i].texture, NULL, &(balls[i].col), 0, NULL, SDL_FLIP_NONE);
}

static void limit_velocity(Ball* ball)
{
	double total_vel = sqrt(pow(ball->vel.x, 2) + pow(ball->vel.y, 2));
	if (total_vel > BALL_MAX_VEL)
	{
		double scale = (double)BALL_MAX_VEL / total_vel;
		ball->vel.x *= scale;
		ball->vel.y *= scale;
	}
}

// bound ball 1 for vertical, 2 for horizontal
void ball_bounce(Ball* b, int side, double multiplier)
{
		if (side == 1)
			b->vel.x *= -multiplier;
		else if (side == 2)
			b->vel.y *= -multiplier;
}

void ball_handle_collisions(Ball* b, SDL_Rect prev_col)
{
	Player* player;
	Obj* wall;

	if (collides_with_player(b->col, &player))
	{
		int side = snap_to_rect(prev_col, &b->col, player->col);
		ball_bounce(b, side, 0.9);
		if (side == 1)
			b->vel.y += player->vel.y * 0.5;
	}

	if (collides_with_wall(b->col, &wall))
	{
		int side = snap_to_rect(prev_col, &b->col, wall->col);
		ball_bounce(b, side, 1.0);
	}

	if (collides_with_edge(b->col))
	{
		int side = snap_to_edge(&b->col);
		ball_bounce(b, side, 1.0);
	}
}

void move_ball(Ball* b)
{
	SDL_Rect prev_col = b->col;

	apply_velocity(&b->col, b->vel);
	ball_handle_collisions(b, prev_col);
	limit_velocity(b);
}
