/*
 * File:	dcpu_ops.h
 *
 * DCPU operations
 */
#ifndef DCPU_OPS_H
#define DCPU_OPS_H

#include "dcpu.h"

/*
 * Perform the next opcode
 */
int dcpu_do_inst( dcpu16_t *dcpu );

/*
 * dcpu_interrupt
 *
 * generate an interrupt
 */
void dcpu_interrupt( dcpu16_t *dcpu, dcpu_reg_t msg );


#endif
