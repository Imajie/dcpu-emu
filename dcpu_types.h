/*
 * File:	dcpu_types.h
 *
 * Typedefs for internal dcpu usage
 */
#ifndef DCPU_TYPES_H
#define DCPU_TYPES_H

#include <stdint.h>

/* makeup of an instruction */
typedef union {
	uint16_t all;
	struct {
		uint16_t o : 5;
		uint16_t b : 5;
		uint16_t a : 6;
	};
} dcpu_inst_t;



#endif
