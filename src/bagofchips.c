/*
  Main file for bag-of-chips CHIP-8 emulator
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "opcodes.h"

#define MEMORY 4096
#define WIDTH 64
#define HEIGHT 32

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
	printf("imagine this emulator is running\n\n");

	printf("Opcode: ");
	if(argc < 2) printf("no opcode at all\n");
	else check_opcode(argv[1]);
	printf("\n");

	int i = 0;
	for (;i<10;i++) printf("VIDEO\tGAMES\n");
	return 0;
}
