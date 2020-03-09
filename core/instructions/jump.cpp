#include "jump.h"
#include "spdlog/spdlog.h"
#include <iostream>
using namespace std;

int jre(CPU* cpu)
{
    int8_t e = static_cast<int8_t>(cpu->mmu->read(cpu->pc + 1) + 2);
    COUT << "JR " << dec << signed(e) << endl;
    cpu->pc += e;
    return 12;
}

int jrNZe(CPU* cpu)
{
    if (cpu->pc == 0x2000) {
        //        cout << "Saw weird jump" << endl;
    }
    int8_t e = static_cast<int8_t>(cpu->mmu->read(cpu->pc + 1) + 2);
    if (e == 0) {

        //                cout << "lock" << endl;
    }
    spdlog::get("cpu_logger")->info("PC: {:04x} - JR NZ, {}", unsigned(cpu->pc), signed(e));
    if (cpu->z_flag == 0) {
        cpu->pc += e;
        return 12;
    } else {
        cpu->pc += 2;
        return 8;
    }
}

int jrZe(CPU* cpu)
{
    int8_t e = static_cast<int8_t>(cpu->mmu->read(cpu->pc + 1) + 2);
    COUT << "JR Z, " << dec << signed(e) << endl;
    if (cpu->z_flag == 1) {
        cpu->pc += e;
        return 12;
    } else {
        cpu->pc += 2;
        return 8;
    }
}
int jrNCe(CPU* cpu)
{
    int8_t e = static_cast<int8_t>(cpu->mmu->read(cpu->pc + 1) + 2);
    COUT << "JR C, " << dec << signed(e) << endl;
    if (cpu->c_flag == 0) {
        cpu->pc += e;
        return 12;
    } else {
        cpu->pc += 2;
        return 8;
    }
}

int jrCe(CPU* cpu)
{
    int8_t e = static_cast<int8_t>(cpu->mmu->read(cpu->pc + 1) + 2);
    COUT << "JR C, " << dec << signed(e) << endl;
    if (cpu->c_flag == 1) {
        cpu->pc += e;
        return 12;
    } else {
        cpu->pc += 2;
        return 8;
    }
}

int retNZ(CPU* cpu)
{
    //    PCL ← (SP)
    //    PCH ← (SP+1)
    //    SP ← SP + 2
    if (cpu->z_flag == 0) {
        uint8_t hi = cpu->mmu->read(cpu->sp + 1);
        uint8_t lo = cpu->mmu->read(cpu->sp);
        cpu->sp += 2;
        cpu->pc = static_cast<uint16_t>((hi << 8) | lo);
        return 20;
    }

    cpu->pc += 1;
    return 8;
}
int retNC(CPU* cpu)
{
    //    PCL ← (SP)
    //    PCH ← (SP+1)
    //    SP ← SP + 2
    if (cpu->c_flag == 0) {
        uint8_t hi = cpu->mmu->read(cpu->sp + 1);
        uint8_t lo = cpu->mmu->read(cpu->sp);
        cpu->sp += 2;
        cpu->pc = static_cast<uint16_t>((hi << 8) | lo);
        return 20;
    }

    cpu->pc += 1;
    return 8;
}

int jpNZnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    COUT << "JP NZ, " << hex << unsigned((hi << 8) | lo) << endl;
    if (cpu->z_flag == 0) {
        cpu->pc = (hi << 8) | lo;
        return 16;
    } else {
        cpu->pc += 3;
        return 12;
    }
}
int jpNCnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    COUT << "JP NC, " << hex << unsigned((hi << 8) | lo) << endl;
    if (cpu->c_flag == 0) {
        cpu->pc = (hi << 8) | lo;
        return 16;
    } else {
        cpu->pc += 3;
        return 12;
    }
}
int jpnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    uint16_t address = static_cast<uint16_t>((hi << 8) | lo);

    cpu->pc = address;
    return 16;
}

int callNZnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    COUT << "CALL NZ, " << hex << unsigned((hi << 8) | lo) << endl;
    if (cpu->z_flag == 0) {
        cpu->pc += 3;
        cpu->mmu->write(cpu->sp - 1, cpu->pc >> 8);
        cpu->mmu->write(cpu->sp - 2, cpu->pc & 0xff);
        cpu->pc = (hi << 8) | lo;
        cpu->sp -= 2;
        return 24;
    } else {
        cpu->pc += 3;
        return 12;
    }
}
int callNCnn(CPU* cpu);

