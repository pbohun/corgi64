#include <cstdint>

#define local static

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

local void nop(cpu *c) {}

local void hlt(cpu *c) {
    c->running = false;
}

// NOTE (phil): remember to set flags after doing arithmetic
local void add(cpu *c) {
    c->a = c->a + c->b;
}

local void sub(cpu *c) {
    c->a = c->a - c->b;
}

local void mul(cpu *c) {
    c->a = c->a * c->b;
}

local void div(cpu *c) {
    c->a = c->a / c->b;
}

local void mod(cpu *c) {
    c->a = c->a % c->b;
}

// register opcodes
local void sia(cpu *c) {
    c->a = c->instr->value;
    // skip immediate value
    c->pc+=4;
}

local void sib(cpu *c) {
    c->b = c->instr->value;
    // skip immediate value
    c->pc+=4;
}

local void sic(cpu *c) {
    c->c = c->instr->value;
    // skip immediate value
    c->pc+=4;
}

// table of opcodes
local void (*optable[256])(cpu*) = {
/*      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |      */
/* 0 */  nop,sia,sib,sic,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 0 */
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

void cpu_init(cpu *c) {
    c->a = 0;
    c->b = 0;
    c->pc = 0;
    c->sp = 0;
    c->flags = 0;
    c->mem = NULL;
    c->instr = (instruction*)malloc(sizeof(instruction));
}

void reset(cpu *c) {
    c->a = 0;
    c->b = 0;
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
        c->instr = (instruction*)(c->mem + c->pc);
        // increment the program counter
        c->pc++;
        // execute
        optable[c->instr->opcode](c);
    }
}