#ifndef HEADER_TRANSFER
#define HEADER_TRANSFER
#include "core/cpu.h"

// 8bit transfer instructions
int ld_BC_A(CPU *cpu);
int ldBn(CPU *cpu);
int ldA_BC_(CPU *cpu);
int ldCn(CPU *cpu);
int ld_DE_A(CPU *cpu);
int ldDn(CPU *cpu);
int ldA_DE_(CPU *cpu); 
int ldEn(CPU *cpu); 
int ld_HLi_A(CPU *cpu);
int ldHn(CPU *cpu);
int ldA_HLi_(CPU *cpu);
int ldLn(CPU *cpu);
int ld_HLd_A(CPU *cpu);
int ld_HL_n(CPU *cpu); 
int ldA_HLd_(CPU *cpu); 
int ldAn(CPU *cpu);
int ldBB(CPU *cpu); 
int ldBC(CPU *cpu); 
int ldBD(CPU *cpu); 
int ldBE(CPU *cpu); 
int ldBH(CPU *cpu); 
int ldBL(CPU *cpu); 
int ldB_HL_(CPU *cpu);
int ldBA(CPU *cpu); 
int ldCB(CPU *cpu); 
int ldCC(CPU *cpu); 
int ldCD(CPU *cpu);
int ldCE(CPU *cpu); 
int ldCH(CPU *cpu);
int ldCL(CPU *cpu);
int ldC_HL_(CPU *cpu); 
int ldCA(CPU *cpu); 
int ldDB(CPU *cpu);
int ldDC(CPU *cpu); 
int ldDD(CPU *cpu); 
int ldDE(CPU *cpu); 
int ldDH(CPU *cpu); 
int ldDL(CPU *cpu);
int ldD_HL_(CPU *cpu);
int ldDA(CPU *cpu);
int ldEB(CPU *cpu);
int ldEC(CPU *cpu); 
int ldED(CPU *cpu); 
int ldEE(CPU *cpu); 
int ldEH(CPU *cpu); 
int ldEL(CPU *cpu); 
int ldE_HL_(CPU *cpu); 
int ldEA(CPU *cpu);
int ldHB(CPU *cpu);
int ldHC(CPU *cpu);
int ldHD(CPU *cpu);
int ldHE(CPU *cpu); 
int ldHH(CPU *cpu); 
int ldHL(CPU *cpu); 
int ldH_HL_(CPU *cpu); 
int ldHA(CPU *cpu); 
int ldLB(CPU *cpu); 
int ldLC(CPU *cpu);
int ldLD(CPU *cpu); 
int ldLE(CPU *cpu); 
int ldLH(CPU *cpu); 
int ldLL(CPU *cpu); 
int ldL_HL_(CPU *cpu); 
int ldLA(CPU *cpu); 
int ld_HL_B(CPU *cpu); 
int ld_HL_C(CPU *cpu); 
int ld_HL_D(CPU *cpu); 
int ld_HL_E(CPU *cpu); 
int ld_HL_H(CPU *cpu); 
int ld_HL_L(CPU *cpu); 
int ld_HL_A(CPU *cpu); 
int ldAB(CPU *cpu); 
int ldAC(CPU *cpu); 
int ldAD(CPU *cpu); 
int ldAE(CPU *cpu); 
int ldAH(CPU *cpu); 
int ldAL(CPU *cpu); 
int ldA_HL_(CPU *cpu); 
int ldAA(CPU *cpu); 
int ld_n_A(CPU *cpu); 
int ld_C_A(CPU *cpu); 
int ld_nn_A(CPU *cpu); 
int ldA_n_(CPU *cpu); 
int ldA_C_(CPU *cpu); 
int ldA_nn_(CPU *cpu);

// 16bit transfer instructions
int ldBCnn(CPU *cpu); 
int ld_nn_SP(CPU *cpu); 
int ldDEnn(CPU *cpu); 
int ldHLnn(CPU *cpu); 
int ldSPnn(CPU *cpu); 
int popBC(CPU *cpu); 
int pushBC(CPU *cpu); 
int popDE(CPU *cpu); 
int pushDE(CPU *cpu); 
int popHL(CPU *cpu); 
int pushHL(CPU *cpu); 
int popAF(CPU *cpu);
int pushAF(CPU *cpu); 
int ldHLSPe(CPU *cpu); 
int ldSPHL(CPU *cpu);

#endif