#include "rot_and_shift.h"
#include "core/utils.h"
#include <iostream>
using namespace std;

int RLCA(CPU* cpu)
{
    //Rotates the contents of register A to the left.
    //That is, the contents of bit 0 are copied to bit 1 and the previous contents of bit 1 (the contents before the
    //copy operation) are copied to bit 2. The same operation is repeated in sequence for the rest of the
    //register. The contents of bit 7 are placed in both CY and bit 0 of register A..
    COUT << "RLCA" << endl;
    uint8_t a = cpu->a;
    uint8_t new_cflag = (a & (1 << 7)) >> 7;

    cpu->z_flag = 0;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    a = a << 1;
    a |= new_cflag;
    cpu->a = a;
    cpu->pc += 1;
    return 4;
}
int RLA(CPU* cpu)
{
    COUT << "RLA" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t a = cpu->a;
    uint8_t new_cflag = (a & (1 << 7)) >> 7;

    cpu->z_flag = 0;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;
    a = a << 1;
    a |= c_flag;
    cpu->a = a;
    cpu->pc += 1;
    return 4;
}
int RRCA(CPU* cpu);
int RRA(CPU* cpu)
{
    COUT << "RRA" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t a = cpu->a;
    uint8_t new_cflag = a & 0x1;

    cpu->z_flag = 0;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;
    a = a >> 1;
    a |= (c_flag << 7);
    cpu->a = a;
    cpu->pc += 1;
    return 4;
}

int rlcB(CPU* cpu);
int rlcC(CPU* cpu);
int rlcD(CPU* cpu);
int rlcE(CPU* cpu);
int rlcH(CPU* cpu);
int rlcL(CPU* cpu);
int rlc_HL_(CPU* cpu);
int rlcA(CPU* cpu);

int rrcB(CPU* cpu);
int rrcC(CPU* cpu);
int rrcD(CPU* cpu);
int rrcE(CPU* cpu);
int rrcH(CPU* cpu);
int rrcL(CPU* cpu);
int rrc_HL_(CPU* cpu);
int rrcA(CPU* cpu);

