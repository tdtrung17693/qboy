#include "bitwise.h"
#include "core/utils.h"
#include <iostream>

using namespace std;

// check bit
int bit0A(CPU* cpu)
{
    COUT << "BIT " << unsigned(0) << ", A" << endl;
    uint8_t bit = readBit(0, cpu->a);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit1A(CPU* cpu)
{
    COUT << "BIT " << unsigned(1) << ", A" << endl;
    uint8_t bit = readBit(1, cpu->a);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit2A(CPU* cpu)
{
    COUT << "BIT " << unsigned(2) << ", A" << endl;
    uint8_t bit = readBit(2, cpu->a);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit3A(CPU* cpu)
{
    COUT << "BIT " << unsigned(3) << ", A" << endl;
    uint8_t bit = readBit(3, cpu->a);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit4A(CPU* cpu)
{
    COUT << "BIT " << unsigned(4) << ", A" << endl;
    uint8_t bit = readBit(4, cpu->a);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit5A(CPU* cpu)
{
    COUT << "BIT " << unsigned(5) << ", A" << endl;
    uint8_t bit = readBit(5, cpu->a);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit6A(CPU* cpu)
{
    COUT << "BIT " << unsigned(6) << ", A" << endl;
    uint8_t bit = readBit(6, cpu->a);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit7A(CPU* cpu)
{
    COUT << "BIT " << unsigned(7) << ", A" << endl;
    uint8_t bit = readBit(7, cpu->a);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit0B(CPU* cpu)
{
    COUT << "BIT " << unsigned(0) << ", B" << endl;
    uint8_t bit = readBit(0, cpu->b);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit1B(CPU* cpu)
{
    COUT << "BIT " << unsigned(1) << ", B" << endl;
    uint8_t bit = readBit(1, cpu->b);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit2B(CPU* cpu)
{
    COUT << "BIT " << unsigned(2) << ", B" << endl;
    uint8_t bit = readBit(2, cpu->b);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit3B(CPU* cpu)
{
    COUT << "BIT " << unsigned(3) << ", B" << endl;
    uint8_t bit = readBit(3, cpu->b);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit4B(CPU* cpu)
{
    COUT << "BIT " << unsigned(4) << ", B" << endl;
    uint8_t bit = readBit(4, cpu->b);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit5B(CPU* cpu)
{
    COUT << "BIT " << unsigned(5) << ", B" << endl;
    uint8_t bit = readBit(5, cpu->b);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit6B(CPU* cpu)
{
    COUT << "BIT " << unsigned(6) << ", B" << endl;
    uint8_t bit = readBit(6, cpu->b);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit7B(CPU* cpu)
{
    COUT << "BIT " << unsigned(7) << ", B" << endl;
    uint8_t bit = readBit(7, cpu->b);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit0C(CPU* cpu)
{
    COUT << "BIT " << unsigned(0) << ", C" << endl;
    uint8_t bit = readBit(0, cpu->c);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit1C(CPU* cpu)
{
    COUT << "BIT " << unsigned(1) << ", C" << endl;
    uint8_t bit = readBit(1, cpu->c);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit2C(CPU* cpu)
{
    COUT << "BIT " << unsigned(2) << ", C" << endl;
    uint8_t bit = readBit(2, cpu->c);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit3C(CPU* cpu)
{
    COUT << "BIT " << unsigned(3) << ", C" << endl;
    uint8_t bit = readBit(3, cpu->c);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit4C(CPU* cpu)
{
    COUT << "BIT " << unsigned(4) << ", C" << endl;
    uint8_t bit = readBit(4, cpu->c);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit5C(CPU* cpu)
{
    COUT << "BIT " << unsigned(5) << ", C" << endl;
    uint8_t bit = readBit(5, cpu->c);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit6C(CPU* cpu)
{
    COUT << "BIT " << unsigned(6) << ", C" << endl;
    uint8_t bit = readBit(6, cpu->c);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit7C(CPU* cpu)
{
    COUT << "BIT " << unsigned(7) << ", C" << endl;
    uint8_t bit = readBit(7, cpu->c);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit0D(CPU* cpu)
{
    uint8_t bit = readBit(0, cpu->d);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit1D(CPU* cpu)
{
    uint8_t bit = readBit(1, cpu->d);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit2D(CPU* cpu)
{
    uint8_t bit = readBit(2, cpu->d);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit3D(CPU* cpu)
{
    uint8_t bit = readBit(3, cpu->d);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit4D(CPU* cpu)
{
    uint8_t bit = readBit(4, cpu->d);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit5D(CPU* cpu)
{
    uint8_t bit = readBit(6, cpu->d);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit6D(CPU* cpu)
{
    uint8_t bit = readBit(6, cpu->d);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit7D(CPU* cpu)
{
    uint8_t bit = readBit(7, cpu->d);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit0E(CPU* cpu);
int bit1E(CPU* cpu);
int bit2E(CPU* cpu);
int bit3E(CPU* cpu);
int bit4E(CPU* cpu);
int bit5E(CPU* cpu);
int bit6E(CPU* cpu);
int bit7E(CPU* cpu);

int bit0H(CPU* cpu)
{
    uint8_t bit = readBit(0, cpu->h);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit1H(CPU* cpu)
{
    uint8_t bit = readBit(1, cpu->h);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit2H(CPU* cpu)
{
    uint8_t bit = readBit(2, cpu->h);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit3H(CPU* cpu)
{
    uint8_t bit = readBit(3, cpu->h);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit4H(CPU* cpu)
{
    uint8_t bit = readBit(4, cpu->h);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit5H(CPU* cpu)
{
    uint8_t bit = readBit(5, cpu->h);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}
int bit6H(CPU* cpu)
{
    uint8_t bit = readBit(6, cpu->h);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit7H(CPU* cpu)
{
    uint8_t bit = readBit(7, cpu->h);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 8;
}

int bit0L(CPU* cpu);
int bit1L(CPU* cpu);
int bit2L(CPU* cpu);
int bit3L(CPU* cpu);
int bit4L(CPU* cpu);
int bit5L(CPU* cpu);
int bit6L(CPU* cpu);
int bit7L(CPU* cpu);

int bit0_HL_(CPU* cpu)
{
    COUT << "BIT " << unsigned(0) << ", (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    uint8_t bit = readBit(0, value);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 16;
}
int bit1_HL_(CPU* cpu)
{
    COUT << "BIT " << unsigned(1) << ", (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    uint8_t bit = readBit(1, value);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 16;
}
int bit2_HL_(CPU* cpu)
{
    COUT << "BIT " << unsigned(2) << ", (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    uint8_t bit = readBit(2, value);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 16;
}
int bit3_HL_(CPU* cpu)
{
    COUT << "BIT " << unsigned(3) << ", (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    uint8_t bit = readBit(3, value);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 16;
}
int bit4_HL_(CPU* cpu)
{
    COUT << "BIT " << unsigned(4) << ", (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    uint8_t bit = readBit(4, value);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 16;
}
int bit5_HL_(CPU* cpu)
{
    COUT << "BIT " << unsigned(5) << ", (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    uint8_t bit = readBit(5, value);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 16;
}
int bit6_HL_(CPU* cpu)
{
    COUT << "BIT " << unsigned(6) << ", (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    uint8_t bit = readBit(6, value);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 16;
}
int bit7_HL_(CPU* cpu)
{
    COUT << "BIT " << unsigned(7) << ", (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    uint8_t bit = readBit(7, value);
    cpu->h_flag = 1;
    cpu->n_flag = 0;
    cpu->z_flag = 1 ^ bit;

    cpu->pc += 2;

    return 16;
}

// reset bit

int res0A(CPU* cpu)
{
    cpu->a = resetBit(0, cpu->a);
    cpu->pc += 2;
    return 8;
}
int res1A(CPU* cpu)
{
    cpu->a = resetBit(1, cpu->a);
    cpu->pc += 2;
    return 8;
}
int res2A(CPU* cpu)
{
    cpu->a = resetBit(2, cpu->a);
    cpu->pc += 2;
    return 8;
}
int res3A(CPU* cpu)
{
    cpu->a = resetBit(3, cpu->a);
    cpu->pc += 2;
    return 8;
}
int res4A(CPU* cpu)
{
    cpu->a = resetBit(4, cpu->a);
    cpu->pc += 2;
    return 8;
}
int res5A(CPU* cpu)
{
    cpu->a = resetBit(5, cpu->a);
    cpu->pc += 2;
    return 8;
}
int res6A(CPU* cpu)
{
    cpu->a = resetBit(6, cpu->a);
    cpu->pc += 2;
    return 8;
}
int res7A(CPU* cpu)
{
    cpu->a = resetBit(7, cpu->a);
    cpu->pc += 2;
    return 8;
}

int res0B(CPU* cpu);
int res1B(CPU* cpu);
int res2B(CPU* cpu);
int res3B(CPU* cpu);
int res4B(CPU* cpu);
int res5B(CPU* cpu);
int res6B(CPU* cpu);
int res7B(CPU* cpu);

int res0C(CPU* cpu);
int res1C(CPU* cpu);
int res2C(CPU* cpu);
int res3C(CPU* cpu);
int res4C(CPU* cpu);
int res5C(CPU* cpu);
int res6C(CPU* cpu);
int res7C(CPU* cpu);

int res0D(CPU* cpu);
int res1D(CPU* cpu);
int res2D(CPU* cpu);
int res3D(CPU* cpu);
int res4D(CPU* cpu);
int res5D(CPU* cpu);
int res6D(CPU* cpu);
int res7D(CPU* cpu);

int res0E(CPU* cpu);
int res1E(CPU* cpu);
int res2E(CPU* cpu);
int res3E(CPU* cpu);
int res4E(CPU* cpu);
int res5E(CPU* cpu);
int res6E(CPU* cpu);
int res7E(CPU* cpu);

int res0H(CPU* cpu);
int res1H(CPU* cpu);
int res2H(CPU* cpu);
int res3H(CPU* cpu);
int res4H(CPU* cpu);
int res5H(CPU* cpu);
int res6H(CPU* cpu);
int res7H(CPU* cpu);

int res0L(CPU* cpu);
int res1L(CPU* cpu);
int res2L(CPU* cpu);
int res3L(CPU* cpu);
int res4L(CPU* cpu);
int res5L(CPU* cpu);
int res6L(CPU* cpu);
int res7L(CPU* cpu);

int res0_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, resetBit(0, value));
    cpu->pc += 2;

    return 16;
}
int res1_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, resetBit(1, value));
    cpu->pc += 2;

    return 16;
}
int res2_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, resetBit(2, value));
    cpu->pc += 2;

    return 16;
}
int res3_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, resetBit(3, value));
    cpu->pc += 2;

    return 16;
}
int res4_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, resetBit(4, value));
    cpu->pc += 2;

    return 16;
}
int res5_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, resetBit(5, value));
    cpu->pc += 2;

    return 16;
}
int res6_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, resetBit(6, value));
    cpu->pc += 2;

    return 16;
}
int res7_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, resetBit(7, value));
    cpu->pc += 2;

    return 16;
}

// set bit

int set0A(CPU* cpu);
int set1A(CPU* cpu);
int set2A(CPU* cpu);
int set3A(CPU* cpu);
int set4A(CPU* cpu);
int set5A(CPU* cpu);
int set6A(CPU* cpu);
int set7A(CPU* cpu);

int set0B(CPU* cpu);
int set1B(CPU* cpu);
int set2B(CPU* cpu);
int set3B(CPU* cpu);
int set4B(CPU* cpu);
int set5B(CPU* cpu);
int set6B(CPU* cpu);
int set7B(CPU* cpu);

int set0C(CPU* cpu);
int set1C(CPU* cpu);
int set2C(CPU* cpu);
int set3C(CPU* cpu);
int set4C(CPU* cpu);
int set5C(CPU* cpu);
int set6C(CPU* cpu);
int set7C(CPU* cpu);

int set0D(CPU* cpu);
int set1D(CPU* cpu);
int set2D(CPU* cpu);
int set3D(CPU* cpu);
int set4D(CPU* cpu);
int set5D(CPU* cpu);
int set6D(CPU* cpu);
int set7D(CPU* cpu);

int set0E(CPU* cpu);
int set1E(CPU* cpu);
int set2E(CPU* cpu);
int set3E(CPU* cpu);
int set4E(CPU* cpu);
int set5E(CPU* cpu);
int set6E(CPU* cpu);
int set7E(CPU* cpu);

int set0H(CPU* cpu)
{
    cpu->h = setBit(0, cpu->h);
    cpu->pc += 2;

    return 8;
}
int set1H(CPU* cpu)
{
    cpu->h = setBit(1, cpu->h);
    cpu->pc += 2;

    return 8;
}
int set2H(CPU* cpu)
{
    cpu->h = setBit(2, cpu->h);
    cpu->pc += 2;

    return 8;
}
int set3H(CPU* cpu)
{
    cpu->h = setBit(3, cpu->h);
    cpu->pc += 2;

    return 8;
}
int set4H(CPU* cpu)
{
    cpu->h = setBit(4, cpu->h);
    cpu->pc += 2;

    return 8;
}
int set5H(CPU* cpu)
{
    cpu->h = setBit(5, cpu->h);
    cpu->pc += 2;

    return 8;
}
int set6H(CPU* cpu)
{
    cpu->h = setBit(6, cpu->h);
    cpu->pc += 2;

    return 8;
}
int set7H(CPU* cpu)
{
    cpu->h = setBit(7, cpu->h);
    cpu->pc += 2;

    return 8;
}

int set0L(CPU* cpu);
int set1L(CPU* cpu);
int set2L(CPU* cpu);
int set3L(CPU* cpu);
int set4L(CPU* cpu);
int set5L(CPU* cpu);
int set6L(CPU* cpu);
int set7L(CPU* cpu);

int set0_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, setBit(0, value));
    cpu->pc += 2;

    return 16;
}
int set1_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, setBit(1, value));
    cpu->pc += 2;

    return 16;
}
int set2_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, setBit(2, value));
    cpu->pc += 2;

    return 16;
}
int set3_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, setBit(3, value));
    cpu->pc += 2;

    return 16;
}
int set4_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, setBit(4, value));
    cpu->pc += 2;

    return 16;
}
int set5_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, setBit(5, value));
    cpu->pc += 2;

    return 16;
}
int set6_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, setBit(6, value));
    cpu->pc += 2;

    return 16;
}
int set7_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);

    cpu->mmu->write(address, setBit(7, value));
    cpu->pc += 2;

    return 16;
}
