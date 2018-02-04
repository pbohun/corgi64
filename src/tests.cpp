#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "cpu.h"

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

int main() {
    cpu *c = (cpu*)malloc(sizeof(cpu));
    reset(c);

    test_add(c);
    test_sub(c);
    test_mul(c);
    test_div(c);
    test_mod(c);

    printf("all test passed");

    return 0;
}