/*
 * File:	dcpu.c
 *
 * Implementation of the dcpu16
 */

#include "dcpu.h"
#include "dcpu_types.h"
#include "dcpu_ops.h"
#include "hardware_device.h"
#include <stdlib.h>

const char *state_strs[] = 
{
	"NORMAL", "SKIPPING", "HALTING", "ON FIRE"
};

/*
 * dcpu_create
 *
 * Create a new dcpu16 with the specified program memory
 */
void dcpu_create( dcpu16_t *dcpu, dcpu_ram_t prog )
{
	dcpu->state = NORMAL;
	dcpu->clocks = 0;

	// everything starts out zero'd
	dcpu->A = 0;
	dcpu->B = 0;
	dcpu->C = 0;
	
	dcpu->I = 0;
	dcpu->J = 0;

	dcpu->X = 0;
	dcpu->Y = 0;
	dcpu->Z = 0;

	dcpu->EX = 0;
	dcpu->IA = 0;
	dcpu->PC = 0;
	dcpu->SP = 0;

	dcpu->memory = prog;

	dcpu->hardware = NULL;
	dcpu->hardware_count = 0;

	dcpu->IAQ = 0;
	dcpu->interrupt = dcpu_interrupt;

	dcpu->ib_start = 0;
	dcpu->ib_end = 0;
	dcpu->ib_size = 0;

	return;
}

/*
 * dcpu_add_hardware
 *
 * Attach the provided hardware device to the DCPU
 */
int dcpu_add_hardware( dcpu16_t *dcpu, dcpu_hardware_t *hardware )
{
	if( dcpu->hardware_count >= MAX_HARDWARE )
		return -1;

	void *temp = realloc(dcpu->hardware, (dcpu->hardware_count+1)*sizeof(dcpu_hardware_t*));
	if( !temp )
		return -1;

	dcpu->hardware = temp;
	dcpu->hardware_count++;

	dcpu->hardware[dcpu->hardware_count-1] = hardware;
	return 0;
}

/*
 * dcpu_free
 *
 * cleanup after this dcpu16
 */
void dcpu_free( dcpu16_t *dcpu )
{
	/* NOP */
	return;
}

/*
 * dcpu_tick
 *
 * Execute a clock tick
 */
void dcpu_tick( dcpu16_t *dcpu )
{
	if( dcpu->state != HALTING )
		dcpu->clocks += dcpu_do_inst( dcpu );

	for( int i = 0; i < dcpu->hardware_count; i++ )
	{
		dcpu->hardware[i]->tick(dcpu, dcpu->hardware[i]);
	}

	// check for interrupt
	if( !dcpu->IAQ && dcpu->ib_size > 0 )
	{
		// get message
		uint16_t msg = dcpu->int_buffer[dcpu->ib_start];

		// move pointer
		dcpu->ib_size--;
		dcpu->ib_start = (dcpu->ib_start+1) % 256;

		// interrupt
		dcpu->interrupt( dcpu, msg );
	}
}

/*
 * dcpu_complete
 *
 * Returns zero when SUB PC,1 has not be encountered, nonzero otherwise
 */
int dcpu_complete( dcpu16_t *dcpu )
{
	return dcpu->state == HALTING;
}

