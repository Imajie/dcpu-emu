/*
 * File:	generic_clock.c
 *
 * Implements a generic clock
 */
#include <stdlib.h>
#include <stdio.h>

#include "generic_clock.h"
#include "../dcpu.h"
#include "../hardware_device.h"

#define HW_ID	0x12D0B402
#define HW_VER	0x0001
#define MAN_ID	0x00000000

// interrupt types
#define CLOCK_DIV	0
#define CLOCK_GET	1
#define CLOCK_MSG	2

typedef struct clock
{
	uint16_t int_msg;

	uint16_t div;
	uint16_t ticks;
	unsigned long start;

} generic_clock_t;

/*
 * init_Clock
 *
 * Initialize the clock
 */
generic_clock_t* init_Clock(void)
{
	generic_clock_t *clock = calloc(1, sizeof(generic_clock_t));

	clock->int_msg = 0;
	clock->div = 0;
	clock->ticks = 0;
	clock->start = 0;

	return clock;
}

/*
 * tick_Clock()
 *
 * Process a step
 */
void tick_Clock( dcpu16_t *dcpu, dcpu_hardware_t *hardware )
{
	generic_clock_t *clock = (void*)hardware->device_data;

	unsigned long elapsed = dcpu->clocks - clock->start;


	if( clock->div )
	{
		double d_elapsed = elapsed * (1.0/dcpu->frequency);
		double d_tick    = clock->div / 60.0;

		if( (int)(d_elapsed / d_tick) != clock->ticks )
		{
			clock->ticks = (int)(d_elapsed / d_tick);

			if( clock->int_msg )
			{
				dcpu->interrupt( dcpu, clock->int_msg );
			}

		}
	}

}

/*
 * interrupt_Clock()
 *
 * handle interrupts
 */
void interrupt_Clock( dcpu16_t *dcpu, dcpu_hardware_t *hardware )
{
	generic_clock_t *clock = (void*)hardware->device_data;

	switch(dcpu->A)
	{
		case CLOCK_DIV:
			clock->div = dcpu->B;
			clock->start = dcpu->clocks;
			break;
		case CLOCK_GET:
			dcpu->C = clock->ticks;
			break;
		case CLOCK_MSG:
			clock->int_msg = dcpu->B;
			break;
		default:
			fprintf(stderr, "Clock: undefined interrupt message 0x%04x\n", dcpu->A);
	}
}

/*
 * create_Clock()
 *
 * Create a generic clock
 */
dcpu_hardware_t* create_Clock(void)
{
	NEW_HARDWARE(Clock);
}

