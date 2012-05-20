/*
 * File:	dcpu.h
 *
 * Implementation of the DCPU-16
 *
 */
#ifndef DCPU_H
#define DCPU_H

#include <stdint.h>

/* memory is 16 bit words */
typedef uint16_t* dcpu_ram_t;
typedef uint16_t  dcpu_reg_t;
typedef int16_t   dcpu_reg_sign_t;

/* CPU states */
typedef enum {
	NORMAL, SKIPPING
} dcpu_state_t;

/* cpu registers */
typedef struct {
	/* Registers */
	uint16_t A, B, C, X, Y, Z, I, J;
	/* program counter */
	uint16_t PC;
	/* stack pointer */
	uint16_t SP;
	/* extra/excess */
	uint16_t EX;
	/* interrupt addr */
	uint16_t IA;

	/* memory */
	dcpu_ram_t memory;

	/* extra stuff */
	unsigned long clocks;
	dcpu_state_t state;
} dcpu16_t ;

/*
 * dcpu_create
 *
 * Create a new dcpu16 with the specified program memory
 */
void dcpu_create( dcpu16_t *dcpu, dcpu_ram_t prog );

/*
 * dcpu_free
 *
 * cleanup after this dcpu16
 */
void dcpu_free( dcpu16_t *dcpu );

/*
 * dcpu_tick
 *
 * Execute a clock tick
 */
void dcpu_tick( dcpu16_t *dcpu );

#endif
