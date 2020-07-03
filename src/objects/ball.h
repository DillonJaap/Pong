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
	Hitbox hb;
	Hitbox prev_hb;
	Vector2 vel;
	SDL_Texture* texture;
} Ball;

void init_balls(SDL_Renderer* renderer);
Ball* get_balls();
void draw_balls(SDL_Renderer* renderer);
void ball_bounce(Ball* b, int side, double multiplier);
void ball_handle_collisions(Ball* b);
void move_ball(Ball* b);

#endif
