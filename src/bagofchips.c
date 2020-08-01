/*
  Main file for bag-of-chips CHIP-8 emulator
*/

#incude <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "opcodes.h"

#define MEMORY 4096
#define WIDTH 64
#define HEIGHT 32
fd
char buf[MEMORY];

uint8_t v0 = 0x00;
uint8_t v1 = 0x00;
uint8_t v2 = 0x00;
uint8_t v3 = 0x00;
uint8_t v4 = 0x00;
uint8_t v5 = 0x00;
uint8_t v6 = 0x00;
uint8_t v7 = 0x00;
uint8_t v8 = 0x00;
uint8_t v9 = 0x00;
uint8_t vA = 0x00;
uint8_t vB = 0x00;
uint8_t vC = 0x00;
uint8_t vD = 0x00;
uint8_t vE = 0x00;
uint8_t vF = 0x00;


int main (int argc, char** argv){
    printf("Imagine this emulator is running\n\n");

    uint16_t opcode = (uint16_t) strtol(argv[1], NULL, 16);
    
    if (argc < 2)
	printf("No opcode provided as an argument\n");
    else {
	printf("Opcode: ");
	check_opcode(opcode);
    }
    printf("\n");

    return 0;
}
