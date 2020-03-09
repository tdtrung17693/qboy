#include "transfer.h"
#include "core/utils.h"
#include "spdlog/spdlog.h"
#include <iostream>
using namespace std;

// 8bit transfer instructions
int ld_BC_A(CPU* cpu)
{
    COUT << "LDD (BC), A" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->b << 8) | cpu->c);
    cpu->mmu->write(address, cpu->a);
    cpu->pc += 1;

    return 8;
}

int ldBn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "LD B, " << hex << unsigned(n) << endl;
    cpu->b = n;

    cpu->pc += 2;
    return 8;
}

int ldA_BC_(CPU* cpu)
{
    COUT << "LD A, (BC)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->b << 8) | cpu->c);
    cpu->a = cpu->mmu->read(address);
    cpu->pc += 1;
    return 8;
}

int ldCn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "LD C, " << hex << unsigned(n) << endl;
    cpu->c = n;

    cpu->pc += 2;
    return 8;
}

int ld_DE_A(CPU* cpu)
{
    COUT << "LD (DE), A" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->d << 8) | cpu->e);
    cpu->mmu->write(address, cpu->a);
    cpu->pc += 1;
    return 8;
}

int ldDn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "LD D, " << hex << unsigned(n) << endl;
    cpu->d = cpu->mmu->read(cpu->pc + 1);

    cpu->pc += 2;
    return 8;
}

int ldA_DE_(CPU* cpu)
{
    COUT << "LD A, (DE)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->d << 8) | cpu->e);
    cpu->a = cpu->mmu->read(address);
    cpu->pc += 1;
    return 8;
}

int ldEn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "LD E, " << hex << unsigned(n) << endl;
    cpu->e = n;

    cpu->pc += 2;
    return 8;
}

int ld_HLi_A(CPU* cpu)
{
    COUT << "LDI (HL), A" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->mmu->write(address, cpu->a);
    COUT << "write to memory address " << hex << unsigned(address) << endl;
    address += 1;

    cpu->h = address >> 8;
    cpu->l = address & 0xff;
    cpu->pc += 1;
    return 8;
}

int ldHn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "LD H, " << hex << unsigned(n) << endl;
    cpu->h = n;

    cpu->pc += 2;
    return 8;
}

int ldA_HLi_(CPU* cpu)
{
    COUT << "LDI A, (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->a = cpu->mmu->read(address);
    address += 1;

    cpu->h = address >> 8;
    cpu->l = address & 0xff;
    cpu->pc += 1;
    return 8;
}

int ldLn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "LD L, " << hex << unsigned(n) << endl;
    cpu->l = n;

    cpu->pc += 2;
    return 8;
}

int ld_HLd_A(CPU* cpu)
{
    COUT << "LDD (HL), A" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);

    cpu->mmu->write(address, cpu->a);
    if (cpu->pc == 0x279d) {
        COUT << "Current HL: " << hex << unsigned(address) << endl;
    }
    address -= 1;

    cpu->h = address >> 8;
    cpu->l = address & 0xff;
    cpu->pc += 1;

    return 8;
}

int ld_HL_n(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "LD (HL), " << hex << unsigned(n) << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->mmu->write(address, n);
    cpu->pc += 2;
    return 12;
}

int ldA_HLd_(CPU* cpu)
{
    COUT << "LDD A, (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->a = cpu->mmu->read(address);
    address -= 1;

    cpu->h = address >> 8;
    cpu->l = address & 0xff;
    cpu->pc += 1;
    return 8;
}

int ldAn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "LD A, " << hex << unsigned(n) << endl;
    cpu->a = n;

    cpu->pc += 2;
    return 8;
}

int ldBB(CPU* cpu)
{
    COUT << "LD B, B" << endl;
    cpu->pc += 1;
    return 4;
}

int ldBC(CPU* cpu)
{
    COUT << "LD B, C" << endl;
    cpu->b = cpu->c;
    cpu->pc += 1;
    return 4;
}

int ldBD(CPU* cpu)
{
    COUT << "LD B, D" << endl;
    cpu->b = cpu->d;
    cpu->pc += 1;
    return 4;
}

int ldBE(CPU* cpu)
{
    COUT << "LD B, E" << endl;
    cpu->b = cpu->e;
    cpu->pc += 1;
    return 4;
}

