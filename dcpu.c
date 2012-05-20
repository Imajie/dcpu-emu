/*
 * File:	dcpu.c
 *
 * Implementation of the dcpu16
 */

#include "dcpu.h"
#include "dcpu_types.h"
#include "dcpu_ops.h"

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

	return;
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
	dcpu->clocks += dcpu_do_inst( dcpu );
}

