#include <cstdint>

using byte = uint8_t;
using i64 = int64_t;

struct cpu {
    i64 a, b, c, pc, sp, flags;
    byte *mem;
};

static void nop(cpu *c) {}

// NOTE (phil): remember to set flags after doing arithmetic
static void add(cpu *c) {
    c->a = c->a + c->b;
}

static void sub(cpu *c) {
    c->a = c->a - c->b;
}

static void mul(cpu *c) {
    c->a = c->a * c->b;
}

static void div(cpu *c) {
    c->a = c->a / c->b;
}

static void mod(cpu *c) {
    c->a = c->a % c->b;
}

// table of opcodes
static void (*optable[256])(cpu*) = {
/*      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |      */
/* 0 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 0 */
/* 1 */  nop,nop,nop,nop,nop,nop,add,sub,mul,div,mod,nop,nop,nop,nop,nop, /* 1 */
/* 2 */  nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop,nop, /* 2 */
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

void reset(cpu *c) {
    c->a = 0;
    c->b = 0;
    c->pc = 0;
    c->sp = 0;
    c->flags = 0;
    c->mem = NULL;
}

void run(cpu *c) {

}