int rst00(CPU* cpu)
{
    uint16_t sp = cpu->sp;
    cpu->pc += 1;
    cpu->mmu->write(sp - 1, cpu->pc >> 8);
    cpu->mmu->write(sp - 2, cpu->pc & 0xff);
    cpu->sp -= 2;
    cpu->pc = 0;
    return 16;
}
int rst08(CPU* cpu)
{
    uint16_t sp = cpu->sp;
    cpu->pc += 1;
    cpu->mmu->write(sp - 1, cpu->pc >> 8);
    cpu->mmu->write(sp - 2, cpu->pc & 0xff);
    cpu->sp -= 2;
    cpu->pc = 0x08;
    return 16;
}
int rst10(CPU* cpu)
{
    uint16_t sp = cpu->sp;
    cpu->pc += 1;
    cpu->mmu->write(sp - 1, cpu->pc >> 8);
    cpu->mmu->write(sp - 2, cpu->pc & 0xff);
    cpu->sp -= 2;
    cpu->pc = 0x10;
    return 16;
}
int rst18(CPU* cpu)
{
    uint16_t sp = cpu->sp;
    cpu->pc += 1;
    cpu->mmu->write(sp - 1, cpu->pc >> 8);
    cpu->mmu->write(sp - 2, cpu->pc & 0xff);
    cpu->sp -= 2;
    cpu->pc = 0x18;
    return 16;
}
int rst20(CPU* cpu)
{
    uint16_t sp = cpu->sp;
    cpu->pc += 1;
    cpu->mmu->write(sp - 1, cpu->pc >> 8);
    cpu->mmu->write(sp - 2, cpu->pc & 0xff);
    cpu->sp -= 2;
    cpu->pc = 0x20;
    return 16;
}
int rst28(CPU* cpu)
{
    COUT << "RST 28h" << endl;
    uint16_t sp = cpu->sp;
    cpu->pc += 1;
    cpu->mmu->write(sp - 1, cpu->pc >> 8);
    cpu->mmu->write(sp - 2, cpu->pc & 0xff);
    cpu->sp -= 2;
    cpu->pc = 0x28;

    return 16;
}
int rst30(CPU* cpu)
{
    uint16_t sp = cpu->sp;
    cpu->pc += 1;
    cpu->mmu->write(sp - 1, cpu->pc >> 8);
    cpu->mmu->write(sp - 2, cpu->pc & 0xff);
    cpu->sp -= 2;
    cpu->pc = 0x30;
    return 16;
}
int rst38(CPU* cpu)
{
    uint16_t sp = cpu->sp;
    cpu->pc += 1;
    cpu->mmu->write(sp - 1, cpu->pc >> 8);
    cpu->mmu->write(sp - 2, cpu->pc & 0xff);
    cpu->sp -= 2;
    cpu->pc = 0x38;
    return 16;
}

int retZ(CPU* cpu)
{
    //    PCL ← (SP)
    //    PCH ← (SP+1)
    //    SP ← SP + 2
    if (cpu->z_flag == 1) {
        uint8_t hi = cpu->mmu->read(cpu->sp + 1);
        uint8_t lo = cpu->mmu->read(cpu->sp);
        cpu->sp += 2;
        cpu->pc = static_cast<uint16_t>((hi << 8) | lo);
        return 20;
    }

    cpu->pc += 1;
    return 8;
}

int retC(CPU* cpu)
{
    //    PCL ← (SP)
    //    PCH ← (SP+1)
    //    SP ← SP + 2
    if (cpu->c_flag == 1) {
        uint8_t hi = cpu->mmu->read(cpu->sp + 1);
        uint8_t lo = cpu->mmu->read(cpu->sp);
        cpu->sp += 2;
        cpu->pc = static_cast<uint16_t>((hi << 8) | lo);
        return 20;
    }

    cpu->pc += 1;
    return 8;
}

int ret(CPU* cpu)
{
    COUT << "RET" << endl;
    uint8_t hi = cpu->mmu->read(cpu->sp + 1);
    uint8_t lo = cpu->mmu->read(cpu->sp);
    cpu->pc = ((hi << 8) | lo);
    cpu->sp += 2;
    return 16;
}
int reti(CPU* cpu)
{
    cpu->IME = true;
    cpu->pc = ((cpu->mmu->read(cpu->sp + 1) << 8) | cpu->mmu->read(cpu->sp));
    cpu->sp += 2;
    //    cout << "End interrupt. Return to " << hex << unsigned(cpu->pc) << endl;
    return 16;
}
int jp_HL_(CPU* cpu)
{
    cpu->pc = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    return 4;
}
int jpZnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    COUT << "JP Z, " << hex << unsigned((hi << 8) | lo) << endl;
    if (cpu->z_flag == 1) {
        cpu->pc = (hi << 8) | lo;
        return 16;
    } else {
        cpu->pc += 3;
        return 12;
    }
}
int jpCnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    COUT << "JP C, " << hex << unsigned((hi << 8) | lo) << endl;
    if (cpu->c_flag == 1) {
        cpu->pc = (hi << 8) | lo;
        return 16;
    } else {
        cpu->pc += 3;
        return 12;
    }
}
int callZnn(CPU* cpu)
{
    uint8_t hi = cpu->mmu->read(cpu->pc + 2);
    uint8_t lo = cpu->mmu->read(cpu->pc + 1);
    COUT << "CALL NZ, " << hex << unsigned((hi << 8) | lo) << endl;
    if (cpu->z_flag == 1) {
        cpu->pc += 3;
        cpu->mmu->write(cpu->sp - 1, cpu->pc >> 8);
        cpu->mmu->write(cpu->sp - 2, cpu->pc & 0xff);
        cpu->pc = (hi << 8) | lo;
        cpu->sp -= 2;
        return 24;
    } else {
        cpu->pc += 3;
        return 12;
    }
}
int callCnn(CPU* cpu);
int callnn(CPU* cpu)
{
    uint8_t low_address = cpu->mmu->read(cpu->pc + 1);
    uint8_t high_address = cpu->mmu->read(cpu->pc + 2);

    cpu->pc += 3;
    cpu->mmu->write(cpu->sp - 1, cpu->pc >> 8);
    cpu->mmu->write(cpu->sp - 2, cpu->pc & 0xff);
    cpu->pc = (high_address << 8) | low_address;
    cpu->sp -= 2;
    return 24;
}
