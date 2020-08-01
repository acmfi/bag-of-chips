/*
  File for opcode parsing

  Note: for now it only consists of prints, also I don't know if the opcode itself its going to be a string
*/

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int check_opcode(uint16_t opcode){
    unsigned char op_nibbles[4];

    op_nibbles[0] = (0xF000 & opcode) >> 12;
    op_nibbles[1] = (0x0F00 & opcode) >> 8;
    op_nibbles[2] = (0x00F0 & opcode) >> 4;
    op_nibbles[3] = (0x000F & opcode);

    switch(op_nibbles[0]){
    case 0x0:
	switch(op_nibbles[1]){
	case 0x0:
	    switch(op_nibbles[2]){
	    case 0x1:
		printf("EXIT %X\n",op_nibbles[3]); return 0;
	    case 0xB:
		printf("(SCHIP-8) SCU %X\n",op_nibbles[3]); return 0;
	    case 0xC:
		printf("(SCHIP-8) SCD %X\n",op_nibbles[3]); return 0;
	    case 0xE:
		switch(op_nibbles[3]){
		case 0x0:
		    printf("CLS\n"); return 0;
		case 0xE:
		    printf("RET\n"); return 0;
		default:
		    printf("CALL %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
		}
	    case 0xF:
		switch(op_nibbles[3]){
		case 0xA:
		    printf("COMPAT\n"); return 0;
		case 0xB:
		    printf("(SCHIP-8) SCR\n"); return 0;					
		case 0xC:
		    printf("(SCHIP-8) SCL\n"); return 0;
		case 0xD:
		    printf("(SCHIP-8) EXIT\n"); return 0;										
		case 0xE:
		    printf("(SCHIP-8) LOW\n"); return 0;
		case 0xF:
		    printf("(SCHIP-8) HIGH\n"); return 0;
		default:
		    printf("CALL %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
		}
	    default:
		printf("CALL %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
	    }
	case 0x2:
	    switch(op_nibbles[2]){
	    case 0xA:
		switch(op_nibbles[3]){
		case 0x0:
		    printf("(CHIP-8X) STEPCOL\n"); return 0;
		default:
		    printf("CALL %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
		}
	    default:
		printf("CALL %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
	    }
	default:
	    printf("CALL %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
	}			
    case 0x1:
	printf("JMP %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
    case 0x2:
	printf("CALL %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
    case 0x3:
	printf("SE V%X, %X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;	   
    case 0x4:
	printf("SNE V%X, %X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;		
    case 0x5:
	switch(op_nibbles[3]){
	case 0x0:
	    printf("SE V%X V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x1:
	    printf("SGT V%X V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	    printf("(CHIP-8X) ADD V%X V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x2:
	    printf("SLT V%X V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x3:
	    printf("SNE V%X V%X\n",op_nibbles[1],op_nibbles[2]); return 0;		
	}
    case 0x6:
	printf("LD V%X, %X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
    case 0x7:
	printf("ADD V%X, %X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
    case 0x8:
	switch(op_nibbles[3]){
	case 0x0:
	    printf("LD V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x1:
	    printf("OR V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x2:
	    printf("AND V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x3:
	    printf("XOR V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x4:
	    printf("ADD V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x5:
	    printf("SUB V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x6:
	    printf("SHR V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x7:
	    printf("SUBN V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0xE:
	    printf("SHL V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	}
    case 0x9:
	switch(op_nibbles[3]){
	case 0x0:
	    printf("SNE V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x1:
	    printf("(CHIP-8E) MUL V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x2:
	    printf("(CHIP-8E) DIV V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	case 0x3:
	    printf("(CHIP-8E) BCD V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	}
    case 0xA:
	printf("LD I, %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
    case 0xB:
	switch(op_nibbles[1]){
	case 0x0:
	    printf("(CHIP-8I) OUT %X%X\n",op_nibbles[2],op_nibbles[3]); return 0;
	case 0x1:
	    switch(op_nibbles[3]){
	    case 0x0:
		printf("(CHIP-8I) OUT V%X\n",op_nibbles[2]); return 0;
	    case 0x1:
		printf("(CHIP-8I) IN V%X\n",op_nibbles[2]); return 0;
	    }
	}
	switch(op_nibbles[3]){
	case 0x0:
	    printf("(CHIP-8X) COL V%X, V%X\n",op_nibbles[1],op_nibbles[2]); return 0;
	default:
	    printf("(CHIP-8X) COL V%X, V%X, %X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
	}
	printf("JMP V0, %X%X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
    case 0xC:
	printf("RND V%X, %X%X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
    case 0xD:
	switch(op_nibbles[3]){
	case 0x0:
	    printf("(SCHIP-8) DRW V%X, V%X, 0\n",op_nibbles[1],op_nibbles[2]); return 0;
	default:
	    printf("DRW V%X, V%X, %X\n",op_nibbles[1],op_nibbles[2],op_nibbles[3]); return 0;
	}
    case 0xE:
	switch(op_nibbles[2]){
	case 0x9:
	    printf("SKP V%X\n",op_nibbles[1]); return 0;
	case 0xA:
	    printf("SKNP V%X\n",op_nibbles[1]); return 0;
	case 0xF:
	    switch(op_nibbles[3]){
	    case 0x2:
		printf("(CHIP-8X) SKP2 V%X\n",op_nibbles[1]); return 0;
	    case 0x5:
		printf("(CHIP-8X) SKNP2 V%X\n",op_nibbles[1]); return 0;
	    }
	}
    case 0xF:
	switch(op_nibbles[2]){
	case 0x0:
	    switch(op_nibbles[3]){
	    case 0x7:
		printf("LD V%X, DT\n",op_nibbles[1]); return 0;
	    case 0xA:
		printf("LD V%X, KEY\n",op_nibbles[1]); return 0;
	    }
	case 0x1:
	    switch(op_nibbles[3]){
	    case 0x5:
		printf("LD DT, V%X\n",op_nibbles[1]); return 0;
	    case 0x8:
		printf("LD ST, V%X\n",op_nibbles[1]); return 0;
	    case 0xE:
		printf("ADD I, V%X\n",op_nibbles[1]); return 0;
	    }
	case 0x2:
	    printf("LD I, FONT(V%X)\n",op_nibbles[1]); return 0;
	case 0x3:
	    switch(op_nibbles[3]){
	    case 0x0:
		printf("(SCHIP-8) LD I, FONT(V%X)\n",op_nibbles[1]); return 0;
	    case 0x3:
		printf("BCD V%X\n",op_nibbles[1]); return 0;
	    }			
	case 0x5:
	    printf("LD V%X, [I]\n",op_nibbles[1]); return 0;
	case 0x6:
	    printf("LD [I], V%X\n",op_nibbles[1]); return 0;
	case 0x7:
	    printf("(CHIP-8E) DISP V%X\n",op_nibbles[1]); return 0;
	    printf("(SCHIP-8) LD R, V%X\n",op_nibbles[1]); return 0;
	case 0x8:
	    printf("(SCHIP-8) LD V%X, R\n",op_nibbles[1]); return 0;
	case 0x9:
	    printf("(CHIP-8E) LD I, V%X\n",op_nibbles[1]); return 0;
	case 0xF:
	    switch(op_nibbles[3]){
	    case 0x8:
		printf("(CHIP-8X) OUT V%X\n",op_nibbles[1]); return 0;
	    case 0xB:
		printf("(CHIP-8X) IN V%X\n",op_nibbles[1]); return 0;
	    }
	}
    }
    return 1;
}
