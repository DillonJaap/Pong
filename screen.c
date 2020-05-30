#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "screen.h"

#define SCREEN_LENGTH 200
#define SCREEN_HEIGHT 200
#define PIXEL_SIZE 4

static uint16_t screen[SCREEN_LENGTH * SCREEN_HEIGHT];

int get_screen_pos(uint32_t row, uint32_t col)
{
	if (row > SCREEN_LENGTH) row = SCREEN_LENGTH;
	if (col > SCREEN_HEIGHT)  col = SCREEN_HEIGHT;
	return screen[col + (SCREEN_LENGTH * row)];
}

void set_screen_pos(uint32_t row, uint32_t col, int value)
{
	if (row > SCREEN_LENGTH) row = SCREEN_LENGTH;
	if (col > SCREEN_HEIGHT)  col = SCREEN_HEIGHT;
	screen[col + (SCREEN_LENGTH * row)] = value;
}

void draw_pixel(SDL_Renderer* renderer, uint32_t row, uint32_t col)
{
	row *= PIXEL_SIZE;
	col *= PIXEL_SIZE;

	for (int y = row; y < PIXEL_SIZE + row; y++)
	{
		for (int x = col; x < PIXEL_SIZE + col; x++)
			SDL_RenderDrawPoint(renderer, y, x);
	}
}

void draw_screen(SDL_Renderer* renderer)
{
	for (int row = 0; row < SCREEN_LENGTH; row++)
	{
		for (int col = 0; col < SCREEN_HEIGHT; col++)
		{
			if (screen[row + (SCREEN_LENGTH * col)])
				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
			else
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
			draw_pixel(renderer, row, col);
		}
	}
}
