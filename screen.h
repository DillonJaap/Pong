#include <stdbool.h>
#include "objects.h"

int  get_screen_pos(uint32_t row, uint32_t col);
void set_screen_pos(uint32_t row, uint32_t col, int value);
void draw_pixel(SDL_Renderer* renderer, uint32_t row, uint32_t col);
void draw_screen(SDL_Renderer* renderer);
