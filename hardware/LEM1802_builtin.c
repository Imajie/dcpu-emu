/*
 * File:	LEM1802_builtin.c
 *
 * Defines the builtin font and pallet
 */
#include "LEM1802_builtin.h"

font_t LEM1802_font[] =
{
	{{ 0xB7, 0x9E, 0x83, 0xE8 }},
	{{ 0x72, 0x2C, 0x75, 0xF4 }},
	{{ 0x19, 0xBB, 0x7F, 0x8F }},
	{{ 0x85, 0xF9, 0xB1, 0x58 }},
	{{ 0x24, 0x27, 0x24, 0x00 }},
	{{ 0x08, 0x2A, 0x08, 0x00 }},
	{{ 0x00, 0x08, 0x00, 0x00 }},
	{{ 0x08, 0x08, 0x08, 0x08 }},
	{{ 0x00, 0xFF, 0x00, 0x00 }},
	{{ 0x00, 0xF8, 0x08, 0x08 }},
	{{ 0x08, 0xF8, 0x00, 0x00 }},
	{{ 0x08, 0x0F, 0x00, 0x00 }},
	{{ 0x00, 0x0F, 0x08, 0x08 }},
	{{ 0x00, 0xFF, 0x08, 0x08 }},
	{{ 0x08, 0xF8, 0x08, 0x08 }},
	{{ 0x08, 0xFF, 0x00, 0x00 }},
	{{ 0x08, 0x0F, 0x08, 0x08 }},
	{{ 0x08, 0xFF, 0x08, 0x08 }},
	{{ 0x66, 0x33, 0x99, 0xCC }},
	{{ 0x99, 0x33, 0x66, 0xCC }},
	{{ 0xFE, 0xF8, 0xE0, 0x80 }},
	{{ 0x7F, 0x1F, 0x07, 0x01 }},
	{{ 0x01, 0x07, 0x1F, 0x7F }},
	{{ 0x80, 0xE0, 0xF8, 0xFE }},
	{{ 0x55, 0x00, 0xAA, 0x00 }},
	{{ 0x55, 0xAA, 0x55, 0xAA }},
	{{ 0xFF, 0xAA, 0xFF, 0x55 }},
	{{ 0x0F, 0x0F, 0x0F, 0x0F }},
	{{ 0xF0, 0xF0, 0xF0, 0xF0 }},
	{{ 0x00, 0x00, 0xFF, 0xFF }},
	{{ 0xFF, 0xFF, 0x00, 0x00 }},
	{{ 0xFF, 0xFF, 0xFF, 0xFF }},
	{{ 0x00, 0x00, 0x00, 0x00 }},
	{{ 0x00, 0x5F, 0x00, 0x00 }},
	{{ 0x03, 0x00, 0x03, 0x00 }},
	{{ 0x3E, 0x14, 0x3E, 0x00 }},
	{{ 0x26, 0x6B, 0x32, 0x00 }},
	{{ 0x61, 0x1C, 0x43, 0x00 }},
	{{ 0x36, 0x29, 0x76, 0x50 }},
	{{ 0x00, 0x02, 0x01, 0x00 }},
	{{ 0x1C, 0x22, 0x41, 0x00 }},
	{{ 0x41, 0x22, 0x1C, 0x00 }},
	{{ 0x14, 0x08, 0x14, 0x00 }},
	{{ 0x08, 0x1C, 0x08, 0x00 }},
	{{ 0x40, 0x20, 0x00, 0x00 }},
	{{ 0x08, 0x08, 0x08, 0x00 }},
	{{ 0x00, 0x04, 0x00, 0x00 }},
	{{ 0x60, 0x1C, 0x03, 0x00 }},
	{{ 0xE3, 0x94, 0xE3, 0x00 }},
	{{ 0x42, 0x7F, 0x40, 0x00 }},
	{{ 0x62, 0x59, 0x46, 0x00 }},
	{{ 0x22, 0x49, 0x66, 0x00 }},
	{{ 0x0F, 0x08, 0x7F, 0x00 }},
	{{ 0x27, 0x45, 0x39, 0x00 }},
	{{ 0x3E, 0x49, 0x32, 0x00 }},
	{{ 0x61, 0x19, 0x07, 0x00 }},
	{{ 0x36, 0x49, 0x36, 0x00 }},
	{{ 0x26, 0x49, 0x3E, 0x00 }},
	{{ 0x00, 0x24, 0x00, 0x00 }},
	{{ 0x40, 0x24, 0x00, 0x00 }}, 
	{{ 0x08, 0x14, 0x22, 0x41 }},
	{{ 0x14, 0x14, 0x14, 0x00 }},
	{{ 0x41, 0x22, 0x14, 0x08 }},
	{{ 0x02, 0x59, 0x06, 0x00 }},
	{{ 0x3E, 0x59, 0x5E, 0x00 }},
	{{ 0x7E, 0x09, 0x7E, 0x00 }},
	{{ 0x7F, 0x49, 0x36, 0x00 }},
	{{ 0x3E, 0x41, 0x22, 0x00 }},
	{{ 0x7F, 0x41, 0x3E, 0x00 }},
	{{ 0x7F, 0x49, 0x41, 0x00 }},
	{{ 0x7F, 0x09, 0x01, 0x00 }},
	{{ 0x3E, 0x41, 0x7A, 0x00 }},
	{{ 0x7F, 0x08, 0x7F, 0x00 }},
	{{ 0x41, 0x7F, 0x41, 0x00 }},
	{{ 0x20, 0x40, 0x3F, 0x00 }},
	{{ 0x7F, 0x08, 0x77, 0x00 }},
	{{ 0x7F, 0x40, 0x40, 0x00 }},
	{{ 0x7F, 0x06, 0x7F, 0x00 }},
	{{ 0x7F, 0x01, 0x7E, 0x00 }},
	{{ 0x3E, 0x41, 0x3E, 0x00 }},
	{{ 0x7F, 0x09, 0x06, 0x00 }},
	{{ 0x3E, 0x41, 0xBE, 0x00 }},
	{{ 0x7F, 0x08, 0x76, 0x00 }},
	{{ 0x26, 0x48, 0x32, 0x00 }},
	{{ 0x01, 0x7F, 0x01, 0x00 }},
	{{ 0x3F, 0x40, 0x3F, 0x00 }},
	{{ 0x1F, 0x60, 0x1F, 0x00 }},
	{{ 0x7F, 0x30, 0x7F, 0x00 }},
	{{ 0x77, 0x08, 0x77, 0x00 }},
	{{ 0x07, 0x78, 0x07, 0x00 }},
	{{ 0x71, 0x49, 0x47, 0x00 }},
	{{ 0x00, 0x7F, 0x41, 0x00 }},
	{{ 0x03, 0x1C, 0x60, 0x00 }},
	{{ 0x00, 0x41, 0x7F, 0x00 }},
	{{ 0x02, 0x01, 0x02, 0x00 }},
	{{ 0x80, 0x80, 0x80, 0x00 }},
	{{ 0x00, 0x01, 0x02, 0x00 }},
	{{ 0x24, 0x54, 0x78, 0x00 }},
	{{ 0x7F, 0x44, 0x38, 0x00 }},
	{{ 0x38, 0x44, 0x28, 0x00 }},
	{{ 0x38, 0x44, 0x7F, 0x00 }},
	{{ 0x38, 0x54, 0x58, 0x00 }},
	{{ 0x08, 0x7E, 0x09, 0x00 }},
	{{ 0x48, 0x54, 0x3D, 0x00 }},
	{{ 0x7F, 0x40, 0x78, 0x00 }},
	{{ 0x44, 0x7D, 0x40, 0x00 }},
	{{ 0x20, 0x40, 0x3D, 0x00 }},
	{{ 0x7F, 0x10, 0x6C, 0x00 }},
	{{ 0x41, 0x7F, 0x40, 0x00 }},
	{{ 0x7C, 0x18, 0x7C, 0x00 }},
	{{ 0x7C, 0x04, 0x78, 0x00 }},
	{{ 0x38, 0x44, 0x38, 0x00 }},
	{{ 0x7C, 0x14, 0x08, 0x00 }},
	{{ 0x08, 0x14, 0x7C, 0x00 }},
	{{ 0x7C, 0x04, 0x08, 0x00 }},
	{{ 0x48, 0x54, 0x24, 0x00 }},
	{{ 0x04, 0x3E, 0x44, 0x00 }},
	{{ 0x3C, 0x40, 0x7C, 0x00 }},
	{{ 0x1C, 0x60, 0x1C, 0x00 }}, 
	{{ 0x7C, 0x30, 0x7C, 0x00 }},
	{{ 0x6C, 0x10, 0x6C, 0x00 }},
	{{ 0x4C, 0x50, 0x3C, 0x00 }},
	{{ 0x64, 0x54, 0x4C, 0x00 }},
	{{ 0x08, 0x36, 0x41, 0x00 }},
	{{ 0x00, 0x77, 0x00, 0x00 }},
	{{ 0x41, 0x36, 0x08, 0x00 }},
	{{ 0x02, 0x01, 0x02, 0x01 }},
	{{ 0x02, 0x05, 0x02, 0x00 }}
};

pallet_t LEM1802_pallet[] =
{
	{ .b = 0x0, .g = 0x0, .r = 0x0 },
	{ .b = 0x0, .g = 0x0, .r = 0xA },
	{ .b = 0x0, .g = 0xA, .r = 0x0 },
	{ .b = 0x0, .g = 0xA, .r = 0xA },
	{ .b = 0xA, .g = 0x0, .r = 0x0 },
	{ .b = 0xA, .g = 0x0, .r = 0xA },
	{ .b = 0xA, .g = 0x5, .r = 0x0 },
	{ .b = 0xA, .g = 0xA, .r = 0xA },
	{ .b = 0x5, .g = 0x5, .r = 0x5 },
	{ .b = 0xF, .g = 0x5, .r = 0x5 },
	{ .b = 0x5, .g = 0xF, .r = 0x5 },
	{ .b = 0xF, .g = 0xF, .r = 0x5 },
	{ .b = 0x5, .g = 0x5, .r = 0xF },
	{ .b = 0xF, .g = 0x5, .r = 0xF },
	{ .b = 0x5, .g = 0xF, .r = 0xF },
	{ .b = 0xF, .g = 0xF, .r = 0xF }
};
