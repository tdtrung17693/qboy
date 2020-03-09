#include "core/cpu.h"
#include "core/gpu.h"
#include "core/instructions/instructions.h"
#include "core/utils.h"
#include "spdlog/spdlog.h"
#include <fstream>
#include <functional>
#include <iostream>

using namespace std;

static vector<int (*)(CPU*)> fns;
static vector<int (*)(CPU*)> fnsCB;
CPU::CPU()
{
    fns.resize(0x100);
    fnsCB.resize(0x100);
    // 8-bit transfer
    fns[0x02] = ld_BC_A;
    fns[0x12] = ld_DE_A;
    fns[0x22] = ld_HLi_A;
    fns[0x32] = ld_HLd_A;
    fns[0x06] = ldBn;
    fns[0x16] = ldDn;
    fns[0x26] = ldHn;
    fns[0x36] = ld_HL_n;
    fns[0x0a] = ldA_BC_;
    fns[0x1a] = ldA_DE_;
    fns[0x2a] = ldA_HLi_;
    fns[0x3a] = ldA_HLd_;
    fns[0x0e] = ldCn;
    fns[0x1e] = ldEn;
    fns[0x2e] = ldLn;
    fns[0x3e] = ldAn;

    fns[0x40] = ldBB;
    fns[0x41] = ldBC;
    fns[0x42] = ldBD;
    fns[0x43] = ldBE;
    fns[0x44] = ldBH;
    fns[0x45] = ldBL;
    fns[0x46] = ldB_HL_;
    fns[0x47] = ldBA;

    fns[0x48] = ldCB;
    fns[0x49] = ldCC;
    fns[0x4a] = ldCD;
    fns[0x4b] = ldCE;
    fns[0x4c] = ldCH;
    fns[0x4d] = ldCL;
    fns[0x4e] = ldC_HL_;
    fns[0x4f] = ldCA;

    fns[0x50] = ldDB;
    fns[0x51] = ldDC;
    fns[0x52] = ldDD;
    fns[0x53] = ldDE;
    fns[0x54] = ldDH;
    fns[0x55] = ldDL;
    fns[0x56] = ldD_HL_;
    fns[0x57] = ldDA;

    fns[0x58] = ldEB;
    fns[0x59] = ldEC;
    fns[0x5a] = ldED;
    fns[0x5b] = ldEE;
    fns[0x5c] = ldEH;
    fns[0x5d] = ldEL;
    fns[0x5e] = ldE_HL_;
    fns[0x5f] = ldEA;

    fns[0x60] = ldHB;
    fns[0x61] = ldHC;
    fns[0x62] = ldHD;
    fns[0x63] = ldHE;
    fns[0x64] = ldHH;
    fns[0x65] = ldHL;
    fns[0x66] = ldH_HL_;
    fns[0x67] = ldHA;

    fns[0x68] = ldLB;
    fns[0x69] = ldLC;
    fns[0x6a] = ldLD;
    fns[0x6b] = ldLE;
    fns[0x6c] = ldLH;
    fns[0x6d] = ldLL;
    fns[0x6e] = ldL_HL_;
    fns[0x6f] = ldLA;

    fns[0x70] = ld_HL_B;
    fns[0x71] = ld_HL_C;
    fns[0x72] = ld_HL_D;
    fns[0x73] = ld_HL_E;
    fns[0x74] = ld_HL_H;
    fns[0x75] = ld_HL_L;
    fns[0x76] = halt;
    fns[0x77] = ld_HL_A;

    fns[0x78] = ldAB;
    fns[0x79] = ldAC;
    fns[0x7a] = ldAD;
    fns[0x7b] = ldAE;
    fns[0x7c] = ldAH;
    fns[0x7d] = ldAL;
    fns[0x7e] = ldA_HL_;
    fns[0x7f] = ldAA;
    fns[0xe0] = ld_n_A;
    fns[0xf0] = ldA_n_;
    fns[0xe2] = ld_C_A;
    fns[0xf2] = ldA_C_;
    fns[0xea] = ld_nn_A;
    fns[0xfa] = ldA_nn_;

    // 16-bit transfer
    fns[0x01] = ldBCnn;
    fns[0x11] = ldDEnn;
    fns[0x21] = ldHLnn;
    fns[0x31] = ldSPnn;
    fns[0x08] = ld_nn_SP;
    fns[0xc1] = popBC;
    fns[0xd1] = popDE;
    fns[0xe1] = popHL;
    fns[0xf1] = popAF;
    fns[0xc5] = pushBC;
    fns[0xd5] = pushDE;
    fns[0xe5] = pushHL;
    fns[0xf5] = pushAF;
    fns[0xf8] = ldHLSPe;
    fns[0xf9] = ldSPHL;

    // 8-bit arithmetic
    fns[0x04] = incB;
    fns[0x14] = incD;
    fns[0x24] = incH;
    fns[0x34] = inc_HL_;
    fns[0x05] = decB;
    fns[0x15] = decD;
    fns[0x25] = decH;
    fns[0x35] = dec_HL_;
    fns[0x0c] = incC;
    fns[0x1c] = incE;
    fns[0x2c] = incL;
    fns[0x3c] = incA;
    fns[0x0d] = decC;
    fns[0x1d] = decE;
    fns[0x2d] = decL;
    fns[0x3d] = decA;

    fns[0x80] = addAB;
    fns[0x81] = addAC;
    fns[0x82] = addAD;
    fns[0x83] = addAE;
    fns[0x84] = addAH;
    fns[0x85] = addAL;
    fns[0x86] = addA_HL_;
    fns[0x87] = addAA;

    fns[0x88] = adcAB;
    fns[0x89] = adcAC;
    fns[0x8a] = adcAD;
    fns[0x8b] = adcAE;
    fns[0x8c] = adcAH;
    fns[0x8d] = adcAL;
    fns[0x8e] = adcA_HL_;
    fns[0x8f] = adcAA;

    fns[0x90] = subAB;
    fns[0x91] = subAC;
    fns[0x92] = subAD;
    fns[0x93] = subAE;
    fns[0x94] = subAH;
    fns[0x95] = subAL;
    fns[0x96] = subA_HL_;
    fns[0x97] = subAA;

    fns[0x98] = sbcAB;
    fns[0x99] = sbcAC;
    fns[0x9a] = sbcAD;
    fns[0x9b] = sbcAE;
    fns[0x9c] = sbcAH;
    fns[0x9d] = sbcAL;
    fns[0x9e] = sbcA_HL_;
    fns[0x9f] = sbcAA;

    fns[0xa0] = andB;
    fns[0xa1] = andC;
    fns[0xa2] = andD;
    fns[0xa3] = andE;
    fns[0xa4] = andH;
    fns[0xa5] = andL;
    fns[0xa7] = andA;

    fns[0xa8] = xorB;
    fns[0xa9] = xorC;
    fns[0xaa] = xorD;
    fns[0xab] = xorE;
    fns[0xac] = xorH;
    fns[0xad] = xorL;
    fns[0xae] = xor_HL_;
    fns[0xaf] = xorA;

    fns[0xb0] = orB;
    fns[0xb1] = orC;
    fns[0xb2] = orD;
    fns[0xb3] = orE;
    fns[0xb4] = orH;
    fns[0xb5] = orL;
    fns[0xb6] = or_HL_;
    fns[0xb7] = orA;

    fns[0xb8] = cpB;
    fns[0xb9] = cpC;
    fns[0xba] = cpD;
    fns[0xbb] = cpE;
    fns[0xbc] = cpH;
    fns[0xbd] = cpL;
    fns[0xbe] = cp_HL_;
    fns[0xbf] = cpA;

    fns[0xc6] = addAn;
    fns[0xce] = adcAn;
    fns[0xd6] = subAn;
    fns[0xe6] = andn;
    fns[0xee] = xorn;
    fns[0xf6] = orn;
    fns[0xfe] = cpn;

    fns[0x3f] = CCF;

    // 16-bit arithmetic
    fns[0x03] = incBC;
    fns[0x09] = addHLBC;
    fns[0x19] = addHLDE;
    fns[0x29] = addHLHL;
    fns[0x39] = addHLSP;
    fns[0xe8] = addSPe;
    fns[0x0b] = decBC;
    fns[0x1b] = decDE;
    fns[0x2b] = decHL;
    fns[0x13] = incDE;
    fns[0x23] = incHL;
    fns[0x33] = incSP;
    fns[0x2f] = CPL;

    // jump + call + ret
    fns[0x18] = jre;
    fns[0x20] = jrNZe;
    fns[0x28] = jrZe;
    fns[0x30] = jrNCe;
    fns[0x38] = jrCe;
    fns[0xc0] = retNZ;
    fns[0xc2] = jpNZnn;
    fns[0xd2] = jpNCnn;
    fns[0xda] = jpCnn;
    fns[0xc3] = jpnn;
    fns[0xc4] = callNZnn;
    fns[0xcc] = callZnn;
    fns[0xca] = jpZnn;
    fns[0xc8] = retZ;
    fns[0xd8] = retC;
    fns[0xc9] = ret;
    fns[0xd9] = reti;
    fns[0xcd] = callnn;
    fns[0xd0] = retNC;
    fns[0xe9] = jp_HL_;

    fns[0xc7] = rst00;
    fns[0xd7] = rst10;
    fns[0xe7] = rst20;
    fns[0xf7] = rst30;
    fns[0xcf] = rst08;
    fns[0xdf] = rst18;
    fns[0xef] = rst28;
    fns[0xff] = rst38;

    // rotate and shift
    fns[0x07] = RLCA;
    fns[0x17] = RLA;
    fns[0x1f] = RRA;

    // bit operation
    fnsCB[0x41] = bit0C;
    fnsCB[0x7c] = bit7H;

    fnsCB[0x10] = rlB;
    fnsCB[0x11] = rlC;
    fnsCB[0x12] = rlD;
    fnsCB[0x13] = rlE;
    fnsCB[0x14] = rlH;
    fnsCB[0x15] = rlL;
    fnsCB[0x16] = rl_HL_;
    fnsCB[0x17] = rlA;

    fnsCB[0x18] = rrB;
    fnsCB[0x19] = rrC;
    fnsCB[0x1a] = rrD;
    fnsCB[0x1b] = rrE;
    fnsCB[0x1c] = rrH;
    fnsCB[0x1d] = rrL;
    fnsCB[0x1e] = rr_HL_;
    fnsCB[0x1f] = rrA;

    fnsCB[0x20] = slaB;
    fnsCB[0x21] = slaC;
    fnsCB[0x22] = slaD;
    fnsCB[0x23] = slaE;
    fnsCB[0x24] = slaH;
    fnsCB[0x25] = slaL;
    fnsCB[0x25] = sla_HL_;
    fnsCB[0x27] = slaA;

    fnsCB[0x30] = swapB;
    fnsCB[0x31] = swapC;
    fnsCB[0x32] = swapD;
    fnsCB[0x33] = swapE;
    fnsCB[0x34] = swapH;
    fnsCB[0x35] = swapL;
    fnsCB[0x36] = swap_HL_;
    fnsCB[0x37] = swapA;

    fnsCB[0x38] = srlB;
    fnsCB[0x39] = srlC;
    fnsCB[0x3a] = srlD;
    fnsCB[0x3b] = srlE;
    fnsCB[0x3c] = srlH;
    fnsCB[0x3d] = srlL;
    fnsCB[0x3e] = srl_HL_;
    fnsCB[0x3f] = srlA;

    fnsCB[0x40] = bit0B;
    fnsCB[0x50] = bit2B;
    fnsCB[0x60] = bit4B;
    fnsCB[0x70] = bit6B;
    fnsCB[0x48] = bit1B;
    fnsCB[0x58] = bit3B;
    fnsCB[0x68] = bit5B;
    fnsCB[0x78] = bit7B;

    fnsCB[0x41] = bit0C;
    fnsCB[0x51] = bit2C;
    fnsCB[0x61] = bit4C;
    fnsCB[0x71] = bit6C;
    fnsCB[0x49] = bit1C;
    fnsCB[0x59] = bit3C;
    fnsCB[0x69] = bit5C;
    fnsCB[0x79] = bit7C;

    fnsCB[0x42] = bit0D;
    fnsCB[0x52] = bit2D;
    fnsCB[0x62] = bit4D;
    fnsCB[0x72] = bit6D;
    fnsCB[0x4a] = bit1D;
    fnsCB[0x5a] = bit3D;
    fnsCB[0x6a] = bit5D;
    fnsCB[0x7a] = bit7D;

    fnsCB[0x44] = bit0H;
    fnsCB[0x54] = bit2H;
    fnsCB[0x64] = bit4H;
    fnsCB[0x74] = bit6H;
    fnsCB[0x4c] = bit1H;
    fnsCB[0x5c] = bit3H;
    fnsCB[0x6c] = bit5H;
    fnsCB[0x7c] = bit7H;

    fnsCB[0x46] = bit0_HL_;
    fnsCB[0x56] = bit1_HL_;
    fnsCB[0x66] = bit2_HL_;
    fnsCB[0x76] = bit3_HL_;
    fnsCB[0x4e] = bit4_HL_;
    fnsCB[0x5e] = bit5_HL_;
    fnsCB[0x6e] = bit6_HL_;
    fnsCB[0x7e] = bit7_HL_;

    fnsCB[0x47] = bit0A;
    fnsCB[0x57] = bit2A;
    fnsCB[0x67] = bit4A;
    fnsCB[0x77] = bit6A;
    fnsCB[0x4f] = bit1A;
    fnsCB[0x5f] = bit3A;
    fnsCB[0x6f] = bit5A;
    fnsCB[0x7f] = bit7A;

    fnsCB[0x86] = res0_HL_;
    fnsCB[0x96] = res1_HL_;
    fnsCB[0xa6] = res2_HL_;
    fnsCB[0xb6] = res3_HL_;
    fnsCB[0x8e] = res4_HL_;
    fnsCB[0x9e] = res5_HL_;
    fnsCB[0xae] = res6_HL_;
    fnsCB[0xbe] = res7_HL_;

    fnsCB[0x87] = res0A;
    fnsCB[0x97] = res2A;
    fnsCB[0xa7] = res4A;
    fnsCB[0xb7] = res6A;
    fnsCB[0x8f] = res1A;
    fnsCB[0x9f] = res3A;
    fnsCB[0xaf] = res5A;
    fnsCB[0xbf] = res7A;

    fnsCB[0xc4] = set0H;
    fnsCB[0xd4] = set1H;
    fnsCB[0xe4] = set2H;
    fnsCB[0xf4] = set3H;
    fnsCB[0xcc] = set4H;
    fnsCB[0xdc] = set5H;
    fnsCB[0xec] = set6H;
    fnsCB[0xfc] = set7H;

    fnsCB[0xc6] = set0_HL_;
    fnsCB[0xd6] = set1_HL_;
    fnsCB[0xe6] = set2_HL_;
    fnsCB[0xf6] = set3_HL_;
    fnsCB[0xce] = set4_HL_;
    fnsCB[0xde] = set5_HL_;
    fnsCB[0xee] = set6_HL_;
    fnsCB[0xfe] = set7_HL_;

    // misc
    fns[0] = nop;
    fns[0x27] = daa;
    fns[0xf3] = di;
    fns[0xfb] = ei;

    timer = new Timer();
    timer->onTimerOverflow([&]() {
        requestInterrupt(INT_TIMER);
    });
}

