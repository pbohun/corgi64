#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "cpu.h"

int main() {
    cpu *c = (cpu*)malloc(sizeof(cpu));
    cpu_init(c);
    std::vector<byte> memory_vec{0x01, 0, 0, 0, 0, 0, 0, 0, 3, 0x02, 0, 0, 0, 0, 0, 0, 0, 4, 0x16, 0x2E};
    c->mem = (byte*)malloc(memory_vec.size()*sizeof(byte));
    std::copy(memory_vec.begin(),memory_vec.end(),c->mem);

    run(c);

    printf("register a should be 7, and is: %lld", (int64_t)c->a);

    return 0;
}