int ldBH(CPU* cpu)
{
    COUT << "LD B, H" << endl;
    cpu->b = cpu->h;
    cpu->pc += 1;
    return 4;
}

int ldBL(CPU* cpu)
{
    COUT << "LD B, L" << endl;
    cpu->b = cpu->l;
    cpu->pc += 1;
    return 4;
}

int ldB_HL_(CPU* cpu)
{
    COUT << "LD B, (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->b = cpu->mmu->read(address);
    cpu->pc += 1;
    return 8;
}

int ldBA(CPU* cpu)
{
    COUT << "LD B, A" << endl;
    cpu->b = cpu->a;
    cpu->pc += 1;
    return 4;
}

int ldCB(CPU* cpu)
{
    COUT << "LD C, B" << endl;
    cpu->c = cpu->b;
    cpu->pc += 1;
    return 4;
}

int ldCC(CPU* cpu)
{
    COUT << "LD C, C" << endl;
    cpu->pc += 1;
    return 4;
}

int ldCD(CPU* cpu)
{
    COUT << "LD C, D" << endl;
    cpu->c = cpu->d;
    cpu->pc += 1;
    return 4;
}

int ldCE(CPU* cpu)
{
    COUT << "LD C, E" << endl;
    cpu->c = cpu->e;
    cpu->pc += 1;
    return 4;
}

int ldCH(CPU* cpu)
{
    COUT << "LD C, H" << endl;
    cpu->c = cpu->h;
    cpu->pc += 1;
    return 4;
}

int ldCL(CPU* cpu)
{
    COUT << "LD C, L" << endl;
    cpu->c = cpu->l;
    cpu->pc += 1;
    return 4;
}

int ldC_HL_(CPU* cpu)
{
    COUT << "LD C, (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->c = cpu->mmu->read(address);
    cpu->pc += 1;
    return 8;
}

int ldCA(CPU* cpu)
{
    COUT << "LD C, A" << endl;
    cpu->c = cpu->a;
    cpu->pc += 1;
    return 4;
}

int ldDB(CPU* cpu)
{
    COUT << "LD D, B" << endl;
    cpu->d = cpu->b;
    cpu->pc += 1;
    return 4;
}

int ldDC(CPU* cpu)
{
    COUT << "LD D, C" << endl;
    cpu->d = cpu->c;
    cpu->pc += 1;
    return 4;
}

int ldDD(CPU* cpu)
{
    COUT << "LD D, D" << endl;
    cpu->pc += 1;
    return 4;
}

int ldDE(CPU* cpu)
{
    COUT << "LD D, E" << endl;
    cpu->d = cpu->e;
    cpu->pc += 1;
    return 4;
}

int ldDH(CPU* cpu)
{
    COUT << "LD D, H" << endl;
    cpu->d = cpu->h;
    cpu->pc += 1;
    return 4;
}

int ldDL(CPU* cpu)
{
    COUT << "LD D, L" << endl;
    cpu->d = cpu->l;
    cpu->pc += 1;
    return 4;
}

int ldD_HL_(CPU* cpu)
{
    COUT << "LD D, (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->d = cpu->mmu->read(address);
    cpu->pc += 1;
    return 8;
}

int ldDA(CPU* cpu)
{
    COUT << "LD D, A" << endl;
    cpu->d = cpu->a;
    cpu->pc += 1;
    return 4;
}

int ldEB(CPU* cpu)
{
    COUT << "LD E, B" << endl;
    cpu->e = cpu->b;
    cpu->pc += 1;
    return 4;
}

int ldEC(CPU* cpu)
{
    COUT << "LD E, C" << endl;
    cpu->e = cpu->c;
    cpu->pc += 1;
    return 4;
}

int ldED(CPU* cpu)
{
    COUT << "LD E, D" << endl;
    cpu->e = cpu->d;
    cpu->pc += 1;
    return 4;
}

int ldEE(CPU* cpu)
{
    COUT << "LD E, E" << endl;
    cpu->pc += 1;
    return 4;
}

int ldEH(CPU* cpu)
{
    COUT << "LD E, H" << endl;
    cpu->e = cpu->h;
    cpu->pc += 1;
    return 4;
}

int ldEL(CPU* cpu)
{
    COUT << "LD E, L" << endl;
    cpu->e = cpu->l;
    cpu->pc += 1;
    return 4;
}