int rlB(CPU* cpu)
{
    COUT << "RL B" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t b = cpu->b;
    uint8_t new_cflag = (b & (1 << 7)) >> 7;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    b = b << 1;
    b |= c_flag;
    cpu->b = b;

    if (b == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rlC(CPU* cpu)
{
    COUT << "RL C" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t c = cpu->c;
    uint8_t new_cflag = (c & (1 << 7)) >> 7;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    c = c << 1;
    c |= c_flag;
    cpu->c = c;

    if (c == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rlD(CPU* cpu)
{
    COUT << "RL D" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t d = cpu->d;
    uint8_t new_cflag = (d & (1 << 7)) >> 7;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    d = d << 1;
    d |= c_flag;
    cpu->d = d;

    if (d == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rlE(CPU* cpu)
{
    COUT << "RL E" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t e = cpu->e;
    uint8_t new_cflag = (e & (1 << 7)) >> 7;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    e = e << 1;
    e |= c_flag;
    cpu->e = e;

    if (e == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rlH(CPU* cpu)
{
    COUT << "RL H" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t h = cpu->h;
    uint8_t new_cflag = (h & (1 << 7)) >> 7;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    h = h << 1;
    h |= c_flag;
    cpu->h = h;

    if (h == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rlL(CPU* cpu)
{
    COUT << "RL L" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t l = cpu->l;
    uint8_t new_cflag = (l & (1 << 7)) >> 7;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    l = l << 1;
    l |= c_flag;
    cpu->l = l;

    if (l == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rl_HL_(CPU* cpu)
{
    COUT << "RL A" << endl;
    uint16_t address = (cpu->h << 8) | cpu->l;
    uint8_t n = cpu->mmu->read(address);
    uint8_t c_flag = cpu->c_flag;
    uint8_t new_cflag = (n & (1 << 7)) >> 7;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    n = n << 1;
    n |= c_flag;
    cpu->mmu->write(address, n);

    if (n == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 16;
}
int rlA(CPU* cpu)
{
    COUT << "RL A" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t a = cpu->a;
    uint8_t new_cflag = (a & (1 << 7)) >> 7;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    a = a << 1;
    a |= c_flag;
    cpu->a = a;

    if (a == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}

int rrB(CPU* cpu)
{
    COUT << "RR B" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t n = cpu->b;
    uint8_t new_cflag = n & 0x1;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    n = n >> 1;
    n |= (c_flag << 7);
    cpu->b = n;

    if (n == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rrC(CPU* cpu)
{
    COUT << "RR B" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t n = cpu->c;
    uint8_t new_cflag = n & 0x1;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    n = n >> 1;
    n |= (c_flag << 7);
    cpu->c = n;

    if (n == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rrD(CPU* cpu)
{
    uint8_t c_flag = cpu->c_flag;
    uint8_t n = cpu->d;
    uint8_t new_cflag = n & 0x1;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    n = n >> 1;
    n |= (c_flag << 7);
    cpu->d = n;

    if (n == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rrE(CPU* cpu)
{
    uint8_t c_flag = cpu->c_flag;
    uint8_t n = cpu->e;
    uint8_t new_cflag = n & 0x1;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    n = n >> 1;
    n |= (c_flag << 7);
    cpu->e = n;

    if (n == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rrH(CPU* cpu)
{
    COUT << "RR B" << endl;
    uint8_t c_flag = cpu->c_flag;
    uint8_t n = cpu->h;
    uint8_t new_cflag = n & 0x1;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    n = n >> 1;
    n |= (c_flag << 7);
    cpu->h = n;

    if (n == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rrL(CPU* cpu)
{
    uint8_t c_flag = cpu->c_flag;
    uint8_t n = cpu->l;
    uint8_t new_cflag = n & 0x1;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    n = n >> 1;
    n |= (c_flag << 7);
    cpu->l = n;

    if (n == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}
int rr_HL_(CPU* cpu)
{
    COUT << "RR B" << endl;
    uint16_t address = (cpu->h << 8) | cpu->l;
    uint8_t c_flag = cpu->c_flag;
    uint8_t n = cpu->mmu->read(address);
    uint8_t new_cflag = n & 0x1;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    n = n >> 1;
    n |= (c_flag << 7);
    cpu->mmu->write(address, n);

    if (n == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 16;
}
int rrA(CPU* cpu)
{
    uint8_t c_flag = cpu->c_flag;
    uint8_t n = cpu->a;
    uint8_t new_cflag = n & 0x1;

    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = new_cflag;

    n = n >> 1;
    n |= (c_flag << 7);
    cpu->a = n;

    if (n == 0)
        cpu->z_flag = 1;
    else
        cpu->z_flag = 0;

    cpu->pc += 2;
    return 8;
}

int slaB(CPU* cpu)
{
    cpu->c_flag = readBit(7, cpu->b);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->b = cpu->b << 1;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 2;

    return 8;
}
int slaC(CPU* cpu)
{
    cpu->c_flag = readBit(7, cpu->c);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->c = cpu->c << 1;
    cpu->z_flag = cpu->c == 0;
    cpu->pc += 2;

    return 8;
}
int slaD(CPU* cpu)
{
    cpu->c_flag = readBit(7, cpu->d);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->d = cpu->d << 1;
    cpu->z_flag = cpu->d == 0;
    cpu->pc += 2;

    return 8;
}
int slaE(CPU* cpu)
{
    cpu->c_flag = readBit(7, cpu->e);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->e = cpu->e << 1;
    cpu->z_flag = cpu->e == 0;
    cpu->pc += 2;

    return 8;
}
int slaH(CPU* cpu)
{
    cpu->c_flag = readBit(7, cpu->h);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->h = cpu->h << 1;
    cpu->z_flag = cpu->h == 0;
    cpu->pc += 2;

    return 8;
}
int slaL(CPU* cpu)
{
    cpu->c_flag = readBit(7, cpu->l);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->l = cpu->l << 1;
    cpu->z_flag = cpu->l == 0;
    cpu->pc += 2;

    return 8;
}
int sla_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->c_flag = readBit(7, value);
    cpu->h_flag = cpu->n_flag = 0;

    value = value << 1;
    cpu->mmu->write(address, value);
    cpu->z_flag = value == 0;
    cpu->pc += 2;

    return 16;
}
int slaA(CPU* cpu)
{
    cpu->c_flag = readBit(7, cpu->a);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->a = static_cast<uint8_t>(cpu->a << 1);
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 2;

    return 8;
}

int sraB(CPU* cpu);
int sraC(CPU* cpu);
int sraD(CPU* cpu);
int sraE(CPU* cpu);
int sraH(CPU* cpu);
int sraL(CPU* cpu);
int sra_HL_(CPU* cpu);
int sraA(CPU* cpu);

int swapB(CPU* cpu)
{
    uint8_t hs = cpu->b >> 4;
    uint8_t ls = cpu->b & 0xf;

    cpu->b = static_cast<uint8_t>((ls << 4) | hs);
    cpu->z_flag = cpu->b == 0;
    cpu->pc += 2;
    return 8;
}
int swapC(CPU* cpu)
{
    uint8_t hs = cpu->c >> 4;
    uint8_t ls = cpu->c & 0xf;

    cpu->c = static_cast<uint8_t>((ls << 4) | hs);
    cpu->z_flag = cpu->c == 0;
    cpu->pc += 2;
    return 8;
}
int swapD(CPU* cpu)
{
    uint8_t hs = cpu->d >> 4;
    uint8_t ls = cpu->d & 0xf;

    cpu->d = static_cast<uint8_t>((ls << 4) | hs);
    cpu->z_flag = cpu->d == 0;
    cpu->pc += 2;
    return 8;
}
int swapE(CPU* cpu)
{
    uint8_t hs = cpu->e >> 4;
    uint8_t ls = cpu->e & 0xf;

    cpu->e = static_cast<uint8_t>((ls << 4) | hs);
    cpu->z_flag = cpu->e == 0;
    cpu->pc += 2;
    return 8;
}
int swapH(CPU* cpu)
{
    uint8_t hs = cpu->h >> 4;
    uint8_t ls = cpu->h & 0xf;

    cpu->h = static_cast<uint8_t>((ls << 4) | hs);
    cpu->z_flag = cpu->h == 0;
    cpu->pc += 2;
    return 8;
}
int swapL(CPU* cpu)
{
    uint8_t hs = cpu->l >> 4;
    uint8_t ls = cpu->l & 0xf;

    cpu->l = static_cast<uint8_t>((ls << 4) | hs);
    cpu->z_flag = cpu->l == 0;
    cpu->pc += 2;
    return 8;
}
int swap_HL_(CPU* cpu)
{
    uint16_t address = (cpu->h << 8) | cpu->l;
    uint8_t value = cpu->mmu->read(address);
    uint8_t hs = value >> 4;
    uint8_t ls = value & 0xf;

    value = static_cast<uint8_t>((ls << 4) | hs);
    cpu->mmu->write(address, value);
    cpu->z_flag = value == 0;
    cpu->pc += 2;
    return 16;
}
int swapA(CPU* cpu)
{
    uint8_t hs = cpu->a >> 4;
    uint8_t ls = cpu->a & 0xf;

    cpu->a = static_cast<uint8_t>((ls << 4) | hs);
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 2;
    return 8;
}

int srlB(CPU* cpu)
{
    cpu->c_flag = readBit(0, cpu->b);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->b = cpu->b >> 1;
    cpu->z_flag = cpu->b == 0;
    cpu->pc += 2;

    return 8;
}
int srlC(CPU* cpu)
{
    cpu->c_flag = readBit(0, cpu->c);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->c = cpu->c >> 1;
    cpu->z_flag = cpu->c == 0;
    cpu->pc += 2;

    return 8;
}
int srlD(CPU* cpu)
{
    cpu->c_flag = readBit(0, cpu->d);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->d = cpu->d >> 1;
    cpu->z_flag = cpu->d == 0;
    cpu->pc += 2;

    return 8;
}
int srlE(CPU* cpu)
{
    cpu->c_flag = readBit(0, cpu->e);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->e = cpu->e >> 1;
    cpu->z_flag = cpu->e == 0;
    cpu->pc += 2;

    return 8;
}
int srlH(CPU* cpu)
{
    cpu->c_flag = readBit(0, cpu->h);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->h = cpu->h >> 1;
    cpu->z_flag = cpu->h == 0;
    cpu->pc += 2;

    return 8;
}
int srlL(CPU* cpu)
{
    cpu->c_flag = readBit(0, cpu->l);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->l = cpu->l >> 1;
    cpu->z_flag = cpu->l == 0;
    cpu->pc += 2;

    return 8;
}
int srl_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);
    cpu->c_flag = readBit(0, value);
    cpu->h_flag = cpu->n_flag = 0;

    value = value >> 1;
    cpu->mmu->write(address, value);
    cpu->z_flag = value == 0;
    cpu->pc += 2;

    return 16;
}
int srlA(CPU* cpu)
{
    cpu->c_flag = readBit(0, cpu->a);
    cpu->h_flag = cpu->n_flag = 0;
    cpu->a = cpu->a >> 1;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 2;

    return 8;
}
