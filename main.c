/*
 * File:	main.c
 *
 * Testing
 */
#include <stdio.h>
#include <stdlib.h>

#include "dcpu.h"
#include "dcpu_types.h"
#include "hardware/LEM1802.h"


uint16_t mem[0x10000];

void read_prog( FILE *file )
{
	uint8_t *ptr = (uint8_t*)mem;

	while( !feof(file) )
	{
		fread(ptr++, 1, 1, file);
	}
}

void reg_debug( dcpu16_t *dcpu )
{
	/* data registers */
	fprintf( stdout, " A=0x%04x  B=0x%04x  C=0x%04x  X=0x%04x  Y=0x%04x  Z=0x%04x  I=0x%04x  J=0x%04x\n", 
			dcpu->A, dcpu->B, dcpu->C, dcpu->X, dcpu->Y, dcpu->Z, dcpu->I, dcpu->J);

	/* state/extra */
	fprintf( stdout, "PC=0x%04x SP=0x%04x EX=0x%04x IA=0x%04x clocks=%i\n",
			dcpu->PC, dcpu->SP, dcpu->EX, dcpu->IA, dcpu->clocks);

	fprintf( stdout, "\n" );
}

int main( int argc, char ** argv )
{
	dcpu16_t dcpu;

	dcpu_inst_t *inst;

	if( argc < 2 )
	{
		fprintf( stderr, "Usage: %s file.bin\n", argv[0] );
		exit(1);
	}

	FILE *file = fopen(argv[1], "rb");
	if( !file )
	{
		perror(argv[1]);
		exit(1);
	}

	read_prog(file);
	fclose(file);

	dcpu_create( &dcpu, mem );

	dcpu_add_hardware( &dcpu, create_LEM1802( 5 ) );

	for( int i = 0; i < 100; i++ )
	{
		dcpu_tick( &dcpu );
		reg_debug( &dcpu );
	}

	printf("Run complete press enter to exit...");
	getchar();
	
	dcpu_free( &dcpu );
	
	return 0;
}
