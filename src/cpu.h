/*
Copyright (C) 2018 Philip Bohun

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
#include <stdint.h>

#define DEST_MASK 0x00FF000000000000
#define ADDR_MASK 0x0000FFFFFFFFFFFF
#define byte uint8_t
#define i64 int64_t

enum OPS {
	LDI, LD, ST, ADD, SUB, MUL, DIV, MOD, JMP, JRO, HLT
};

char *op_strings[] = {
	"LDI", "LD", "ST", "ADD", "SUB", "MUL", "DIV", "MOD", "JMP", "JRO", "HLT"
};

// instruction 64 bits total
// 8 bits : opcode
// 8 bits : destination register
// 48 bits : source register / immediate value

typedef struct {
	i64 reg[8];
    i64 pc, sp, flags;
    bool running;
    byte *mem;
} Cpu;

Cpu *new_cpu() {
	Cpu *c = (Cpu*)malloc(sizeof(Cpu));
	c->mem = (byte*)malloc(sizeof(byte) * 8000);
	c->pc = 0;
	c->sp = 8000;
	c->flags = 0;
	return c;
}

void run(Cpu *c) {
    c->running = true;
    while(c->running) {
		i64 *mem = (i64*)c->mem;
		i64 instr = mem[c->pc];
		i64 op = (uint64_t)instr >> 56;
		i64 dst = (instr & DEST_MASK) >> 48;
		i64 src = instr & ADDR_MASK;

		printf("op:%s, dst:%I64d, src:%I64d\n", op_strings[op], dst, src);

		switch (op) {
		case LDI:
			c->reg[dst] = src;
			break;
		case LD:
			if (src < 8) {
				c->reg[dst] = mem[c->reg[src]];
			} else {
				c->reg[dst] = mem[src];
			}
			break;
		case ST:
			if (src < 8) {
				mem[c->reg[dst]] = c->reg[src];
			} else {
				mem[dst] = c->reg[src];
			}break;
		case ADD:
			c->reg[dst] += c->reg[src];
			break;
		case SUB:
			c->reg[dst] -= c->reg[src];
			break;
		case MUL:
			c->reg[dst] *= c->reg[src];
			break;
		case DIV:
			c->reg[dst] /= c->reg[src];
			break;
		case MOD:
			c->reg[dst] %= c->reg[src];
			break;
		case JMP:
			c->pc = src - 1;
			break;
		case JRO:
			c->pc += src;
			break;
		case HLT:
			c->running = false;
			break;
		default:
			printf("Unknown opcode:%I64d\n", op);
			exit(0);		
		}
		c->pc++;
    }
}
