/*
 * File:	hardware_device.h
 *
 * Generic hardware device interface
 */
#ifndef HARDWARE_DEVICE_H
#define HARDWARE_DEVICE_H

#include <stdint.h>
#include "dcpu.h"

#define NEW_HARDWARE(type, ...) 										\
	dcpu_hardware_t* hardware = calloc(1, sizeof(dcpu_hardware_t));		\
																		\
	hardware->interrupt	= interrupt_##type;								\
	hardware->tick		= tick_##type;									\
	hardware->hw_id		= HW_ID;										\
	hardware->hw_ver	= HW_VER;										\
	hardware->man_id	= MAN_ID;										\
																		\
	hardware->device_data = (void*)init_##type(__VA_ARGS__);			\
	return hardware;

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
