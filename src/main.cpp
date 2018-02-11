#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "cpu.h"

int main() {
    cpu *c = (cpu*)malloc(sizeof(cpu));
    cpu_init(c);
    byte *memory = {0x01, 3, 0x02, 4, 0x16, 0x2E};
    c->mem = memory;

    run(c);

    printf("register a should be 7, and is:", (int64_t)c->a);

    return 0;
}
