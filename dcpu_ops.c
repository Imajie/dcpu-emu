/*
 * File:	dcpu_ops.c
 *
 * implements dcpu opcodes
 */

#include <stdio.h>

#include "dcpu.h"
#include "dcpu_types.h"
#include "dcpu_ops.h"

/* forward declarations */
int dcpu_special( dcpu16_t *dcpu, dcpu_inst_t inst);
int dcpu_set( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_add( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_sub( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_mul( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_mli( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_div( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_dvi( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_mod( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_and( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_bor( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_xor( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_shr( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_asr( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_shl( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ifb( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ifc( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ife( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ifn( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ifg( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ifa( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ifl( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ifu( dcpu16_t *dcpu, dcpu_inst_t inst );

int dcpu_jsr( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_int( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ing( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_ins( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_hwn( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_hwq( dcpu16_t *dcpu, dcpu_inst_t inst );
int dcpu_hwi( dcpu16_t *dcpu, dcpu_inst_t inst );

int dcpu_inval( dcpu16_t *dcpu, dcpu_inst_t inst );

/*
 * lookup table for instructions
 */
int (*dcpu_ops[])( dcpu16_t *dcpu, dcpu_inst_t inst ) = 
{
	dcpu_special,	/* 0x00 = special ops */
	dcpu_set,		/* 0x01 = SET */
	dcpu_add,		/* 0x02 = ADD */
	dcpu_sub,		/* 0x03 = SUB */
	dcpu_mul,		/* 0x04 = MUL */
	dcpu_mli,		/* 0x05 = MLI */
	dcpu_div,		/* 0x06 = DIV */
	dcpu_dvi,		/* 0x07 = DVI */
	dcpu_mod,		/* 0x08 = MOD */
	dcpu_and,		/* 0x09 = AND */
	dcpu_bor,		/* 0x0a = BOR */
	dcpu_xor,		/* 0x0b = XOR */
	dcpu_shr,		/* 0x0c = SHR */
	dcpu_asr,		/* 0x0d = ASR */
	dcpu_shl,		/* 0x0e = SHL */
	dcpu_inval,		/* 0x0f = INVALID */
	dcpu_ifb,		/* 0x10 = IFB */
	dcpu_ifc,		/* 0x11 = IFC */
	dcpu_ife,		/* 0x12 = IFE */
	dcpu_ifn,		/* 0x13 = IFN */
	dcpu_ifg,		/* 0x14 = IFG */
	dcpu_ifa,		/* 0x15 = IFA */
	dcpu_ifl,		/* 0x16 = IFL */
	dcpu_ifu,		/* 0x17 = IFU */
	dcpu_inval,		/* 0x18 = INVALID */
	dcpu_inval,		/* 0x19 = INVALID */
	dcpu_inval,		/* 0x1a = INVALID */
	dcpu_inval,		/* 0x1b = INVALID */
	dcpu_inval,		/* 0x1c = INVALID */
	dcpu_inval,		/* 0x1d = INVALID */
	dcpu_inval,		/* 0x1e = INVALID */
	dcpu_inval		/* 0x1f = INVALID */
};

/* 
 * special ops lookup
 */
int (*dcpu_special_ops[])( dcpu16_t *dcpu, dcpu_inst_t inst ) =
{
	dcpu_inval,		/* 0x00 = INVALD */
	dcpu_jsr,		/* 0x01 = JSR */
	dcpu_inval,		/* 0x02 = INVALD */
	dcpu_inval,		/* 0x03 = INVALD */
	dcpu_inval,		/* 0x04 = INVALD */
	dcpu_inval,		/* 0x05 = INVALD */
	dcpu_inval,		/* 0x06 = INVALD */
	dcpu_inval,		/* 0x07 = INVALD */
	dcpu_int,		/* 0x08 = INT */
	dcpu_ing,		/* 0x09 = ING */
	dcpu_ins,		/* 0x0a = INS */
	dcpu_inval,		/* 0x0b = INVALD */
	dcpu_inval,		/* 0x0c = INVALD */
	dcpu_inval,		/* 0x0d = INVALD */
	dcpu_inval,		/* 0x0e = INVALD */
	dcpu_inval,		/* 0x0f = INVALD */
	dcpu_hwn,		/* 0x10 = HWN */
	dcpu_hwq,		/* 0x11 = HWQ */
	dcpu_hwi,		/* 0x12 = HWI */
	dcpu_inval,		/* 0x13 = INVALD */
	dcpu_inval,		/* 0x14 = INVALD */
	dcpu_inval,		/* 0x15 = INVALD */
	dcpu_inval,		/* 0x16 = INVALD */
	dcpu_inval,		/* 0x17 = INVALD */
	dcpu_inval,		/* 0x18 = INVALD */
	dcpu_inval,		/* 0x19 = INVALD */
	dcpu_inval,		/* 0x1a = INVALD */
	dcpu_inval,		/* 0x1b = INVALD */
	dcpu_inval,		/* 0x1c = INVALD */
	dcpu_inval,		/* 0x1d = INVALD */
	dcpu_inval,		/* 0x1e = INVALD */
	dcpu_inval,		/* 0x1f = INVALD */
};

/* 
 * helpers 
 */
#define A_TYPE 0x00
#define B_TYPE 0x01

void set( dcpu16_t *dcpu, dcpu_reg_t val, dcpu_reg_t res )
{
	switch(val)
	{
		// register
		case 0x00: dcpu->A = res; break;
		case 0x01: dcpu->B = res; break;
		case 0x02: dcpu->C = res; break;
		case 0x03: dcpu->X = res; break;
		case 0x04: dcpu->Y = res; break;
		case 0x05: dcpu->Z = res; break;
		case 0x06: dcpu->I = res; break;
		case 0x07: dcpu->J = res; break;

		// [register]
		case 0x08: dcpu->memory[dcpu->A] = res; break;
		case 0x09: dcpu->memory[dcpu->B] = res; break;
		case 0x0a: dcpu->memory[dcpu->C] = res; break;
		case 0x0b: dcpu->memory[dcpu->X] = res; break;
		case 0x0c: dcpu->memory[dcpu->Y] = res; break;
		case 0x0d: dcpu->memory[dcpu->Z] = res; break;
		case 0x0e: dcpu->memory[dcpu->I] = res; break;
		case 0x0f: dcpu->memory[dcpu->J] = res; break;

		// [register+next_word]
		case 0x10: dcpu->memory[dcpu->A + dcpu->memory[dcpu->PC++]] = res; break;
		case 0x11: dcpu->memory[dcpu->B + dcpu->memory[dcpu->PC++]] = res; break;
		case 0x12: dcpu->memory[dcpu->C + dcpu->memory[dcpu->PC++]] = res; break;
		case 0x13: dcpu->memory[dcpu->X + dcpu->memory[dcpu->PC++]] = res; break;
		case 0x14: dcpu->memory[dcpu->Y + dcpu->memory[dcpu->PC++]] = res; break;
		case 0x15: dcpu->memory[dcpu->Z + dcpu->memory[dcpu->PC++]] = res; break;
		case 0x16: dcpu->memory[dcpu->I + dcpu->memory[dcpu->PC++]] = res; break;
		case 0x17: dcpu->memory[dcpu->J + dcpu->memory[dcpu->PC++]] = res; break;

		/* PUSH */
	    case 0x18: dcpu->memory[--dcpu->SP] = res; break;

		/* PEEK */
		case 0x19: dcpu->memory[dcpu->SP] = res; break;

		/* PICK */
		case 0x1a: dcpu->memory[dcpu->SP + dcpu->memory[dcpu->PC++]] = res; break;
		
		/* SP, PC, EX */
		case 0x1b: dcpu->SP = res;  break;
		case 0x1c: dcpu->PC = res;  break;
		case 0x1d: dcpu->EX = res;  break;

		/* [next word] */
		case 0x1e: dcpu->memory[dcpu->memory[dcpu->PC++]] = res;  break;

		/* next word */
		case 0x1f: dcpu->memory[dcpu->PC++] = res;  break;

		/* literal value */
		default: break;
	}
	/* NOT REACHED */
}

dcpu_reg_t get( dcpu16_t *dcpu, dcpu_reg_t val, int type )
{
	switch(val)
	{
		// register
		case 0x00: return dcpu->A; 
		case 0x01: return dcpu->B; 
		case 0x02: return dcpu->C; 
		case 0x03: return dcpu->X; 
		case 0x04: return dcpu->Y; 
		case 0x05: return dcpu->Z; 
		case 0x06: return dcpu->I; 
		case 0x07: return dcpu->J; 

		// [register]
		case 0x08: return dcpu->memory[dcpu->A]; 
		case 0x09: return dcpu->memory[dcpu->B]; 
		case 0x0a: return dcpu->memory[dcpu->C]; 
		case 0x0b: return dcpu->memory[dcpu->X]; 
		case 0x0c: return dcpu->memory[dcpu->Y]; 
		case 0x0d: return dcpu->memory[dcpu->Z]; 
		case 0x0e: return dcpu->memory[dcpu->I]; 
		case 0x0f: return dcpu->memory[dcpu->J]; 

		// [register+next_word]
		case 0x10: return dcpu->memory[dcpu->A + dcpu->memory[dcpu->PC++]]; 
		case 0x11: return dcpu->memory[dcpu->B + dcpu->memory[dcpu->PC++]]; 
		case 0x12: return dcpu->memory[dcpu->C + dcpu->memory[dcpu->PC++]]; 
		case 0x13: return dcpu->memory[dcpu->X + dcpu->memory[dcpu->PC++]]; 
		case 0x14: return dcpu->memory[dcpu->Y + dcpu->memory[dcpu->PC++]]; 
		case 0x15: return dcpu->memory[dcpu->Z + dcpu->memory[dcpu->PC++]]; 
		case 0x16: return dcpu->memory[dcpu->I + dcpu->memory[dcpu->PC++]]; 
		case 0x17: return dcpu->memory[dcpu->J + dcpu->memory[dcpu->PC++]]; 

		/* POP/PUSH */
	    case 0x18:
			if( type == A_TYPE )
				return dcpu->memory[dcpu->SP++];
			else
				return dcpu->memory[--dcpu->SP];

		/* PEEK */
		case 0x19: return dcpu->memory[dcpu->SP];

		/* PICK */
		case 0x1a: return dcpu->memory[dcpu->SP + dcpu->memory[dcpu->PC++]];
		
		/* SP, PC, EX */
		case 0x1b: return dcpu->SP; 
		case 0x1c: return dcpu->PC; 
		case 0x1d: return dcpu->EX; 

		/* [next word] */
		case 0x1e: return dcpu->memory[dcpu->memory[dcpu->PC++]]; 

		/* next word */
		case 0x1f: return dcpu->memory[dcpu->PC++]; 

		/* literal value */
		default: return val - 0x21;
	}
	/* NOT REACHED */
}
dcpu_reg_t get_a( dcpu16_t *dcpu, dcpu_reg_t val )
{
	return get( dcpu, val, A_TYPE );
}

dcpu_reg_t get_b( dcpu16_t *dcpu, dcpu_reg_t val )
{
	return get( dcpu, val, B_TYPE );
}


/*
 * Perform the next opcode
 */
int dcpu_do_inst( dcpu16_t *dcpu )
{
	dcpu_inst_t inst;
	inst.all = dcpu->memory[dcpu->PC++];

	fprintf( stdout, "Got opcode a=%x, b=%x, o=%x\n", inst.a, inst.b, inst.o);
	return dcpu_ops[inst.o]( dcpu, inst );
}

int dcpu_special( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	// PC was advanced previously
	return dcpu_special_ops[inst.b]( dcpu, inst );
}

/*
 * operations 
 */

int dcpu_set( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	set( dcpu, inst.b, get_a( dcpu, inst.a ) );
	return 1;
}

int dcpu_add( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b + a);
	return 2;
}
int dcpu_sub( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b - a);
	return 2;
}
int dcpu_mul( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b * a);
	return 2;
}
int dcpu_mli( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_sign_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b * a);
	return 2;
}
int dcpu_div( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b / a);
	return 3;
}
int dcpu_dvi( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_sign_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b / a);
	return 3;
}
int dcpu_mod( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b % a);
	return 3;
}
int dcpu_and( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b & a);
	return 1;
}
int dcpu_bor( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b | a);
	return 1;
}
int dcpu_xor( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b ^ a);
	return 1;
}
int dcpu_shr( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b >> a);
	return 2;
}
int dcpu_asr( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_sign_t b;
	dcpu_reg_t a;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b >> a);
	return 2;
}
int dcpu_shl( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	set( dcpu, inst.b, b << a);
	return 2;
}
int dcpu_ifb( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	if( b & a == 0 ) dcpu->state = SKIPPING;
	return 2;
}
int dcpu_ifc( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	if( b & a != 0 ) dcpu->state = SKIPPING;
	return 2;
}
int dcpu_ife( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	if( b != a ) dcpu->state = SKIPPING;
	return 2;
}
int dcpu_ifn( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	if( b == a ) dcpu->state = SKIPPING;
	return 2;
}
int dcpu_ifg( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	if( b <= a ) dcpu->state = SKIPPING;
	return 2;
}
int dcpu_ifa( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_sign_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	if( b <= a ) dcpu->state = SKIPPING;
	return 2;
}
int dcpu_ifl( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	if( b >= a ) dcpu->state = SKIPPING;
	return 2;
}
int dcpu_ifu( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu_reg_sign_t a, b;
	a = get_a( dcpu, inst.a );
	b = get_b( dcpu, inst.b );
	if( b >= a ) dcpu->state = SKIPPING;
	return 2;
}

int dcpu_jsr( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	dcpu->memory[--dcpu->SP] = dcpu->PC;
	dcpu->PC = get_a( dcpu, inst.a );
	return 3;
}
int dcpu_int( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	// TODO
	return 4;
}
int dcpu_ing( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	// TODO
	return 1;
}
int dcpu_ins( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	// TODO
	return 1;
}

int dcpu_hwn( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	// TODO
	return 2;
}
int dcpu_hwq( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	// TODO
	return 4;
}
int dcpu_hwi( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	// TODO
	return 4;
}

int dcpu_inval( dcpu16_t *dcpu, dcpu_inst_t inst )
{
	fprintf(stderr, "Invalid opcode %#x\n", inst);
	return 0;
}

