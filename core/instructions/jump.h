#ifndef HEADER_JUMP
#define HEADER_JUMP

#include "core/cpu.h"

int jre(CPU *cpu);
int jrNZe(CPU *cpu); 
int jrZe(CPU *cpu);
int jrNCe(CPU *cpu);
int jrCe(CPU *cpu);

int retNZ(CPU *cpu);
int retNC(CPU *cpu);

int jpNZnn(CPU *cpu);
int jpNCnn(CPU *cpu);
int jpnn(CPU *cpu);

int callNZnn(CPU *cpu);
int callNCnn(CPU *cpu);

int rst00(CPU *cpu);
int rst08(CPU *cpu);
int rst10(CPU *cpu);
int rst18(CPU *cpu);
int rst20(CPU *cpu);
int rst28(CPU *cpu);
int rst30(CPU *cpu);
int rst38(CPU *cpu);

int retZ(CPU *cpu);
int retC(CPU *cpu);
int ret(CPU *cpu);
int reti(CPU *cpu);
int jp_HL_(CPU *cpu);
int jpZnn(CPU *cpu);
int jpCnn(CPU *cpu);
int callZnn(CPU *cpu);
int callCnn(CPU *cpu);
int callnn(CPU *cpu);

#endif