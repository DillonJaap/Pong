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
void draw_balls(SDL_Renderer* renderer);
void move_ball();

#endif