int ldE_HL_(CPU* cpu)
{
    COUT << "LD E, (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    COUT << "HL: " << hex << address << " - Value: " << unsigned(cpu->mmu->read(address)) << endl;
    cpu->e = cpu->mmu->read(address);
    cpu->pc += 1;
    return 8;
}

int ldEA(CPU* cpu)
{
    COUT << "LD E, A" << endl;
    cpu->e = cpu->a;
    cpu->pc += 1;
    return 4;
}

int ldHB(CPU* cpu)
{
    COUT << "LD H, B" << endl;
    cpu->h = cpu->b;
    cpu->pc += 1;
    uint16_t hl = (cpu->h << 8) | cpu->l;
    if ((hl >> 8) == 0xb2) {
        dumpCPU(cpu);
    }
    return 4;
}

int ldHC(CPU* cpu)
{
    COUT << "LD H, C" << endl;
    cpu->h = cpu->c;
    cpu->pc += 1;
    return 4;
}

int ldHD(CPU* cpu)
{
    COUT << "LD H, D" << endl;
    cpu->h = cpu->d;
    cpu->pc += 1;
    return 4;
}

int ldHE(CPU* cpu)
{
    COUT << "LD H, E" << endl;
    cpu->h = cpu->e;
    cpu->pc += 1;
    return 4;
}

int ldHH(CPU* cpu)
{
    COUT << "LD H, H" << endl;
    cpu->pc += 1;
    return 4;
}

int ldHL(CPU* cpu)
{
    COUT << "LD H, L" << endl;
    cpu->h = cpu->l;
    cpu->pc += 1;
    return 4;
}

int ldH_HL_(CPU* cpu)
{
    COUT << "LD H, (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->h = cpu->mmu->read(address);
    cpu->pc += 1;
    return 8;
}

int ldHA(CPU* cpu)
{
    COUT << "LD H, A" << endl;
    cpu->h = cpu->a;
    cpu->pc += 1;
    return 4;
}

int ldLB(CPU* cpu)
{
    COUT << "LD L, B" << endl;
    cpu->l = cpu->b;
    cpu->pc += 1;
    return 4;
}

int ldLC(CPU* cpu)
{
    COUT << "LD L, C" << endl;
    cpu->l = cpu->c;
    cpu->pc += 1;

    return 4;
}

int ldLD(CPU* cpu)
{
    COUT << "LD L, D" << endl;
    cpu->l = cpu->d;
    cpu->pc += 1;
    return 4;
}

int ldLE(CPU* cpu)
{
    COUT << "LD L, E" << endl;
    cpu->l = cpu->e;
    cpu->pc += 1;
    return 4;
}

int ldLH(CPU* cpu)
{
    COUT << "LD L, H" << endl;
    cpu->l = cpu->h;
    cpu->pc += 1;
    return 4;
}

int ldLL(CPU* cpu)
{
    COUT << "LD L, L" << endl;
    cpu->pc += 1;
    return 4;
}

int ldL_HL_(CPU* cpu)
{
    COUT << "LD L, (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->l = cpu->mmu->read(address);
    cpu->pc += 1;
    return 8;
}

int ldLA(CPU* cpu)
{
    COUT << "LD L, A" << endl;
    cpu->l = cpu->a;
    cpu->pc += 1;
    return 4;
}

int ld_HL_B(CPU* cpu)
{
    COUT << "LD (HL), B" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->mmu->write(address, cpu->b);
    cpu->pc += 1;
    return 8;
}

int ld_HL_C(CPU* cpu)
{
    COUT << "LD (HL), C" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->mmu->write(address, cpu->c);
    cpu->pc += 1;
    return 8;
}

int ld_HL_D(CPU* cpu)
{
    COUT << "LD (HL), D" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->mmu->write(address, cpu->d);
    cpu->pc += 1;
    return 8;
}

int ld_HL_E(CPU* cpu)
{
    COUT << "LD (HL), E" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->mmu->write(address, cpu->e);
    cpu->pc += 1;
    return 8;
}

int ld_HL_H(CPU* cpu)
{
    COUT << "LD (HL), H" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->mmu->write(address, cpu->h);
    cpu->pc += 1;
    return 8;
}

