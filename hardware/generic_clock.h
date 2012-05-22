/*
 * File:	generic_clock.h
 *
 * Implements a generic clock
 */
#ifndef GENERIC_CLOCK_H
#define GENERIC_CLOCK_H

#include "../dcpu.h"
#include "../hardware_device.h"

/*
 * create_Clock()
 *
 * Create a generic clock
 */
dcpu_hardware_t* create_Clock(void);

#endif
