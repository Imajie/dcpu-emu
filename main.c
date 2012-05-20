/*
 * File:	main.c
 *
 * Testing
 */
#include "dcpu.h"
#include "dcpu_types.h"

uint16_t mem[0x8000] = 
{
	0x0000, 0x0000
};

int main( int argc, char ** argv )
{
	dcpu16_t dcpu;

	dcpu_inst_t *inst;

	inst = (void*)&mem[0];
	/* ADD A, 0x01 */
	inst->o = 0x02;
	inst->a = 0x22;
	inst->b = 0x00;

	inst = (void*)&mem[1];
	/* SET PC, 0x00 */
	inst->o = 0x01;
	inst->a = 0x21;
	inst->b = 0x1C;


	dcpu_create( &dcpu, mem );

	for( int i = 0; i < 100; i++ )
	{
		dcpu_tick( &dcpu );
		printf("A = %i\n", dcpu.A);
	}

	dcpu_free( &dcpu );
	
	return 0;
}