int ld_HL_L(CPU* cpu)
{
    COUT << "LD (HL), L" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->mmu->write(address, cpu->l);
    cpu->pc += 1;
    return 8;
}

int ld_HL_A(CPU* cpu)
{
    COUT << "LD (HL), A" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->mmu->write(address, cpu->a);
    cpu->pc += 1;
    return 8;
}

int ldAB(CPU* cpu)
{
    COUT << "LD A, B" << endl;
    cpu->a = cpu->b;
    cpu->pc += 1;
    return 4;
}

int ldAC(CPU* cpu)
{
    COUT << "LD A, C" << endl;
    cpu->a = cpu->c;
    cpu->pc += 1;
    return 4;
}

int ldAD(CPU* cpu)
{
    COUT << "LD A, D" << endl;
    cpu->a = cpu->d;
    cpu->pc += 1;
    return 4;
}

int ldAE(CPU* cpu)
{
    COUT << "LD A, E" << endl;
    cpu->a = cpu->e;
    cpu->pc += 1;
    return 4;
}

int ldAH(CPU* cpu)
{
    COUT << "LD A, H" << endl;
    cpu->a = cpu->h;
    cpu->pc += 1;
    return 4;
}

int ldAL(CPU* cpu)
{
    COUT << "LD A, L" << endl;
    cpu->a = cpu->l;
    cpu->pc += 1;
    return 4;
}

int ldA_HL_(CPU* cpu)
{
    COUT << "LD A, (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->a = cpu->mmu->read(address);
    cpu->pc += 1;
    return 8;
}

int ldAA(CPU* cpu)
{
    COUT << "LD A, A" << endl;
    cpu->pc += 1;
    return 4;
}

int ld_n_A(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    cpu->mmu->write(0xff00 + n, cpu->a);
    cpu->pc += 2;
    return 12;
}

int ld_C_A(CPU* cpu)
{
    COUT << "LD (C), A" << endl;
    cpu->mmu->write(0xff00 + cpu->c, cpu->a);
    cpu->pc += 1;
    return 8;
}

int ld_nn_A(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    uint16_t nn = static_cast<uint16_t>((hi << 8) | lo);
    COUT << "LD (" << hex << unsigned(nn) << "), A" << endl;

    cpu->mmu->write(nn, cpu->a);
    cpu->pc += 3;
    return 16;
}

int ldA_n_(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    cpu->a = cpu->mmu->read(0xff00 + n);
    cpu->pc += 2;
    return 12;
}

int ldA_C_(CPU* cpu)
{
    COUT << "LD A, (C)" << endl;
    cpu->a = cpu->mmu->read(0xff00 + cpu->c);
    cpu->pc += 1;
    return 8;
}

int ldA_nn_(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    uint16_t nn = static_cast<uint16_t>((hi << 8) | lo);
    COUT << "LD A, (" << hex << unsigned(nn) << ")" << endl;

    cpu->a = cpu->mmu->read(nn);
    cpu->pc += 3;
    return 16;
}

// 16bit transfer instructions
int ldBCnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    uint16_t nn = static_cast<uint16_t>((hi << 8) | lo);
    COUT << "LD BC, " << hex << unsigned(nn) << endl;
    cpu->b = nn >> 8;
    cpu->c = nn & 0xff;

    cpu->pc += 3;
    return 12;
}

int ld_nn_SP(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    uint8_t hiSP = cpu->sp >> 8;
    uint8_t loSP = cpu->sp & 0xf;

    uint16_t nn = static_cast<uint16_t>((hi << 8) | lo);
    COUT << "LD (" << hex << unsigned(nn) << "), SP" << endl;
    cpu->mmu->write(nn, loSP);
    cpu->mmu->write(nn + 1, hiSP);

    cpu->pc += 3;
    return 20;
}

int ldDEnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);

    uint16_t nn = static_cast<uint16_t>((hi << 8) | lo);
    COUT << "LD DE, " << hex << unsigned(nn) << endl;
    cpu->d = nn >> 8;
    cpu->e = nn & 0xff;

    //    if (cpu->pc == 0x18a7) {
    //        spdlog::get("cpu_logger")->set_level(spdlog::level::info);
    //    }

    cpu->pc += 3;

    return 12;
}

int ldHLnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);

    cpu->h = hi;
    cpu->l = lo;
    COUT << "LD HL, " << hex << unsigned((cpu->h << 8) | cpu->l) << endl;

    cpu->pc += 3;
    return 12;
}

int ldSPnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);

    uint16_t nn = static_cast<uint16_t>((hi << 8) | lo);
    COUT << "LD SP, " << hex << unsigned(nn) << endl;
    cpu->sp = nn;

    cpu->pc += 3;
    return 12;
}

int popBC(CPU* cpu)
{
    COUT << "POP BC" << endl;
    cpu->c = cpu->mmu->read(cpu->sp);
    cpu->b = cpu->mmu->read(cpu->sp + 1);
    cpu->sp = cpu->sp + 2;

    cpu->pc += 1;
    return 12;
}

int pushBC(CPU* cpu)
{
    COUT << "PUSH BC" << endl;
    cpu->mmu->write(cpu->sp - 1, cpu->b);
    cpu->mmu->write(cpu->sp - 2, cpu->c);
    cpu->sp = cpu->sp - 2;
    cpu->pc += 1;
    return 16;
}

int popDE(CPU* cpu)
{
    COUT << "POP DE" << endl;
    cpu->e = cpu->mmu->read(cpu->sp);
    cpu->d = cpu->mmu->read(cpu->sp + 1);
    cpu->sp = cpu->sp + 2;
    cpu->pc += 1;
    return 12;
}

int pushDE(CPU* cpu)
{
    COUT << "PUSH DE" << endl;
    cpu->mmu->write(cpu->sp - 1, cpu->d);
    cpu->mmu->write(cpu->sp - 2, cpu->e);
    cpu->sp = cpu->sp - 2;
    cpu->pc += 1;
    return 16;
}

int popHL(CPU* cpu)
{
    COUT << "POP HL" << endl;

    cpu->l = cpu->mmu->read(cpu->sp);
    cpu->h = cpu->mmu->read(cpu->sp + 1);
    cpu->sp = cpu->sp + 2;
    cpu->pc += 1;
    COUT << "HL = " << hex << unsigned((cpu->h << 8) | cpu->l) << endl;
    return 12;
}

int pushHL(CPU* cpu)
{
    COUT << "PUSH HL" << endl;
    cpu->mmu->write(cpu->sp - 1, cpu->h);
    cpu->mmu->write(cpu->sp - 2, cpu->l);
    cpu->sp = cpu->sp - 2;
    cpu->pc += 1;
    return 16;
}

int popAF(CPU* cpu)
{
    COUT << "POP AF" << endl;
    cpu->f = cpu->mmu->read(cpu->sp);

    cpu->z_flag = readBit(7, cpu->f);
    cpu->n_flag = readBit(6, cpu->f);
    cpu->h_flag = readBit(5, cpu->f);
    cpu->c_flag = readBit(4, cpu->f);

    cpu->a = cpu->mmu->read(cpu->sp + 1);
    cpu->sp = cpu->sp + 2;
    cpu->pc += 1;
    return 12;
}

int pushAF(CPU* cpu)
{
    COUT << "PUSH AF" << endl;
    cpu->f = (cpu->z_flag << 7) | (cpu->n_flag << 6) | (cpu->h_flag << 5) | (cpu->c_flag << 4);
    cpu->mmu->write(cpu->sp - 1, cpu->a);
    cpu->mmu->write(cpu->sp - 2, cpu->f);
    cpu->sp = cpu->sp - 2;
    cpu->pc += 1;
    return 16;
}

int ldHLSPe(CPU* cpu)
{
    int8_t e = static_cast<int8_t>(cpu->mmu->read(cpu->pc + 1));
    uint8_t new_h_flag = (((cpu->sp & 0xfff) + (e & 0xfff)) & 0x1000) != 0;
    uint8_t new_c_flag = ((cpu->sp + e) & 0x10000) != 0;
    uint16_t newHL = static_cast<uint16_t>(cpu->sp + e);
    cpu->h = newHL >> 8;
    cpu->l = newHL & 0xff;

    cpu->z_flag = 0;
    cpu->n_flag = 0;

    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 2;
    return 12;
}

int ldSPHL(CPU* cpu)
{
    cpu->sp = (cpu->h << 8) | cpu->l;
    cpu->pc += 1;
    return 8;
}