void CPU::setMMU(MMU* mmu)
{
    this->mmu = mmu;

    timer->connect(mmu);
}
void CPU::setGPU(GPU* gpu)
{
    this->gpu = gpu;
    gpu->onVBlank([&]() {
        requestInterrupt(INT_VBLANK);
    });

    gpu->onLCDStat([&]() {
        requestInterrupt(INT_LCD_STAT);
    });
}
void CPU::setAPU(APU* apu)
{
    this->apu = apu;
}

int CPU::execute(uint8_t opcode)
{
    int cycles = 0;
    //    if (mmu->isBooting == false)
    //        printf("PC: %04x - OpCode: %02x\n", pc, opcode);
    if (opcode == 0xcb) {
        opcode = mmu->read(pc + 1);
        if (fnsCB[opcode] == nullptr) {
            cout << "Address: " << hex << unsigned(pc) << endl;
            cout << "CB Opcode not implemented. Opcode: " << hex << unsigned(opcode)
                 << std::endl;
            exit(1);
        }
        cycles = fnsCB[opcode](this);
    } else {
        if (fns[opcode] == nullptr) {
            cout << "Address: " << hex << unsigned(pc) << endl;
            cout << "Opcode not implemented. Opcode: " << hex << unsigned(opcode)
                 << std::endl;
            spdlog::get("cpu_logger")->flush();
            exit(1);
        }
        cycles = fns[opcode](this);
    }

    updateTimer(cycles);
    gpu->update(cycles);
    apu->update(cycles);
    handleInterrupt();

    return 0;
}

