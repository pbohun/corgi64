/*
Copyright (C) 2018 Philip Bohun

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
#include <cstdint>

using byte = uint8_t;
using i64 = int64_t;

struct instruction {
    byte opcode;
    i64 value;
};

struct cpu {
    i64 a, b, c, pc, sp, flags;
    instruction *instr;
    bool running;
    byte *mem;
};

void cpu_fetch(cpu *c) {
    c->instr->opcode = *(c->mem + c->pc);
    c->instr->value = *(i64*)(c->mem + c->pc + 1);
}

void cpu_print_status(cpu *c) {
    printf("a: %lld\nb: %lld\nc: %lld\npc: %lld\nsp: %lld\nflags: %lld\n",
        c->a, c->b, c->c, c->pc, c->sp, c->flags);
}

void nop(cpu *c) {}

void hlt(cpu *c) {
    c->running = false;
}

// TODO: (phil) change name to have underscores
void setArithmeticFlag(cpu *c) {
    if (c->a == 0) {
        c->flags |= 1;
    } else if (c->a < 0) {
        c->flags |= 2;
    } else if (c->a > 0) {
        c->flags &= ~2;
    }
}

void add(cpu *c) {
    c->a = c->a + c->b;
    setArithmeticFlag(c);
}

void sub(cpu *c) {
    c->a = c->a - c->b;
    setArithmeticFlag(c);
}

void mul(cpu *c) {
    c->a = c->a * c->b;
    setArithmeticFlag(c);
}

void div(cpu *c) {
    c->a = c->a / c->b;
    setArithmeticFlag(c);
}

void mod(cpu *c) {
    c->a = c->a % c->b;
    setArithmeticFlag(c);
}

// register opcodes
void sia(cpu *c) {
    c->a = c->instr->value;
}

void sib(cpu *c) {
    c->b = c->instr->value;
}

void sic(cpu *c) {
    c->c = c->instr->value;
}

// memory opcodes
void lda(cpu *c) {
    c->a = *(i64*)(c->mem + c->instr->value);
}

void ldb(cpu *c) {
    c->b = *(i64*)(c->mem + c->instr->value);
}

void ldc(cpu *c) {
    c->c = *(i64*)(c->mem + c->instr->value);
}

void sta(cpu *c) {
    *(i64*)(c->mem + c->instr->value) = c->a;
}

void stb(cpu *c) {
    *(i64*)(c->mem + c->instr->value) = c->b;
}

void stc(cpu *c) {
    *(i64*)(c->mem + c->instr->value) = c->c;
}

// table of opcodes
void (*optable[256])(cpu*) = {
/*      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |      */
/* 0 */  nop,sia,sib,sic,lda,ldb,ldc,sta,stb,stc,nop,nop,nop,nop,nop,nop, /* 0 */
/* 1 */  nop,nop,nop,nop,nop,nop,add,sub,mul,div,mod,nop,nop,nop,nop,nop, /* 1 */
/* 2 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,hlt,nop, /* 2 */
/* 3 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 3 */
/* 4 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 4 */
/* 5 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 5 */
/* 6 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 6 */
/* 7 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 7 */
/* 8 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 8 */
/* 9 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 9 */
/* A */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* A */
/* B */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* B */
/* C */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* C */
/* D */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* D */
/* E */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* E */
/* F */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* F */
};

// table of memory offsets
i64 offset_table[256] = {
/*      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |      */
/* 0 */    1,  9,  9,  9,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 0 */
/* 1 */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 1 */
/* 2 */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 2 */
/* 3 */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 3 */
/* 4 */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 4 */
/* 5 */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 5 */
/* 6 */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 6 */
/* 7 */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 7 */
/* 8 */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 8 */
/* 9 */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 9 */
/* A */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* A */
/* B */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* B */
/* C */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* C */
/* D */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* D */
/* E */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* E */
/* F */    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* F */
};

void cpu_init(cpu *c) {
    c->a = 0;
    c->b = 0;
    c->c = 0;
    c->pc = 0;
    c->sp = 0;
    c->flags = 0;
    c->mem = NULL;
    c->instr = (instruction*)malloc(sizeof(instruction));
}

void reset(cpu *c) {
    c->a = 0;
    c->b = 0;
    c->c = 0;
    c->pc = 0;
    c->sp = 0;
    c->flags = 0;
    if (c->instr == NULL) {
        c->instr = (instruction*)malloc(sizeof(instruction));
    }
}

void run(cpu *c) {
    c->running = true;
    while(c->running) {
        // fetch and decode
        cpu_fetch(c);
        // increment the program counter
        c->pc += offset_table[c->instr->opcode];
        // execute
        optable[c->instr->opcode](c);
    }
}