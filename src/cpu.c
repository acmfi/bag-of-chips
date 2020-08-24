#include "display.h"
#include "stack.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 4096
#define WIDTH 64
#define HEIGHT 32

#define VX regs[op_nibbles.X]
#define VY regs[op_nibbles.Y]
#define VF regs[15]

Stack *stack;

uint8_t mem[MEM_SIZE];
uint16_t PC = 0x200;

// General purpouse registers
uint8_t regs[16];

// mem address register
uint8_t I = 0x00;

// two kinds of timer . both work at 60Hz
uint8_t delay_timer = 0;
uint8_t sound_timer = 0;

// error managing variable
int *error;

struct nibbles {
  uint8_t I : 4;     // instruction type first 4 bits
  uint8_t X : 4;     // second nibble
  uint8_t Y : 4;     // third nibble
  uint8_t N : 4;     // fourth nibble
  uint8_t NN : 8;    // last byte / 2 nibbles
  uint16_t NNN : 12; // last 12 bits / 3 nibbles
};

uint8_t lo(uint16_t address) { return (uint8_t)address; }
uint8_t hi(uint16_t address) { return (uint8_t)(address >> 8); }

uint16_t fetch() {
  uint16_t opcode = (uint16_t)mem[PC] << 8 | mem[PC + 1];
  PC += 2;
  return opcode;
}

struct nibbles decode(uint16_t opcode) {
  struct nibbles op_nibbles;
  op_nibbles.I = (0xF000 & opcode) >> 12;
  op_nibbles.X = (0x0F00 & opcode) >> 8;
  op_nibbles.Y = (0x00F0 & opcode) >> 4;
  op_nibbles.N = (0x000F & opcode);
  op_nibbles.NN = (0x00FF & opcode);
  op_nibbles.NNN = (0x0FFF & opcode);
  return op_nibbles;
}

int execute(uint16_t instr) {
  struct nibbles op_nibbles = decode(instr);

  switch (op_nibbles.I) {
  case 0x0: // special functions
    if (op_nibbles.X == 0) {
      if (op_nibbles.NN == 0xE0) {
        // CLEAR SCREEN
      } else if (op_nibbles.NN == 0xEE) {
        // return
        PC = pop(stack, error);
        if (error) {
          perror("invalid return value");
          exit(1);
        }
      }
    } else {
      // 0x0NNN : CALL NNN
      push(stack, PC, error);
      PC = op_nibbles.NNN;
      if (error) {
        perror("StackOverflow :3");
        exit(1);
      }
    }
    break;
  case 0x1: // inconditional jump
    PC = op_nibbles.NNN;
    break;
  case 0x2: // call subroutine
    // push PC+1
    PC = op_nibbles.NNN;
    break;
  case 0x3: // jeq reg-n
    PC += VX == op_nibbles.NN;
    break;
  case 0x4: // jne reg-n
    PC += VX != op_nibbles.NN;
    break;
  case 0x5: // jeq reg-reg
    PC += VX == op_nibbles.Y;
    break;
  case 0x6: // Vx = NN
    VX = op_nibbles.NN;
    break;
  case 0x7: // Vx += NN
    VX += op_nibbles.NN;
    break;
  case 0x8: // logic operations and assignment
    switch (op_nibbles.N) {
    case 0x0: // Vx=Vy
      VX = VY;
      break;
    case 0x1: // Vx=Vx|Vy
      VX = VX | VY;
      break;
    case 0x2: // Vx=Vx&Vy
      VX = VX & VY;
      break;
    case 0x3: // Vx=Vx^Vy
      VX = VX ^ VY;
      break;
    case 0x4: // VX += VY
      VX += VY;
      break;
    case 0x5: // VX -= VY
      VX -= VY;
      break;
    case 0x6:
      VF = VX & 0x1;
      VX >>= 1;
      break;
    }
    break;
  case 0x9: // jne reg-reg
    PC += VX != op_nibbles.Y && !op_nibbles.N;
    break;
  case 0xA: // Sets I to the address NNN.
    I = op_nibbles.NNN;
    break;
  case 0xB: // Jumps to the address NNN plus V0.
    PC = regs[0] + op_nibbles.NNN;
    break;
  case 0xC: // VX = rand() &NN
    VX = rand() & op_nibbles.NN;
    break;
  case 0xD: // draw(Vx,Vy,N)
    draw(VX, VY, op_nibbles.N);
    break;
  case 0xE: // check keypresses
    if (op_nibbles.NN == 0x9E)
    {
      // key X is pressed
      PC += key() == VX;
    }
    else if (op_nibbles.NN == 0xA1)
    {
      // key X not pressed
      PC += key() != VX;
    }
    break;
  case 0xF: // memory, timers, sprites
    switch (op_nibbles.NN)
    {
    case 0x07:
      // get dalay
      VX = delay_timer;
      break;
    case 0x0A:
      // get key
      VX = get_key();
      break;
    case 0x15:
      // set delay
      delay_timer = VX;
      break;
    case 0x18:
      sound_timer = VX;
      break;
    case 0x1E:
      I += VX;
      break;
    case 0x29:
      I = sprite(VX);
      break;
    case 0x33:
      mem[I] = VX / 100;
      mem[I + 1] = (VX % 100) / 10;
      mem[I + 2] = (VX % 100) % 10;
      break;
    case 0x55: // dump registers
      for (int i = 0; i < op_nibbles.X; i++)
      {
        mem[I + i] = regs[i];
      }
      break;
    case 0x65: // load registers
      for (int i = 0; i < op_nibbles.X; i++)
      {
        regs[i] = mem[I + i];
      }
      break;
    }
    break;
  }
  return 0;
}

int loadFont(char *fontFile) {
  FILE *font = fopen(fontFile, "r");
  uint8_t val;
  int elems = -1;
  fscanf(font, "%d", val);
  while (val != EOF && elems < 0x201) {
    mem[++elems] = val;
    fscanf(font, "%d", val);
  }
}

int main(int argc, char *argv)
{
  loadFont("font");
  stack = create_stack(16);
  while (1)
  {
    uint16_t instr = fetch();
    execute(instr);
  }
  free_stack(stack);
}
