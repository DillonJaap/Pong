#include <SDL.h>
#include <math.h>
#include "common.h"
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
   	balls[0].hb      = init_hitbox(50, 50, 10, 10);
   	balls[0].prev_hb = init_hitbox(50, 50, 10, 10);

	for (int i = 0; i < NUM_BALLS; i++)
	{
		balls[i].texture = texture;
		balls[i].vel.x = 2.0;
		balls[i].vel.y = 1.5;
	}
}

Ball* get_balls()
{
	return balls;
}

void draw_balls(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	for (int i = 0; i < NUM_BALLS; i++)
	{
		rect = hitbox_to_SDLRect((balls[i]).hb);
		SDL_RenderCopyEx(renderer, balls[i].texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
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

void ball_handle_collisions(Ball* b)
{
	Player* player;
	Obj* wall;
	Vector2 zero_vel = (Vector2){0.0, 0.0};

	if (collides_with_player(b->hb, &player))
	{
		SIDE side = resolve_collision(&b->hb, b->prev_hb, player->hb, player->prev_hb);
		bounce(&b->vel, &player->vel, side, 1.2);
	}

	if (collides_with_wall(b->hb, &wall))
	{
		SIDE side = resolve_collision(&b->hb, b->prev_hb, wall->hb, wall->hb);
		bounce(&b->vel, &zero_vel, side, 1.2);
	}

	if (collides_with_edge(b->hb))
	{
		SIDE side = resolve_edge_collision(&b->hb);
		bounce(&b->vel, &zero_vel, side, 1.0);
	}
}

void move_ball(Ball* b)
{
	b->prev_hb = b->hb;
	apply_velocity(&b->hb, b->vel);
	ball_handle_collisions(b);
	limit_velocity(&b->vel, 4.5);
}
