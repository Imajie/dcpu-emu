/*
 * File:	sdl.h
 *
 * Header for SDL related functions
 */
#ifndef SDL_H
#define SDL_H

#include <SDL.h>

#define BPP 4
#define DEPTH 32

extern int sdl_killed;

/*
 * sdl_init
 *
 * Initialize SDL and create a window
 */
SDL_Surface * sdl_init(unsigned int width, unsigned int height);

/*
 * sdl_draw_screen
 *
 * Draw the color at the corresponding pixel
 */
void sdl_draw_screen(SDL_Surface* screen, int x, int y, uint8_t r, uint8_t g, uint8_t b );

/*
 * sdl_handle_events
 *
 * Handle SDL events
 */
int sdl_handle_events(void);

#endif
