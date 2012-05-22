/*
 * File:	generic_keyboard.c
 *
 * Implements a generic keyboard
 */
#include <stdlib.h>

#include "../dcpu.h"
#include "../hardware_device.h"
#include "generic_keyboard.h"
#include "sdl.h"

#define HW_ID	0x30CF7406
#define HW_VER	0x0001
#define MAN_ID	0x00000000

// Interrupt codes
#define KEYBOARD_CLEAR	0
#define KEYBOARD_GET	1
#define KEYBOARD_QUERY	2
#define KEYBOARD_MSG	3

// keystate
#define RELEASED	0
#define PRESSED		1

#define BUFFER_SIZE	20
#define NUM_KEYS	0xFF
typedef struct keyboard {
	// message to send on interrupt
	uint16_t int_msg;

	// keyevent buffer, circular
	uint16_t buffer[BUFFER_SIZE];
	uint16_t b_start, b_end, b_size;
	uint16_t last_b_size;

	// keystates
	uint8_t key_states[NUM_KEYS];

	
} keyboard_t;

/*
 * init_Keyboard()
 *
 * Intitialize the keyboard
 */
keyboard_t* init_Keyboard()
{
	keyboard_t *keyboard = calloc(1, sizeof(keyboard_t));

	// disable interrupts
	keyboard->int_msg = 0;

	// initialize buffer
	keyboard->b_start = 0;
	keyboard->b_end = 0;
	keyboard->b_size = 0;
	keyboard->last_b_size = 0;

	// set all keys to released
	for( int i = 0; i < NUM_KEYS; i++ )
	{
		keyboard->key_states[i] = RELEASED;
	}

	sdl_attach_keyboard( keyboard );

	return keyboard;
}

/*
 * event_callback_Keyboard()
 * 
 * Handle an SDL key event
 */
void event_callback_Keyboard( keyboard_t *keyboard, uint16_t keysym, uint8_t state )
{
	uint16_t to_add = 0;
	if( keysym >= 0x20 && keysym <= 0x7F && state )
	{
		// ASCII, only listen to PRESSED
		to_add = keysym;
	}
	else
	{
		switch(keysym)
		{
			case SDLK_BACKSPACE:
				to_add = 0x10;
				break;
			case SDLK_RETURN:
				to_add = 0x11;
				break;
			case SDLK_INSERT:
				to_add = 0x12;
				break;
			case SDLK_DELETE:
				to_add = 0x13;
				break;
			case SDLK_UP:
				to_add = 0x80;
				break;
			case SDLK_DOWN:
				to_add = 0x81;
				break;
			case SDLK_LEFT:
				to_add = 0x82;
				break;
			case SDLK_RIGHT:
				to_add = 0x84;
				break;
			case SDLK_LSHIFT: case SDLK_RSHIFT:
				to_add = 0x90;
				break;
			case SDLK_LCTRL: case SDLK_RCTRL:
				to_add = 0x91;
				break;
		}
	}

	if( to_add )
	{
		if( keyboard->b_size == BUFFER_SIZE )
		{
			fprintf(stderr, "Keyboard: Buffer full, dropping keys\n");
			return;
		}

		keyboard->buffer[keyboard->b_end] = to_add;

		// advance pointer
		keyboard->b_size++;
		keyboard->b_end = (keyboard->b_end+1) % BUFFER_SIZE;

		keyboard->key_states[to_add] = state;
	}
}

/*
 * tick_Keyboard()
 * 
 * Update for this time step
 */
void tick_Keyboard( dcpu16_t *dcpu, dcpu_hardware_t *hardware )
{
	keyboard_t *keyboard = (void*)hardware->device_data;

	if( keyboard->int_msg != 0 && keyboard->b_size > keyboard->last_b_size )
	{
		dcpu->interrupt( dcpu, keyboard->int_msg );
	}
	keyboard->last_b_size = keyboard->b_size;

}

/*
 * interrupt_Keyboard()
 *
 * Handle interrupt
 */
void interrupt_Keyboard( dcpu16_t *dcpu, dcpu_hardware_t *hardware )
{
	keyboard_t *keyboard = (void*)hardware->device_data;

	switch(dcpu->A)
	{
		case KEYBOARD_CLEAR:
			// clear out the buffer
			keyboard->b_start = 0;
			keyboard->b_end = 0;
			keyboard->b_size = 0;
			break;
		case KEYBOARD_GET:
			if( keyboard->b_size != 0 )
			{
				dcpu->C = keyboard->buffer[keyboard->b_start];

				// advance pointer
				keyboard->b_size--;
				keyboard->b_start = (keyboard->b_start+1) % BUFFER_SIZE;
			}
			else
			{
				// no key
				dcpu->C = 0x0000;
			}

			break;
		case KEYBOARD_QUERY:
			dcpu->C = (keyboard->key_states[dcpu->B] == PRESSED);
			break;
		case KEYBOARD_MSG:
			keyboard->int_msg = dcpu->B;
			break;
		default:
			fprintf(stderr, "Keyboard: unknown message 0x%04x\n", dcpu->A);
			break;
	}
}

/*
 * create_Keyboard()
 *
 * Create the generic keyboard
 */
dcpu_hardware_t* create_Keyboard(void)
{
	NEW_HARDWARE(Keyboard);
}

