#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "player.h"
#include "objects.h"
#include "walls.h"
#include "vector.h"
#include "collision.h"


typedef struct Ball
{
	SDL_Rect col;
	Vector2 vel;
	SDL_Texture* texture;
} Ball;

void init_balls(SDL_Renderer* renderer);
Ball* get_balls();
void draw_balls(SDL_Renderer* renderer);
static void limit_velocity(Ball* ball);
void ball_bounce(Ball* b, int side, double multiplier);
void ball_handle_collisions(Ball* b, SDL_Rect prev_col);
void move_ball(Ball* b);

#endif
