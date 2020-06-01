#include <SDL.h>
#include "player.h"
#include "objects.h"

void handle_player_input(Obj* player)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
		player->y--;
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
		player->y++;

	if (currentKeyStates[SDL_SCANCODE_LEFT])
		player->x--;
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		player->x++;
}

Obj init_player(SDL_Renderer* renderer)
{
	Obj player = {.x = 0, .y = 0, .h = 15, .w = 7};
	SDL_Surface* surface = SDL_LoadBMP("./player.bmp");
	player.texture = SDL_CreateTextureFromSurface(renderer, surface);
	player.hit_box = NULL;
	return player;
}
