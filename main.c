#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "screen.h"
#include "objects.h"
#include "player.h"
#include "error.h"

const int SCREEN_LENGTH = 400;
const int SCREEN_HEIGHT = 400;


bool init(SDL_Window** window, SDL_Renderer** renderer)
{
	printf("start\n");
	check_error(SDL_Init(SDL_INIT_VIDEO), "could not init video");
	printf("vid\n");
	check_error(TTF_Init(), "could not init ttf");
	printf("ttf\n");


	*window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_LENGTH, 
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	check_null((void*)window, NULL);

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	check_null((void*)renderer, NULL);

	// disable anisotropic filtering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
}

void close_stuff(SDL_Window* window, SDL_Renderer* renderer)
{
	//Destroy Window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	TTF_Quit();
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

void draw_text(SDL_Renderer* renderer, char* text, TTF_Font* font)
{
	SDL_Rect* pos = &(SDL_Rect){0,0,40,40};
	SDL_Color text_color = {0, 0, 0};

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, text_color);
	check_null((void*)text_surface, "failed to create text_surface");

	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	check_null((void*)text_texture, "failed to create text_texture");

	SDL_RenderCopy(renderer, text_texture, NULL, &(text_surface->clip_rect));
}

int main(int argc, char** argv)
{
	// create window and renderer
	SDL_Window* window     = NULL;
	SDL_Renderer* renderer = NULL;
	init(&window, &renderer);

	TTF_Font* font = TTF_OpenFont("./UbuntuMono-Regular.ttf", 28);
	check_null((void*)font, NULL);

	Obj player = init_player(renderer);
	char time_str[16] = "0";

	Uint32 start_time = SDL_GetTicks();
	Uint32 num_frames = 0;
	double avg_fps    = 0;

	while (!quit())
	{
		// handle_inputs
		handle_player_input(&player);

		// clear screen
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		// draw various game objects and text
		draw_obj(renderer, player);
		draw_text(renderer, time_str, font);

		// update screen
		SDL_RenderPresent(renderer);

		// finished rendering frame
		num_frames++;

		// calculate FPS 
		if (num_frames % 30 == 0)
		{
			avg_fps = num_frames / ((SDL_GetTicks() - start_time) / 1000.f);
			snprintf(time_str, 16, "FPS: %lf", avg_fps);
		}

		// reset fps count
		if (num_frames > 120)
		{
			num_frames = 0;
			start_time = SDL_GetTicks();
		}
	}

	close_stuff(window, renderer);
	return 0;
}
