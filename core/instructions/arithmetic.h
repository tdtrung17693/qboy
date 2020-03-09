#ifndef HEADER_ARITHMETIC
#define HEADER_ARITHMETIC

#include "core/cpu.h"

// 8bit arithmetic
int incB(CPU* cpu);
int incD(CPU* cpu);
int incH(CPU* cpu);
int inc_HL_(CPU* cpu);
int incC(CPU* cpu);
int incE(CPU* cpu);
int incL(CPU* cpu);
int incA(CPU* cpu);

int decB(CPU* cpu);
int decD(CPU* cpu);
int decH(CPU* cpu);
int dec_HL_(CPU* cpu);
int decC(CPU* cpu);
int decE(CPU* cpu);
int decL(CPU* cpu);
int decA(CPU* cpu);

int CPL(CPU* cpu);
int CCF(CPU* cpu);

int addAB(CPU* cpu);
int addAC(CPU* cpu);
int addAD(CPU* cpu);
int addAE(CPU* cpu);
int addAH(CPU* cpu);
int addAL(CPU* cpu);
int addA_HL_(CPU* cpu);
int addAA(CPU* cpu);

int adcAB(CPU* cpu);
int adcAC(CPU* cpu);
int adcAD(CPU* cpu);
int adcAE(CPU* cpu);
int adcAH(CPU* cpu);
int adcAL(CPU* cpu);
int adcA_HL_(CPU* cpu);
int adcAA(CPU* cpu);

int subAB(CPU* cpu);
int subAC(CPU* cpu);
int subAD(CPU* cpu);
int subAE(CPU* cpu);
int subAH(CPU* cpu);
int subAL(CPU* cpu);
int subA_HL_(CPU* cpu);
int subAA(CPU* cpu);

int sbcAB(CPU* cpu);
int sbcAC(CPU* cpu);
int sbcAD(CPU* cpu);
int sbcAE(CPU* cpu);
int sbcAH(CPU* cpu);
int sbcAL(CPU* cpu);
int sbcA_HL_(CPU* cpu);
int sbcAA(CPU* cpu);

int andB(CPU* cpu);
int andC(CPU* cpu);
int andD(CPU* cpu);
int andE(CPU* cpu);
int andH(CPU* cpu);
int andL(CPU* cpu);
int and_HL_(CPU* cpu);
int andA(CPU* cpu);

int xorB(CPU* cpu);
int xorC(CPU* cpu);
int xorD(CPU* cpu);
int xorE(CPU* cpu);
int xorH(CPU* cpu);
int xorL(CPU* cpu);
int xor_HL_(CPU* cpu);
int xorA(CPU* cpu);

int orB(CPU* cpu);
int orC(CPU* cpu);
int orD(CPU* cpu);
int orE(CPU* cpu);
int orH(CPU* cpu);
int orL(CPU* cpu);
int or_HL_(CPU* cpu);
int orA(CPU* cpu);

int cpB(CPU* cpu);
int cpC(CPU* cpu);
int cpD(CPU* cpu);
int cpE(CPU* cpu);
int cpH(CPU* cpu);
int cpL(CPU* cpu);
int cp_HL_(CPU* cpu);
int cpA(CPU* cpu);

int addAn(CPU* cpu);
int subAn(CPU* cpu);
int andn(CPU* cpu);
int orn(CPU* cpu);

int adcAn(CPU* cpu);
int sbcAn(CPU* cpu);
int xorn(CPU* cpu);
int cpn(CPU* cpu);

// 16bit arithmetic
int incBC(CPU* cpu);
int incDE(CPU* cpu);
int incHL(CPU* cpu);
int incSP(CPU* cpu);
int addHLBC(CPU* cpu);
int addHLDE(CPU* cpu);
int addHLHL(CPU* cpu);
int addHLSP(CPU* cpu);
int addSPe(CPU* cpu);
int decBC(CPU* cpu);
int decDE(CPU* cpu);
int decHL(CPU* cpu);
int decSP(CPU* cpu);

#endif
