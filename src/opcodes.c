/*
  File for opcode parsing

  Note: for now it only consists of prints, also I don't know if the opcode itself its going to be a string
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int check_opcode(char* opcode){
	//uint16_t op = strtol(opcode,NULL,16);
	
	if(strlen(opcode) < 4){
		printf("no opcode at all\n"); return 1;		
	}
	
	switch(opcode[0]){
	case '0':
		switch(opcode[1]){
		case '0':
			switch(opcode[2]){
			case '1':
				printf("EXIT %c\n",opcode[3]); return 0;
			case 'B':
				printf("(SCHIP-8) SCU %c\n",opcode[3]); return 0;
			case 'C':
				printf("(SCHIP-8) SCD %c\n",opcode[3]); return 0;
			case 'E':
				switch(opcode[3]){
				case '0':
					printf("CLS\n"); return 0;
				case 'E':
					printf("RET\n"); return 0;
				default:
					printf("CALL %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
				}
			case 'F':
				switch(opcode[3]){
				case 'A':
					printf("COMPAT\n"); return 0;
				case 'B':
					printf("(SCHIP-8) SCR\n"); return 0;					
				case 'C':
					printf("(SCHIP-8) SCL\n"); return 0;
				case 'D':
					printf("(SCHIP-8) EXIT\n"); return 0;										
				case 'E':
					printf("(SCHIP-8) LOW\n"); return 0;
				case 'F':
					printf("(SCHIP-8) HIGH\n"); return 0;
				default:
					printf("CALL %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
				}
			default:
				printf("CALL %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
			}
		case '2':
			switch(opcode[2]){
			case 'A':
				switch(opcode[3]){
				case '0':
					printf("(CHIP-8X) STEPCOL\n"); return 0;
				default:
					printf("CALL %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
				}
			default:
				printf("CALL %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
			}
		default:
			printf("CALL %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
		}			
	case '1':
		printf("JMP %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
	case '2':
		printf("CALL %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
	case '3':
		printf("SE V%c, %c%c\n",opcode[1],opcode[2],opcode[3]); return 0;	   
	case '4':
		printf("SNE V%c, %c%c\n",opcode[1],opcode[2],opcode[3]); return 0;		
	case '5':
		switch(opcode[3]){
		case '0':
			printf("SE V%c V%c\n",opcode[1],opcode[2]); return 0;
		case '1':
			printf("SGT V%c V%c\n",opcode[1],opcode[2]); return 0;
			printf("(CHIP-8X) ADD V%c V%c\n",opcode[1],opcode[2]); return 0;
		case '2':
			printf("SLT V%c V%c\n",opcode[1],opcode[2]); return 0;
		case '3':
			printf("SNE V%c V%c\n",opcode[1],opcode[2]); return 0;		
		}
	case '6':
		printf("LD V%c, %c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
	case '7':
		printf("ADD V%c, %c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
	case '8':
		switch(opcode[3]){
		case '0':
			printf("LD V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '1':
			printf("OR V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '2':
			printf("AND V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '3':
			printf("XOR V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '4':
			printf("ADD V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '5':
			printf("SUB V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '6':
			printf("SHR V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '7':
			printf("SUBN V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case 'E':
			printf("SHL V%c, V%c\n",opcode[1],opcode[2]); return 0;
		}
	case '9':
				switch(opcode[3]){
		case '0':
			printf("SNE V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '1':
			printf("(CHIP-8E) MUL V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '2':
			printf("(CHIP-8E) DIV V%c, V%c\n",opcode[1],opcode[2]); return 0;
		case '3':
			printf("(CHIP-8E) BCD V%c, V%c\n",opcode[1],opcode[2]); return 0;
		}
	case 'A':
		printf("LD I, %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
	case 'B':
		switch(opcode[1]){
		case '0':
			printf("(CHIP-8I) OUT %c%c\n",opcode[2],opcode[3]); return 0;
		case '1':
			switch(opcode[3]){
			case '0':
				printf("(CHIP-8I) OUT V%c\n",opcode[2]); return 0;
			case '1':
				printf("(CHIP-8I) IN V%c\n",opcode[2]); return 0;
			}
		}
		switch(opcode[3]){
		case '0':
			printf("(CHIP-8X) COL V%c, V%c\n",opcode[1],opcode[2]); return 0;
		default:
			printf("(CHIP-8X) COL V%c, V%c, %c\n",opcode[1],opcode[2],opcode[3]); return 0;
		}
		printf("JMP V0, %c%c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
	case 'C':
		printf("RND V%c, %c%c\n",opcode[1],opcode[2],opcode[3]); return 0;
	case 'D':
		switch(opcode[3]){
		case '0':
			printf("(SCHIP-8) DRW V%c, V%c, 0\n",opcode[1],opcode[2]); return 0;
		default:
			printf("DRW V%c, V%c, %c\n",opcode[1],opcode[2],opcode[3]); return 0;
		}
	case 'E':
		switch(opcode[2]){
		case '9':
			printf("SKP V%c\n",opcode[1]); return 0;
		case 'A':
			printf("SKNP V%c\n",opcode[1]); return 0;
		case 'F':
			switch(opcode[3]){
			case '2':
				printf("(CHIP-8X) SKP2 V%c\n",opcode[1]); return 0;
			case '5':
				printf("(CHIP-8X) SKNP2 V%c\n",opcode[1]); return 0;
			}
		}
	case 'F':
		switch(opcode[2]){
		case '0':
			switch(opcode[3]){
			case '7':
				printf("LD V%c, DT\n",opcode[1]); return 0;
			case 'A':
				printf("LD V%c, KEY\n",opcode[1]); return 0;
			}
		case '1':
			switch(opcode[3]){
			case '5':
				printf("LD DT, V%c\n",opcode[1]); return 0;
			case '8':
				printf("LD ST, V%c\n",opcode[1]); return 0;
			case 'E':
				printf("ADD I, V%c\n",opcode[1]); return 0;
			}
		case '2':
			printf("LD I, FONT(V%c)\n",opcode[1]); return 0;
		case '3':
			switch(opcode[3]){
			case '0':
				printf("(SCHIP-8) LD I, FONT(V%c)\n",opcode[1]); return 0;
			case '3':
				printf("BCD V%c\n",opcode[1]); return 0;
			}			
		case '5':
			printf("LD V%c, [I]\n",opcode[1]); return 0;
		case '6':
			printf("LD [I], V%c\n",opcode[1]); return 0;
		case '7':
			printf("(CHIP-8E) DISP V%c\n",opcode[1]); return 0;
			printf("(SCHIP-8) LD R, V%c\n",opcode[1]); return 0;
		case '8':
			printf("(SCHIP-8) LD V%c, R\n",opcode[1]); return 0;
		case '9':
			printf("(CHIP-8E) LD I, V%c\n",opcode[1]); return 0;
		case 'F':
			switch(opcode[3]){
			case '8':
				printf("(CHIP-8X) OUT V%c\n",opcode[1]); return 0;
			case 'B':
				printf("(CHIP-8X) IN V%c\n",opcode[1]); return 0;
			}
		}
	}
	return 1;
}
