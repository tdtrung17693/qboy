#ifndef HEADER_ROTSHIFT
#define HEADER_ROTSHIFT

#include "core/cpu.h"

int RLCA(CPU *cpu);
int RLA(CPU *cpu);
int RRCA(CPU *cpu);
int RRA(CPU *cpu);

int rlcB(CPU *cpu);
int rlcC(CPU *cpu);
int rlcD(CPU *cpu);
int rlcE(CPU *cpu);
int rlcH(CPU *cpu);
int rlcL(CPU *cpu);
int rlc_HL_(CPU *cpu);
int rlcA(CPU *cpu);

int rrcB(CPU *cpu);
int rrcC(CPU *cpu);
int rrcD(CPU *cpu);
int rrcE(CPU *cpu);
int rrcH(CPU *cpu);
int rrcL(CPU *cpu);
int rrc_HL_(CPU *cpu);
int rrcA(CPU *cpu);

int rlB(CPU *cpu);
int rlC(CPU *cpu);
int rlD(CPU *cpu);
int rlE(CPU *cpu);
int rlH(CPU *cpu);
int rlL(CPU *cpu);
int rl_HL_(CPU *cpu);
int rlA(CPU *cpu);

int rrB(CPU *cpu);
int rrC(CPU *cpu);
int rrD(CPU *cpu);
int rrE(CPU *cpu);
int rrH(CPU *cpu);
int rrL(CPU *cpu);
int rr_HL_(CPU *cpu);
int rrA(CPU *cpu);

int slaB(CPU *cpu);
int slaC(CPU *cpu);
int slaD(CPU *cpu);
int slaE(CPU *cpu);
int slaH(CPU *cpu);
int slaL(CPU *cpu);
int sla_HL_(CPU *cpu);
int slaA(CPU *cpu);

int sraB(CPU *cpu);
int sraC(CPU *cpu);
int sraD(CPU *cpu);
int sraE(CPU *cpu);
int sraH(CPU *cpu);
int sraL(CPU *cpu);
int sra_HL_(CPU *cpu);
int sraA(CPU *cpu);

int swapB(CPU *cpu);
int swapC(CPU *cpu);
int swapD(CPU *cpu);
int swapE(CPU *cpu);
int swapH(CPU *cpu);
int swapL(CPU *cpu);
int swap_HL_(CPU *cpu);
int swapA(CPU *cpu);

int srlB(CPU *cpu);
int srlC(CPU *cpu);
int srlD(CPU *cpu);
int srlE(CPU *cpu);
int srlH(CPU *cpu);
int srlL(CPU *cpu);
int srl_HL_(CPU *cpu);
int srlA(CPU *cpu);




#endif