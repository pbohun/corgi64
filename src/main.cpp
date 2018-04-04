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
