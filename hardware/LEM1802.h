/*
 * File:	LEM1802.h
 *
 * Implementation of the LEM1802 monitor
 */
#ifndef LEM1802_H
#define LEM1802_H

#include "../hardware_device.h"
#include "sdl.h"

/* display ram format */
typedef union {
	uint16_t all;
	struct {
		uint16_t c : 7;
		uint16_t blink : 1;
		uint16_t fg : 4;
		uint16_t bg : 4;
	};
} display_t;

/* font format */
typedef struct {
	uint8_t cols[4];
} font_t;

/* pallet format */
typedef union {
	uint16_t all;
	struct {
		uint16_t b : 4;
		uint16_t g : 4;
		uint16_t r : 4;
		uint16_t resv : 4;
	};
} pallet_t;
#define _4_to_8(a)	(((a)<<4) | (a))
#define PALLET_TO_RGB(x) _4_to_8((x).r), _4_to_8((x).g), _4_to_8((x).b)

/* internal montior state */
typedef struct {
	/* pointer to character ram */
	display_t *display;

	/* pointer to font ram */
	font_t *font;

	/* pointer to pallet ram */
	pallet_t *pallet;

	/* monitor scale */
	unsigned int monitor_scale;

	/* SDL surface */
	SDL_Surface *screen;

	/* border color */
	char border;

} LEM1802_t;

/*
 * create_LEM1802
 *
 * Create a new LEM1802 monitor
 */
dcpu_hardware_t* create_LEM1802(unsigned int monitor_scale);

#endif
