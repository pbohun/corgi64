#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "cpu.h"

void test_hlt(cpu *c) {
    c->running = true;
    hlt(c);
    assert(c->running == false);
    cpu_print_status(c);
}

void test_add(cpu *c) {
    c->a = 3;
    c->b = 4;
    add(c);
    assert(c->a == 7);
    cpu_print_status(c);
}

void test_sub(cpu *c) {
    c->a = 7;
    c->b = 4;
    sub(c);
    assert(c->a == 3);
    cpu_print_status(c);
}

void test_mul(cpu *c) {
    c->a = 3;
    c->b = 4;
    mul(c);
    assert(c->a == 12);
    cpu_print_status(c);
}

void test_div(cpu *c) {
    c->a = 12;
    c->b = 4;
    div(c);
    assert(c->a == 3);
    cpu_print_status(c);
}

void test_mod(cpu *c) {
    c->a = 3;
    c->b = 4;
    mod(c);
    assert(c->a == 3);
    cpu_print_status(c);
}

void test_sia(cpu *c) {
    c->instr->value = 3;
    sia(c);
    assert(c->a == 3);
    cpu_print_status(c);
}

void test_sib(cpu *c) {
    c->instr->value = 4;
    sib(c);
    assert(c->b == 4);
    cpu_print_status(c);
}

void test_sic(cpu *c) {
    c->instr->value = 5;
    sic(c);
    assert(c->c == 5);
    cpu_print_status(c);
}

// test for loading values from memory 
void test_lda(cpu *c) {
    c->mem[0] = 1;
    c->mem[1] = 1;
    c->instr->value = 0;
    lda(c);
    assert(c->a == 257);
    cpu_print_status(c);
}

void test_ldb(cpu *c) {
    c->mem[0] = 2;
    c->mem[1] = 1;
    c->instr->value = 0;
    ldb(c);
    assert(c->b == 258);
    cpu_print_status(c);
}

void test_ldc(cpu *c) {
    c->mem[0] = 3;
    c->mem[1] = 1;
    c->instr->value = 0;
    ldc(c);
    assert(c->c == 259);
    cpu_print_status(c);
}

int main() {
    cpu *c = (cpu*)malloc(sizeof(cpu));
    cpu_init(c);
    byte memory[32] = {0};
    c->mem = memory;
    // misc tests 
    test_hlt(c);
    // test arithmetic
    test_add(c);
    test_sub(c);
    test_mul(c);
    test_div(c);
    test_mod(c);
    // test immediate values 
    test_sia(c);
    test_sib(c);
    test_sic(c);
    // test load memory opcodes
    test_lda(c);
    test_ldb(c);
    test_ldc(c);

    printf("all test passed");

    return 0;
}