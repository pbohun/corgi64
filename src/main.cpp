#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "cpu.h"

int main() {
    cpu *c = (cpu*)malloc(sizeof(cpu));
    reset(c);

    return 0;
}
