#ifndef HEADER_MISC
#define HEADER_MISC

#include "core/cpu.h"

int nop(CPU* cpu);
int halt(CPU* cpu);
int di(CPU* cpu);
int ei(CPU* cpu);
int daa(CPU* cpu);

#endif
