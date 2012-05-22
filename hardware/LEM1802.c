/*
 * File:	LEM1802.c
 *
 * Implementation of the LEM1802 monitor
 */
#include "../hardware_device.h"
#include "LEM1802.h"
#include "LEM1802_builtin.h"
#include "sdl.h"
#include <stdlib.h>
#include <stdio.h>

#define HW_ID	0x7349F615
#define HW_VER	0x1802
#define MAN_ID	0x1C6C8B36

/* pixel resolution of the screen */
#define SCREEN_WIDTH	128
#define SCREEN_HEIGHT	96

/* number of characters in each dimension */
#define X_RES			32
#define Y_RES			12

/* character size */
#define CHAR_WIDTH		4
#define CHAR_HEIGHT		8

/* Interrupt types */
#define MEM_MAP_SCREEN		0
#define MEM_MAP_FONT		1
#define MEM_MAP_PALLET		2
#define SET_BORDER_COLOR	3
#define MEM_DUMP_FONT		4
#define MEM_DUMP_PALLET		5

/* internal montior state */
typedef struct {
	/* addr of character ram */
	display_t *display;

	/* copy of display ram */
	display_t d_copy[X_RES*Y_RES];

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
 * Default FONT and PALLET
 */
font_t *default_font = LEM1802_font;
pallet_t *default_pallet = LEM1802_pallet;

/*
 * init_LEM1802
 *
 * Initialize the window, and load font map
 */
LEM1802_t* init_LEM1802( unsigned int monitor_scale )
{
	LEM1802_t *monitor = (LEM1802_t*)calloc(1, sizeof(LEM1802_t));
	
	monitor->display = NULL;
	monitor->font = default_font;
	monitor->pallet = default_pallet;
	monitor->border = 0x0;

	monitor->screen = sdl_init( SCREEN_WIDTH*monitor_scale, SCREEN_HEIGHT*monitor_scale );
	monitor->monitor_scale = monitor_scale;

	return monitor;
}

/*
 * tick_LEM1802
 *
 * update the display
 */
void tick_LEM1802( dcpu16_t* dcpu, dcpu_hardware_t *hardware )
{
	LEM1802_t *monitor = (void*)hardware->device_data;
	int update = 0;
	
	// update the screen
	if( monitor->display )
	{
		for( int x = 0; x < X_RES; x++ )
		{
			for( int y = 0; y < Y_RES; y++ )
			{
				// don't draw if we don't need to
				if( monitor->d_copy[x+X_RES*y].all == monitor->display[x+X_RES*y].all )
					continue;

				// new character
				monitor->d_copy[x+X_RES*y].all = monitor->display[x+X_RES*y].all;
				update = 1;
				
				// get the properties of this character
				font_t ch = monitor->font[monitor->display[x+X_RES*y].c];
				pallet_t fg = monitor->pallet[monitor->display[x+X_RES*y].fg];
				pallet_t bg = monitor->pallet[monitor->display[x+X_RES*y].bg];

				for( int cx = 0; cx < CHAR_WIDTH; cx++ )
				{
					for( int cy = 0; cy < CHAR_HEIGHT; cy++ )
					{
						for( int i = 0; i < monitor->monitor_scale; i++ )
						{
							for( int j = 0; j < monitor->monitor_scale; j++ )
							{
								int x_i, y_i;
								x_i = x*CHAR_WIDTH*monitor->monitor_scale+cx*monitor->monitor_scale+i;
								y_i = y*CHAR_HEIGHT*monitor->monitor_scale+cy*monitor->monitor_scale+j;
								if( ch.cols[cx] & (1<<cy) )
									sdl_draw_screen( monitor->screen, x_i, y_i, PALLET_TO_RGB(fg) );
								else
									sdl_draw_screen( monitor->screen, x_i, y_i, PALLET_TO_RGB(bg) );
							}
						}
					}
				}
			}
		}
	}
	if( update )
		SDL_Flip( monitor->screen );
}

/*
 * interrupt_LEM1802
 *
 * handle interrupts
 */
void interrupt_LEM1802( dcpu16_t* dcpu, dcpu_hardware_t *hardware )
{
	LEM1802_t *monitor = (void*)hardware->device_data;
	dcpu_reg_t a = dcpu->A;
	long b = dcpu->B;
	font_t* f_out;
	pallet_t* p_out;
	switch(a)
	{
		case MEM_MAP_SCREEN:
			monitor->display = (display_t*)(&dcpu->memory[b]);
			break;
		case MEM_MAP_FONT:
			monitor->font = (font_t*)(&dcpu->memory[b]);
			break;
		case MEM_MAP_PALLET:
			monitor->pallet = (pallet_t*)(&dcpu->memory[b]);
			break;
		case SET_BORDER_COLOR:
			monitor->border = dcpu->B & 0xF;
			break;
		case MEM_DUMP_FONT:
			f_out = (font_t*)&dcpu->memory[dcpu->B];
			for( int i = 0; i < 128; i++ )
			{
				*f_out++ = default_font[i];
			}
			break;
		case MEM_DUMP_PALLET:
			p_out = (pallet_t*)&dcpu->memory[dcpu->B];
			for( int i = 0; i < 16; i++ )
			{
				*p_out++ = default_pallet[i];
			}
			break;
		default:
			fprintf( stderr, "LEM1802: Unknown interrupt message %i\n", a);
			break;
	}
	return;
}

/*
 * create_LEM1802
 *
 * Create a new LEM1802 monitor
 */
dcpu_hardware_t* create_LEM1802( unsigned int monitor_scale )
{
	NEW_HARDWARE(LEM1802, monitor_scale);
	/*
	dcpu_hardware_t* hardware = calloc(1, sizeof(dcpu_hardware_t));

	// setup hardware interface
	hardware->interrupt	= interrupt_LEM1802;
	hardware->tick		= tick_LEM1802;
	hardware->hw_id		= HW_ID;
	hardware->hw_ver	= HW_VER;
	hardware->man_id	= MAN_ID;


	// intialize window, load font, etc...
	hardware->device_data = (void*)init_LEM1802( monitor_scale );

	return hardware;
	*/
}

