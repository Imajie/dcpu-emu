/*
 * File:	main.c
 *
 * Testing
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <poll.h>
#include <sys/time.h>

#include "dcpu.h"
#include "dcpu_types.h"
#include "hardware/sdl.h"
#include "hardware/LEM1802.h"
#include "hardware/generic_keyboard.h"
#include "hardware/generic_clock.h"

uint16_t mem[0x10000];

int killed = 0;
void _kill( int x )
{
	killed = 1;
}

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
	fprintf( stdout, "PC=0x%04x SP=0x%04x EX=0x%04x IA=0x%04x IAQ=0x%04x clocks=%i\tstate=%s\n",
			dcpu->PC, dcpu->SP, dcpu->EX, dcpu->IA, dcpu->IAQ, dcpu->clocks, state_strs[dcpu->state]);

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
	dcpu_add_hardware( &dcpu, create_Keyboard( ) );
	dcpu_add_hardware( &dcpu, create_Clock( ) );

	signal( SIGKILL, _kill );
	signal( SIGTERM, _kill );
	signal( SIGINT, _kill );

	struct timeval start, end;
	while( !dcpu_complete( &dcpu ) && !killed && !sdl_killed )
	{
		gettimeofday( &start, NULL );
		int ticks = dcpu_tick( &dcpu );
		sdl_handle_events();
		//reg_debug( &dcpu );
		
		gettimeofday( &end, NULL );
		int elapsed = (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec);

		int to_sleep = 10*ticks - elapsed;

		if( to_sleep > 0 )
		{
			usleep( to_sleep );
		}
	}

	struct pollfd pollinfo[1];
	pollinfo[0].fd = 0;
	pollinfo[0].events = POLLIN;

	printf("Run complete press enter to exit..."); fflush(stdout);
	while( !killed && !sdl_killed && !poll( pollinfo, 1, 0 ) )
	{
		sdl_handle_events();
	}
	
	dcpu_free( &dcpu );
	
	return 0;
}
