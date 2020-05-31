all:
	gcc -I/usr/include/SDL2  *.c $(sdl2-config --libs --cflags) -lSDL2 -lSDL2_ttf -g -o a.out
