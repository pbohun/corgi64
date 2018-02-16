#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "cpu.h"

void stackdump(cpu *c){
    printf("registers\n\tA %lld\n\tB %lld\n\tC %lld",(int64_t)c->a,(int64_t)c->b,(int64_t)c->c);
}

int main() {
    cpu *c = (cpu*)malloc(sizeof(cpu));
    cpu_init(c);
    std::vector<byte> memory_vec{0x01, 0, 0, 0, 0, 0, 0, 0, 3, 0x02, 0, 0, 0, 0, 0, 0, 0, 4, 0x16, 0x2E};
    c->mem = (byte*)malloc(memory_vec.size()*sizeof(byte));
    std::copy(memory_vec.begin(),memory_vec.end(),c->mem);

    run(c);

    stackdump(c);

    return 0;
}
