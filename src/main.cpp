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
i64 MakeInstruction(i64 op, i64 dst, i64 src) { 
	i64 instr = op << 56; 
	instr = instr | (dst << 48);
	instr = instr | (src & ADDR_MASK);
	return instr;
}

int main() {
	Cpu *c = new_cpu();
	i64 memory[] = {
		MakeInstruction(LDI, 0, 5),
		MakeInstruction(LDI, 1, 10),
		MakeInstruction(ST, 1, 0),
		MakeInstruction(LD, 2, 1),
		MakeInstruction(JMP, 0, 6),
		MakeInstruction(ADD, 1, 2),
		MakeInstruction(HLT, 0, 0)
	};
	/*
	i64 memory[] = {
		// load 3 and 4
		MakeInstruction(LDI, 0, 3),
		MakeInstruction(LDI, 1, 4),

		// add 3 and 4 
		MakeInstruction(ADD, 0, 1),

		// sub 5 from 7
		MakeInstruction(LDI, 2, 5),
		MakeInstruction(SUB, 0, 2),

		// mul 2 by 8
		MakeInstruction(LDI, 2, 8),
		MakeInstruction(MUL, 0, 2),

		// div 16 by 3
		MakeInstruction(LDI, 2, 3),
		MakeInstruction(DIV, 0, 2),

		// mod 5 2
		MakeInstruction(LDI, 2, 2),
		MakeInstruction(MOD, 0, 2),

		MakeInstruction(HLT, 0, 0)
	};
	*/
    c->mem = (byte*)memory;

    run(c);

	printf("reg2:%ld\n", c->reg[2]);
    return 0;
}
