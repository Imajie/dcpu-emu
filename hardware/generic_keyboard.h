/*
 * File:	generic_keyboard.h
 *
 * Implements a generic keyboard
 */
#ifndef GENERIC_KEYBOARD_H
#define GENERIC_KEYBOARD_H

#include "../hardware_device.h"

struct keyboard;
typedef struct keyboard keyboard_t;

/*
 * event_callback_Keyboard()
 * 
 * Handle an SDL key event
 */
void event_callback_Keyboard( keyboard_t *keyboard, uint16_t keysym, uint8_t state );

/*
 * create_Keyboard()
 *
 * Create the generic keyboard
 */
dcpu_hardware_t* create_Keyboard(void);


#endif
