#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "cpu.h"

void test_hlt(cpu *c) {
    c->running = true;
    hlt(c);
    assert(c->running == false);
    printf("running is %d\n", c->running);
}

void test_add(cpu *c) {
    c->a = 3;
    c->b = 4;
    add(c);
    assert(c->a == 7);
    printf("3 + 4 is: %lld\n", (int64_t)c->a);
}

void test_sub(cpu *c) {
    c->a = 7;
    c->b = 4;
    sub(c);
    assert(c->a == 3);
    printf("7 - 4 is: %lld\n", (int64_t)c->a);
}

void test_mul(cpu *c) {
    c->a = 3;
    c->b = 4;
    mul(c);
    assert(c->a == 12);
    printf("3 * 4 is: %lld\n", (int64_t)c->a);
}

void test_div(cpu *c) {
    c->a = 12;
    c->b = 4;
    div(c);
    assert(c->a == 3);
    printf("12 / 4 is: %lld\n", (int64_t)c->a);
}

void test_mod(cpu *c) {
    c->a = 3;
    c->b = 4;
    mod(c);
    assert(c->a == 3);
    printf("3 mod 4 is: %lld\n", (int64_t)c->a);
}

void test_sia(cpu *c) {
    c->instr->value = 3;
    sia(c);
    assert(c->a == 3);
    printf("register a is %lld\n", (int64_t)c->a);
}

void test_sib(cpu *c) {
    c->instr->value = 4;
    sib(c);
    assert(c->b == 4);
    printf("register b is %lld\n", (int64_t)c->b);
}

void test_sic(cpu *c) {
    c->instr->value = 5;
    sic(c);
    assert(c->c == 5);
    printf("register c is %lld\n", (int64_t)c->c);
}

int main() {
    cpu *c = (cpu*)malloc(sizeof(cpu));
    cpu_init(c);
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

    printf("all test passed");

    return 0;
}