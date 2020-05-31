#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
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

	*window = SDL_CreateWindow( "SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_LENGTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("window could not be created Error: %s\n", SDL_GetError());
		return 0;
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// disable anisotropic filtering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");


	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}
}

void close_stuff(SDL_Window* window, SDL_Renderer* renderer)
{
	//Destroy Window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window   = NULL;
	renderer = NULL;

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

void draw_text(SDL_Renderer* renderer, char* text)
{
	SDL_Color text_color = {0, 0, 0};
	TTF_Font* font = TTF_OpenFont("./UbuntuMono-Regular.ttf", 28);
	if (font == NULL)
	{
		printf("you fucked up!\n");
		return;
	}

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, text_color);
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_Rect* pos = &(SDL_Rect){0,0,40,40};

	SDL_RenderCopy(renderer, text_texture, NULL, &(text_surface->clip_rect));
}

int main(int argc, char** argv)
{
	SDL_Window* window     = NULL;
	SDL_Renderer* renderer = NULL;

	init(&window, &renderer);

	Obj player = init_player(renderer);
	char time_str[16] = "0";

	Uint32 start_time = SDL_GetTicks();
	Uint32 num_frames = 0;
	double avg_fps    = 0;

	while (!quit())
	{
		// TODO turn player input into its own function
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
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
		draw_text(renderer, time_str);

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
