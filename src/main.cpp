#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "cpu.h"

int main() {
    cpu *c = (cpu*)malloc(sizeof(cpu));
    cpu_init(c);
    byte memory[] = {
        0x01,   // sia
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02,   // sib
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x16,   // add
        0x2E    // hlt
    };
    c->mem = memory;

    run(c);

    cpu_print_status(c);

    return 0;
}
