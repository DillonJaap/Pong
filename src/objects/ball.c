#include <SDL.h>
#include <math.h>
#include "vector.h"
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
	SDL_Surface* surface = SDL_LoadBMP("../../assests/player.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   	balls[0].col = (SDL_Rect){.x = 50, .y = 5, .h = 15, .w = 7};

	for (int i = 0; i < NUM_BALLS; i++)
	{
		balls[i].texture = texture;
		balls[i].vel.x = 3.0;
		balls[i].vel.y = 0.5;
	}
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



void move_ball()
{
	Obj* wall;
	Player* player;
/*
	balls[0].col.x += balls[0].vel.x;
	if (collides_with_player(balls[0].col, &player))
	{
		snap_to_rec(&balls[0].col, &(player->col), balls[0].vel);
		balls[0].vel.x *= -0.9;
		balls[0].vel.y += player->yvel * 0.5;
	}
	else if (collides_with_wall(balls[0].col, &wall))
	{
		snap_to_rec(&balls[0].col, &(wall->col), balls[0].vel);
		balls[0].vel.x *= -0.9;
	}
	else if (collides_with_right_edge(balls[0].col) || collides_with_left_edge(balls[0].col))
	{
		snap_to_vertical_edge(&balls[0].col, balls[0].vel);
		balls[0].vel.x *= -0.9;
	}
	
	balls[0].col.y += balls[0].vel.y;
	if (collides_with_player(balls[0].col, &player))
	{
		snap_to_rec(&balls[0].col, &(player->col), balls[0].vel);
		balls[0].vel.y *= -1.0;
	}
	else if (collides_with_wall(balls[0].col, &wall))
	{
		snap_to_rec(&balls[0].col, &(wall->col), balls[0].vel);
		balls[0].vel.y *= -1.0;
	}
	else if (collides_with_top_edge(balls[0].col) || collides_with_bottom_edge(balls[0].col))
	{
		snap_to_horizontal_edge(&balls[0].col, balls[0].vel);
		balls[0].vel.y *= -1.0;
	}

	limit_velocity(&balls[0]);
	*/
}
