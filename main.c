#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "screen.h"
#include "objects.h"

const int SCREEN_LENGTH = 400;
const int SCREEN_HEIGHT = 400;

bool init(SDL_Window** window, SDL_Renderer** renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("video init error\n");
		return 0;
	}

	*window = SDL_CreateWindow(
			"SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_LENGTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("window could not be created Error: %s\n", SDL_GetError());
		return 0;
	}

	*renderer = SDL_CreateRenderer(
			*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// disable anisotropic filtering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
}

void close_stuff(SDL_Window* window, SDL_Renderer* renderer)
{
	//Destroy Window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window   = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool quit()
{
	SDL_Event e;

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
			return true;
	}
	return false;
}

int main(int argc, char** argv)
{
	SDL_Window* window     = NULL;
	SDL_Renderer* renderer = NULL;

	init(&window, &renderer);

	Obj player = init_player(renderer);


	while (!quit())
	{

		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
		if (currentKeyStates[SDL_SCANCODE_UP])
			player.y--;
		else if (currentKeyStates[SDL_SCANCODE_DOWN])
			player.y++;

		if (currentKeyStates[SDL_SCANCODE_LEFT])
			player.x--;
		else if (currentKeyStates[SDL_SCANCODE_RIGHT])
			player.x++;

		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		draw_obj(renderer, player);
		SDL_RenderPresent(renderer);
	}

	close_stuff(window, renderer);
	return 0;
}
