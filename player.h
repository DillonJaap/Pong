#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "objects.h"

void handle_player_input(Obj* player);
Obj init_player(SDL_Renderer* renderer);

#endif