void CPU::reset()
{
    a = f = b = c = d = e = h = l = sp = pc = 0;
    mmu->isBooting = true;
    IME = false;
}

void CPU::updateTimer(uint8_t cycles)
{
    //    FF04 - DIV - Divider Register (R/W)
    //    This register is incremented at rate of 16384Hz (~16779Hz on SGB). In CGB Double Speed Mode it is incremented twice as fast, ie. at 32768Hz. Writing any value to this register resets it to 00h.

    //    FF05 - TIMA - Timer counter (R/W)
    //    This timer is incremented by a clock frequency specified by the TAC register ($FF07). When the value overflows (gets bigger than FFh) then it will be reset to the value specified in TMA (FF06), and an interrupt will be requested, as described below.

    //    FF06 - TMA - Timer Modulo (R/W)
    //    When the TIMA overflows, this data will be loaded.

    //    FF07 - TAC - Timer Control (R/W)

    //      Bit 2    - Timer Stop  (0=Stop, 1=Start)
    //      Bits 1-0 - Input Clock Select
    //                 00:   4096 Hz    (~4194 Hz SGB)
    //                 01: 262144 Hz  (~268400 Hz SGB)
    //                 10:  65536 Hz   (~67110 Hz SGB)
    //                 11:  16384 Hz   (~16780 Hz SGB)
    // Main clock: 4.194304MHz
    divCounter -= cycles;
    if (divCounter <= 0) {
        divCounter += 256;
        mmu->write(0xff04, mmu->read(0xff04) + 1);
    }

    timer->update(cycles);
}

