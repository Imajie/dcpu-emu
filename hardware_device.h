/*
 * File:	hardware_device.h
 *
 * Generic hardware device interface
 */
#ifndef HARDWARE_DEVICE_H
#define HARDWARE_DEVICE_H

#include <stdint.h>
#include "dcpu.h"


/* hardware type */
typedef struct dcpu_hardware
{
	void (*interrupt)(dcpu16_t*, struct dcpu_hardware*);
	void (*tick)(dcpu16_t*, struct dcpu_hardware*);
	uint32_t		hw_id;
	uint32_t		hw_ver;
	uint32_t		man_id;
	void*			device_data;
}dcpu_hardware_t;

#endif
