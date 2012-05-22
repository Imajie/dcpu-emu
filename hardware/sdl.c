/*
 * File:	sdl.c
 *
 * SDL interface functions
 */

#include <stdio.h>
#include <SDL.h>
#include "sdl.h"

/*
 * sdl_init
 *
 * Initialize SDL and create a window
 */
SDL_Surface * sdl_init(unsigned int width, unsigned int height)
{
	SDL_Surface *screen;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return NULL;

	if (!(screen = SDL_SetVideoMode(width, height, DEPTH, SDL_HWSURFACE)))
	{
		SDL_Quit();
	}
	return screen;
}

/*
 * setpixel
 *
 * Actually draw on the screen at (x,y)
 */
void setpixel(SDL_Surface *screen, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t *pixmem32;
	uint32_t color;  

	color = SDL_MapRGB( screen->format, r, g, b );

	pixmem32 = (uint32_t*) screen->pixels  + y + x;
	*pixmem32 = color;
}

/*
 * sdl_draw_screen
 *
 * Draw the color at the corresponding pixel
 */
void sdl_draw_screen(SDL_Surface* screen, int x, int y, uint8_t r, uint8_t g, uint8_t b )
{ 
	int ytimesw;

	if(SDL_MUSTLOCK(screen)) 
	{
		if(SDL_LockSurface(screen) < 0) return;
	}

	ytimesw = y*screen->pitch/BPP;

	setpixel(screen, x, ytimesw, r, g, b);

	if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
}


/*
 * sdl_handle_events
 *
 * Handle SDL events
 */
int sdl_handle_events( SDL_Surface *screen )
{
	int quit = 0;
	SDL_Event event;
	while(SDL_PollEvent(&event)) 
	{      
		switch (event.type) 
		{
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYDOWN:
				// TODO
				break;
		}
	}
	return quit;

	SDL_Flip(screen);
}