void CPU::step()
{
    try {
        bool print = false;
        if (pc == 0x4d) {
            print = true;
            COUT << "Writing: " << hex << unsigned(a) << " to address " << hex
                 << unsigned((h << 8) | l) << endl;
        }
        execute(mmu->read(pc));
        if (print) {
            COUT << "Memory value : " << hex
                 << unsigned(mmu->read(((h << 8) | l) + 1)) << endl;
        }
    } catch (std::exception& e) {
    }
}

void CPU::loadBootRom()
{
    mmu->loadBootROM();
}

void CPU::loadRom(string romPath)
{
    mmu->loadROM(romPath);
}

void CPU::requestInterrupt(int interruptType)
{
    uint8_t IF = mmu->read(0xff0f);
    IF |= (1 << interruptType);
    mmu->write(0xff0f, IF);
}

void CPU::handleInterrupt()
{
    //   1. When an interrupt is generated, the IF flag will be
    //   set.
    //   2. If the IME flag is set & the corresponding IE flag
    //   is set, the following 3 steps are performed.
    //   3. Reset the IME flag and prevent all interrupts.
    //   4. The PC (program counter) is pushed onto the stack.
    //   5. Jump to the starting address of the interrupt.

    if (willEnableInterrupt) {
        IME = true;
        COUT << "Interrupt enabled" << endl;
        willEnableInterrupt = false;
        return;
    }

    if (!IME)
        return;
    bool haveInterrupt = false;
    uint8_t resetBit = 0;
    uint16_t savedPC = pc;
    uint8_t IF = mmu->read(0xff0f);
    uint8_t IE = mmu->read(0xffff);

    if ((IF & 0x01) == 1) {
        // VBlank interrupt
        if ((IE & 0x01) != 1)
            return;

        pc = 0x0040;
        resetBit = 0;
        haveInterrupt = true;
    } else if (((IF & 0x02) >> 1) == 1) {
        // LCD STAT Interrupt Requested
        if (((IE & 0x02) >> 1) != 1)
            return;

        pc = 0x0048;
        resetBit = 1;
        haveInterrupt = true;
    } else if (((IF & 0x04) >> 2) == 1) {
        // Timer interrupt
        if (((IE & 0x04) >> 2) != 1)
            return;
        pc = 0x0050;
        resetBit = 2;
        haveInterrupt = true;
    } else if (((IF & 0x08) >> 3) == 1) {
        // Serial interrupt
        if (((IE & 0x08) >> 3) != 1)
            return;

        pc = 0x0058;
        resetBit = 3;
        haveInterrupt = true;
    } else if (((IF & 0x10) >> 4) == 1) {
        // Joypad interrupt
        if (((IE & 0x10) >> 4) != 1)
            return;

        cout << "Handle joypadc" << endl;
        pc = 0x0060;
        resetBit = 4;
        haveInterrupt = true;
    }

    if (haveInterrupt) {

        IME = false;
        mmu->write(sp - 1, savedPC >> 8);
        mmu->write(sp - 2, savedPC & 0xff);
        sp -= 2;
        uint8_t newIF = IF & (~(1 << resetBit));
        mmu->write(0xff0f, newIF);
    }
}
