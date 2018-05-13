/*
Copyright (C) 2018 Philip Bohun

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "cpu.h"

void test_get_flag_value(cpu *c) {
    reset(c);
    c->flags = 2;
    i64 value = get_flag_value(c, 1);
    assert(1 == value);
    cpu_print_status(c);
}

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

void test_zero_flag(cpu *c) {
    reset(c);
    c->a = 0;
    c->b = 0;
    sub(c);
    assert(c->flags == 1);
    cpu_print_status(c);
}

void test_negative_flag(cpu *c) {
    reset(c);
    c->a = 0;
    c->b = 1;
    sub(c);
    assert(c->flags == 2);
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

void test_sta(cpu *c) {
    c->a = 128;
    c->instr->value = 16;
    sta(c);
    assert(128 == *(i64*)(c->mem + 16));
    cpu_print_status(c);
}

void test_stb(cpu *c) {
    c->b = 512;
    c->instr->value = 16;
    stb(c);
    assert(512 == *(i64*)(c->mem + 16));
    cpu_print_status(c);
}

void test_stc(cpu *c) {
    c->c = 1024;
    c->instr->value = 16;
    stc(c);
    assert(1024 == *(i64*)(c->mem + 16));
    cpu_print_status(c);
}

// tests for branching
void test_jmp(cpu *c) {
    reset(c);
    c->instr->value = 30;
    c->pc = 1;
    jmp(c);
    assert(30 == c->instr->value);
    cpu_print_status(c);
}

void test_beq(cpu *c) {
    reset(c);
    c->instr->value = 10;
    c->flags = 1;
    c->pc = 5;
    beq(c);
    assert(10 == c->pc);
    cpu_print_status(c);
}

int main() {
    cpu *c = (cpu*)malloc(sizeof(cpu));
    cpu_init(c);
    byte memory[32] = {0};
    c->mem = memory;
    // test get flag value
    test_get_flag_value(c);
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
    test_sta(c);
    test_stb(c);
    test_stc(c);
    // test flags 
    test_zero_flag(c);
    test_negative_flag(c);
    // test jump opcodes
    test_jmp(c);
    test_beq(c);
    printf("all test passed");

    return 0;
}