#include "arithmetic.h"
#include "core/utils.h"
#include "spdlog/spdlog.h"
#include <iostream>
using namespace std;

int incB(CPU* cpu)
{
    COUT << "INC B" << endl;
    uint8_t lowB = cpu->b & 0xf;

    cpu->b += 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->b == 0);
    cpu->n_flag = 0;
    cpu->h_flag = static_cast<uint8_t>(lowB > (cpu->b & 0xf));

    cpu->pc += 1;
    return 4;
}

int incD(CPU* cpu)
{
    COUT << "INC D" << endl;
    uint8_t lowD = cpu->d & 0xf;

    cpu->d += 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->d == 0);
    cpu->n_flag = 0;
    cpu->h_flag = static_cast<uint8_t>(lowD > (cpu->d & 0xf));

    cpu->pc += 1;
    return 4;
}

int incH(CPU* cpu)
{
    COUT << "INC H" << endl;
    uint8_t lowH = cpu->h & 0xf;

    cpu->h += 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->h == 0);
    cpu->n_flag = 0;
    cpu->h_flag = static_cast<uint8_t>(lowH > (cpu->h & 0xf));

    cpu->pc += 1;
    return 4;
}

int inc_HL_(CPU* cpu)
{
    COUT << "INC (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);
    uint8_t lowValue = value & 0xf;

    value += 1;
    cpu->mmu->write(address, value);
    cpu->z_flag = static_cast<uint8_t>(value == 0);
    cpu->n_flag = 0;
    cpu->h_flag = static_cast<uint8_t>(lowValue > (value & 0xf));

    cpu->pc += 1;
    return 12;
}

int incC(CPU* cpu)
{
    COUT << "INC C" << endl;
    uint8_t lowC = cpu->c & 0xf;

    cpu->c += 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->c == 0);
    cpu->n_flag = 0;
    cpu->h_flag = static_cast<uint8_t>(lowC > (cpu->c & 0xf));

    cpu->pc += 1;
    return 4;
}

int incE(CPU* cpu)
{
    COUT << "INC E" << endl;
    uint8_t new_h_flag = (((cpu->e & 0xf) + 1) & 0x10) != 0;
    uint8_t lowE = cpu->e & 0xf;

    cpu->e += 1;
    cpu->z_flag = cpu->e == 0;
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;

    cpu->pc += 1;
    return 4;
}

int incL(CPU* cpu)
{
    COUT << "INC L" << endl;
    uint8_t lowL = cpu->l & 0xf;

    cpu->l += 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->l == 0);
    cpu->n_flag = 0;
    cpu->h_flag = static_cast<uint8_t>(lowL > (cpu->l & 0xf));

    cpu->pc += 1;
    return 4;
}

int incA(CPU* cpu)
{
    COUT << "INC A" << endl;
    uint8_t lowA = cpu->a & 0xf;

    cpu->a += 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = static_cast<uint8_t>(lowA > (cpu->a & 0xf));

    cpu->pc += 1;
    return 4;
}

int decB(CPU* cpu)
{
    COUT << "DEC B" << endl;
    uint8_t new_h_flag = (cpu->b & 0xf) < 1;

    cpu->b -= 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->b == 0);
    cpu->n_flag = 1;
    cpu->h_flag = new_h_flag;

    cpu->pc += 1;
    return 4;
}

int decD(CPU* cpu)
{
    COUT << "DEC D" << endl;
    uint8_t new_h_flag = static_cast<uint8_t>((cpu->d & 0xf) < 1);

    cpu->d -= 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->d == 0);
    cpu->n_flag = 1;
    cpu->h_flag = new_h_flag;

    cpu->pc += 1;
    return 4;
}

int decH(CPU* cpu)
{
    COUT << "DEC H" << endl;
    uint8_t lowH = cpu->h & 0xf;

    cpu->h -= 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->h == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(lowH < (cpu->h & 0xf));

    cpu->pc += 1;
    return 4;
}

int dec_HL_(CPU* cpu)
{
    COUT << "DEC (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t value = cpu->mmu->read(address);
    uint8_t lowValue = value & 0xf;

    value -= 1;
    cpu->mmu->write(address, value);
    cpu->z_flag = static_cast<uint8_t>(value == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(lowValue > (value & 0xf));

    cpu->pc += 1;
    return 12;
}

int decC(CPU* cpu)
{
    COUT << "DEC C" << endl;
    uint8_t new_h_flag = (cpu->c & 0xf) < 1;

    cpu->c -= 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->c == 0);
    cpu->n_flag = 1;
    cpu->h_flag = new_h_flag;

    cpu->pc += 1;
    return 4;
}

int decE(CPU* cpu)
{
    COUT << "DEC E" << endl;
    uint8_t lowE = cpu->e & 0xf;

    cpu->e -= 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->e == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(lowE < (cpu->e & 0xf));

    cpu->pc += 1;
    return 4;
}

int decL(CPU* cpu)
{
    COUT << "DEC L" << endl;
    uint8_t lowL = cpu->l & 0xf;

    cpu->l -= 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->l == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(lowL < (cpu->l & 0xf));

    cpu->pc += 1;
    return 4;
}

int decA(CPU* cpu)
{
    COUT << "DEC A" << endl;
    uint8_t lowA = cpu->a & 0xf;

    cpu->a -= 1;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(lowA < (cpu->a & 0xf));

    cpu->pc += 1;
    return 4;
}

int CPL(CPU* cpu)
{
    cpu->a = 255 - cpu->a;
    cpu->h_flag = 1;
    cpu->n_flag = 1;

    cpu->pc += 1;
    return 4;
}
int CCF(CPU* cpu)
{
    cpu->c_flag = 1 - cpu->c_flag;
    cpu->h_flag = 0;
    cpu->n_flag = 0;
    cpu->pc += 1;
    return 4;
}

int addAB(CPU* cpu)
{
    COUT << "ADD A,B" << endl;
    uint8_t new_h_flag = (((cpu->b & 0xf) + (cpu->a & 0xf)) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + cpu->b) & 0x100) != 0;

    cpu->a += cpu->b;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;
    return 4;
}

int addAC(CPU* cpu)
{
    uint8_t new_h_flag = (((cpu->c & 0xf) + (cpu->a & 0xf)) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + cpu->c) & 0x100) != 0;

    cpu->a += cpu->c;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;
    return 4;
}
int addAD(CPU* cpu)
{
    COUT << "ADD A,D" << endl;
    uint8_t new_h_flag = (((cpu->d & 0xf) + (cpu->a & 0xf)) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + cpu->d) & 0x100) != 0;

    cpu->a += cpu->d;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;
    return 4;
}
int addAE(CPU* cpu)
{
    COUT << "ADD A,E" << endl;
    uint8_t new_h_flag = (((cpu->e & 0xf) + (cpu->a & 0xf)) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + cpu->e) & 0x100) != 0;

    cpu->a += cpu->e;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;
    return 4;
}
int addAH(CPU* cpu)
{
    COUT << "ADD A,H" << endl;
    uint8_t new_h_flag = (((cpu->h & 0xf) + (cpu->a & 0xf)) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + cpu->h) & 0x100) != 0;

    cpu->a += cpu->h;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;
    return 4;
}
int addAL(CPU* cpu)
{
    COUT << "ADD A,L" << endl;
    uint8_t new_h_flag = (((cpu->l & 0xf) + (cpu->a & 0xf)) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + cpu->l) & 0x100) != 0;

    cpu->a += cpu->l;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;
    return 4;
}
int addA_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t n = cpu->mmu->read(address);
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf)) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n) & 0x100) != 0;

    cpu->a += n;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;
    return 8;
}
int addAA(CPU* cpu)
{
    uint8_t new_h_flag = (((cpu->a & 0xf) + (cpu->a & 0xf)) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + cpu->a) & 0x100) != 0;

    cpu->a += cpu->a;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;
    COUT << "Double A = " << hex << unsigned(cpu->a) << endl;
    return 4;
}

int adcAB(CPU* cpu)
{
    uint8_t n = cpu->b;
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf) + cpu->c_flag) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n + cpu->c_flag) & 0x100) != 0;

    cpu->a += (n + cpu->c_flag);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 1;
    return 4;
}
int adcAC(CPU* cpu)
{
    uint8_t n = cpu->c;
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf) + cpu->c_flag) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n + cpu->c_flag) & 0x100) != 0;

    cpu->a += (n + cpu->c_flag);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 1;
    return 4;
}
int adcAD(CPU* cpu)
{
    uint8_t n = cpu->d;
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf) + cpu->c_flag) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n + cpu->c_flag) & 0x100) != 0;

    cpu->a += (n + cpu->c_flag);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 1;
    return 4;
}
int adcAE(CPU* cpu)
{
    uint8_t n = cpu->e;
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf) + cpu->c_flag) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n + cpu->c_flag) & 0x100) != 0;

    cpu->a += (n + cpu->c_flag);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 1;
    return 4;
}
int adcAH(CPU* cpu)
{
    uint8_t n = cpu->h;
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf) + cpu->c_flag) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n + cpu->c_flag) & 0x100) != 0;

    cpu->a += (n + cpu->c_flag);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 1;
    return 4;
}
int adcAL(CPU* cpu)
{
    uint8_t n = cpu->l;
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf) + cpu->c_flag) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n + cpu->c_flag) & 0x100) != 0;

    cpu->a += (n + cpu->c_flag);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 1;
    return 4;
}
int adcA_HL_(CPU* cpu)
{
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t n = cpu->mmu->read(address);
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf) + cpu->c_flag) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n + cpu->c_flag) & 0x100) != 0;

    cpu->a += (n + cpu->c_flag);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 1;
    return 8;
}
int adcAA(CPU* cpu)
{
    uint8_t n = cpu->a;
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf) + cpu->c_flag) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n + cpu->c_flag) & 0x100) != 0;

    cpu->a += (n + cpu->c_flag);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 1;
    return 4;
}

int subAB(CPU* cpu)
{
    COUT << "SUB B" << endl;
    cpu->z_flag = static_cast<uint8_t>(cpu->b == cpu->a);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(cpu->b & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>(cpu->b > cpu->a);

    cpu->a -= cpu->b;

    cpu->pc += 1;
    return 4;
}
int subAC(CPU* cpu)
{
    COUT << "SUB C" << endl;
    cpu->z_flag = static_cast<uint8_t>(cpu->c == cpu->a);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(cpu->c & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>(cpu->c > cpu->a);

    cpu->a -= cpu->c;

    cpu->pc += 1;
    return 4;
}
int subAD(CPU* cpu)
{
    COUT << "SUB D" << endl;
    cpu->z_flag = static_cast<uint8_t>(cpu->d == cpu->a);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(cpu->d & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>(cpu->d > cpu->a);

    cpu->a -= cpu->d;

    cpu->pc += 1;
    return 4;
}
int subAE(CPU* cpu)
{
    COUT << "SUB E" << endl;
    cpu->z_flag = static_cast<uint8_t>(cpu->e == cpu->a);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(cpu->e & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>(cpu->e > cpu->a);

    cpu->a -= cpu->e;

    cpu->pc += 1;
    return 4;
}
int subAH(CPU* cpu)
{
    COUT << "SUB H" << endl;
    cpu->z_flag = static_cast<uint8_t>(cpu->h == cpu->a);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(cpu->h & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>(cpu->h > cpu->a);

    cpu->a -= cpu->h;

    cpu->pc += 1;
    return 4;
}
int subAL(CPU* cpu)
{
    COUT << "SUB L" << endl;
    cpu->z_flag = static_cast<uint8_t>(cpu->l == cpu->a);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(cpu->l & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>(cpu->l > cpu->a);

    cpu->a -= cpu->l;

    cpu->pc += 1;
    return 4;
}
int subA_HL_(CPU* cpu)
{
    COUT << "SUB (HL)" << endl;
    uint16_t address = (cpu->h << 8) | cpu->l;
    uint8_t n = cpu->mmu->read(address);
    cpu->z_flag = static_cast<uint8_t>(n == cpu->a);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(n & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->a -= n;

    cpu->pc += 1;
    return 8;
}
int subAA(CPU* cpu)
{
    COUT << "SUB A" << endl;
    cpu->z_flag = 1;
    cpu->n_flag = 1;
    cpu->h_flag = 0;
    cpu->c_flag = 0;

    cpu->a -= cpu->a;

    cpu->pc += 1;
    return 4;
}

int sbcAB(CPU* cpu)
{
    COUT << "SBC B" << endl;
    cpu->z_flag = static_cast<uint8_t>((cpu->a - cpu->b - cpu->c_flag) == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((cpu->b + cpu->c_flag) & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>((cpu->b + cpu->c_flag) > cpu->a);

    cpu->a -= (cpu->b + cpu->c_flag);

    cpu->pc += 1;
    return 4;
}
int sbcAC(CPU* cpu)
{
    COUT << "SBC C" << endl;
    cpu->z_flag = static_cast<uint8_t>((cpu->a - cpu->c - cpu->c_flag) == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((cpu->c + cpu->c_flag) & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>((cpu->c + cpu->c_flag) > cpu->a);

    cpu->a -= (cpu->c + cpu->c_flag);

    cpu->pc += 1;
    return 4;
}
int sbcAD(CPU* cpu)
{
    COUT << "SBC D" << endl;
    cpu->z_flag = static_cast<uint8_t>((cpu->a - cpu->d - cpu->c_flag) == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((cpu->d + cpu->c_flag) & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>((cpu->d + cpu->c_flag) > cpu->a);

    cpu->a -= (cpu->d + cpu->c_flag);

    cpu->pc += 1;
    return 4;
}
int sbcAE(CPU* cpu)
{
    COUT << "SBC E" << endl;
    cpu->z_flag = static_cast<uint8_t>((cpu->a - cpu->e - cpu->c_flag) == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((cpu->e + cpu->c_flag) & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>((cpu->e + cpu->c_flag) > cpu->a);

    cpu->a -= (cpu->e + cpu->c_flag);

    cpu->pc += 1;
    return 4;
}
int sbcAH(CPU* cpu)
{
    COUT << "SBC H" << endl;
    cpu->z_flag = static_cast<uint8_t>((cpu->a - cpu->h - cpu->c_flag) == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((cpu->h + cpu->c_flag) & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>((cpu->h + cpu->c_flag) > cpu->a);

    cpu->a -= (cpu->h + cpu->c_flag);

    cpu->pc += 1;
    return 4;
}
int sbcAL(CPU* cpu)
{
    COUT << "SBC L" << endl;
    cpu->z_flag = static_cast<uint8_t>((cpu->a - cpu->l - cpu->c_flag) == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((cpu->l + cpu->c_flag) & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>((cpu->l + cpu->c_flag) > cpu->a);

    cpu->a -= (cpu->l + cpu->c_flag);

    cpu->pc += 1;
    return 4;
}
int sbcA_HL_(CPU* cpu)
{
    COUT << "SBC (HL)" << endl;
    uint16_t address = (cpu->h << 8) | cpu->l;
    uint8_t n = cpu->mmu->read(address);
    cpu->z_flag = static_cast<uint8_t>((cpu->a - n - cpu->c_flag) == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((n + cpu->c_flag) & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>((n + cpu->c_flag) > cpu->a);

    cpu->a -= (n + cpu->c_flag);

    cpu->pc += 1;
    return 8;
}
int sbcAA(CPU* cpu)
{
    COUT << "SBC A" << endl;
    cpu->z_flag = static_cast<uint8_t>((cpu->a - cpu->a - cpu->c_flag) == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((cpu->a + cpu->c_flag) & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>((cpu->a + cpu->c_flag) > cpu->a);

    cpu->a -= (cpu->a + cpu->c_flag);

    cpu->pc += 1;
    return 4;
}

int andB(CPU* cpu)
{
    cpu->a &= cpu->b;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int andC(CPU* cpu)
{
    cpu->a &= cpu->c;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int andD(CPU* cpu)
{
    cpu->a &= cpu->d;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int andE(CPU* cpu)
{
    cpu->a &= cpu->e;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int andH(CPU* cpu)
{
    cpu->a &= cpu->h;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int andL(CPU* cpu)
{
    cpu->a &= cpu->l;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int and_HL_(CPU* cpu);
int andA(CPU* cpu)
{
    //    Z - Set if result is zero.
    //    N - Reset.
    //    H - Set.
    //    C - Reset.
    cpu->a &= cpu->a;
    cpu->z_flag = cpu->a == 0;
    cpu->n_flag = 0;
    cpu->h_flag = 1;
    cpu->c_flag = 0;
    cpu->pc += 1;
    return 4;
}

int xorB(CPU* cpu)
{
    cpu->a = cpu->a ^ cpu->b;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int xorC(CPU* cpu)
{
    cpu->a = cpu->a ^ cpu->c;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int xorD(CPU* cpu)
{
    cpu->a = cpu->a ^ cpu->d;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int xorE(CPU* cpu)
{
    cpu->a = cpu->a ^ cpu->e;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int xorH(CPU* cpu)
{
    cpu->a = cpu->a ^ cpu->h;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int xorL(CPU* cpu)
{
    cpu->a = cpu->a ^ cpu->l;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 4;
}
int xor_HL_(CPU* cpu)
{
    uint16_t address = (cpu->h << 8) | cpu->l;
    uint8_t n = cpu->mmu->read(address);
    cpu->a = cpu->a ^ n;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 1;
    return 8;
}
int xorA(CPU* cpu)
{
    COUT << "XOR A" << endl;
    cpu->a = 0;
    // set flags
    cpu->z_flag = 1;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;

    cpu->pc += 1;
    return 4;
}

int orB(CPU* cpu)
{
    COUT << "OR B" << endl;
    cpu->a = cpu->a | cpu->b;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = cpu->h_flag = cpu->c_flag = 0;

    cpu->pc += 1;
    return 4;
}
int orC(CPU* cpu)
{
    COUT << "OR C" << endl;
    cpu->a = cpu->a | cpu->c;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = cpu->h_flag = cpu->c_flag = 0;

    cpu->pc += 1;
    return 4;
}
int orD(CPU* cpu)
{
    COUT << "OR D" << endl;
    cpu->a = cpu->a | cpu->d;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = cpu->h_flag = cpu->c_flag = 0;

    cpu->pc += 1;
    return 4;
}
int orE(CPU* cpu)
{
    COUT << "ORE D" << endl;
    cpu->a = cpu->a | cpu->e;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = cpu->h_flag = cpu->c_flag = 0;

    cpu->pc += 1;
    return 4;
}
int orH(CPU* cpu)
{
    COUT << "OR HD" << endl;
    cpu->a = cpu->a | cpu->h;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = cpu->h_flag = cpu->c_flag = 0;

    cpu->pc += 1;
    return 4;
}
int orL(CPU* cpu)
{
    COUT << "OR L" << endl;
    cpu->a = cpu->a | cpu->l;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = cpu->h_flag = cpu->c_flag = 0;

    cpu->pc += 1;
    return 4;
}
int or_HL_(CPU* cpu)
{
    COUT << "OR (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    cpu->a = cpu->a | cpu->mmu->read(address);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = cpu->h_flag = cpu->c_flag = 0;

    cpu->pc += 1;
    return 8;
}

int orA(CPU* cpu)
{
    COUT << "OR A" << endl;
    cpu->z_flag = cpu->a == 0;
    cpu->n_flag = cpu->h_flag = cpu->c_flag = 0;

    cpu->pc += 1;
    return 4;
}

int cpB(CPU* cpu)
{
    uint8_t n = cpu->b;
    uint8_t r = cpu->a - n;

    cpu->z_flag = static_cast<uint8_t>(r == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((n & 0xf) > (cpu->a & 0xf));
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->pc += 1;
    return 4;
}
int cpC(CPU* cpu)
{
    uint8_t n = cpu->c;
    uint8_t r = cpu->a - n;

    cpu->z_flag = static_cast<uint8_t>(r == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((n & 0xf) > (cpu->a & 0xf));
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->pc += 1;
    return 4;
}
int cpD(CPU* cpu)
{
    uint8_t n = cpu->d;
    uint8_t r = cpu->a - n;

    cpu->z_flag = static_cast<uint8_t>(r == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((n & 0xf) > (cpu->a & 0xf));
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->pc += 1;
    return 4;
}
int cpE(CPU* cpu)
{
    uint8_t n = cpu->e;
    uint8_t r = cpu->a - n;

    cpu->z_flag = static_cast<uint8_t>(r == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((n & 0xf) > (cpu->a & 0xf));
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->pc += 1;
    return 4;
}
int cpH(CPU* cpu)
{
    uint8_t n = cpu->h;
    uint8_t r = cpu->a - n;

    cpu->z_flag = static_cast<uint8_t>(r == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((n & 0xf) > (cpu->a & 0xf));
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->pc += 1;
    return 4;
}
int cpL(CPU* cpu)
{
    uint8_t n = cpu->l;
    uint8_t r = cpu->a - n;

    cpu->z_flag = static_cast<uint8_t>(r == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((n & 0xf) > (cpu->a & 0xf));
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->pc += 1;
    return 4;
}
int cp_HL_(CPU* cpu)
{
    COUT << "CP (HL)" << endl;
    uint16_t address = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t n = cpu->mmu->read(address);
    uint8_t r = cpu->a - n;

    cpu->z_flag = static_cast<uint8_t>(r == 0);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((n & 0xf) > (cpu->a & 0xf));
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->pc += 1;
    return 8;
}
int cpA(CPU* cpu)
{
    cpu->z_flag = 0;
    cpu->n_flag = 1;
    cpu->h_flag = 0;
    cpu->c_flag = 0;

    cpu->pc += 1;
    return 4;
}

int addAn(CPU* cpu)
{
    COUT << "ADD A,n" << endl;
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    uint8_t new_h_flag = (((n & 0xf) + (cpu->a & 0xf)) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n) & 0x100) != 0;

    cpu->a += n;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 2;
    return 8;
}
int subAn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "SUB A,n" << endl;
    cpu->z_flag = static_cast<uint8_t>(cpu->b == cpu->a);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>(n & 0xf) > (cpu->a & 0xf);
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->a -= n;

    cpu->pc += 2;
    return 8;
}
int andn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);

    cpu->a = cpu->a & n;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = 1;
    cpu->c_flag = 0;
    cpu->pc += 2;
    return 8;
}
int orn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "OR " << hex << unsigned(n) << endl;
    cpu->a = cpu->a | n;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = cpu->h_flag = cpu->c_flag = 0;

    cpu->pc += 2;
    return 8;
}

int adcAn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    uint8_t new_h_flag = (((cpu->a & 0xf) + (n & 0xf) + cpu->c_flag) & 0x10) != 0;
    uint8_t new_c_flag = ((cpu->a + n + cpu->c_flag) & 0x100) != 0;

    cpu->a += (n + cpu->c_flag);
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->n_flag = 0;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;

    cpu->pc += 2;
    return 8;
}
int sbcAn(CPU* cpu);
int xorn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "XOR " << hex << unsigned(n) << endl;

    cpu->a = cpu->a ^ n;
    cpu->n_flag = 0;
    cpu->h_flag = 0;
    cpu->c_flag = 0;
    cpu->z_flag = cpu->a == 0;
    cpu->pc += 2;
    return 8;
}
int cpn(CPU* cpu)
{
    uint8_t n = cpu->mmu->read(cpu->pc + 1);
    COUT << "CP " << hex << unsigned(n) << endl;

    cpu->z_flag = static_cast<uint8_t>(cpu->a == n);
    cpu->n_flag = 1;
    cpu->h_flag = static_cast<uint8_t>((n & 0xf) > (cpu->a & 0xf));
    cpu->c_flag = static_cast<uint8_t>(n > cpu->a);

    cpu->pc += 2;
    return 8;
}

// 16bit arithmetic
int incBC(CPU* cpu)
{
    COUT << "INC BC" << endl;
    uint16_t bc = static_cast<uint16_t>((cpu->b << 8) | cpu->c);
    bc += 1;
    cpu->b = bc >> 8;
    cpu->c = bc & 0xff;
    cpu->pc += 1;
    return 8;
}

int incDE(CPU* cpu)
{
    COUT << "INC DE" << endl;
    uint16_t de = static_cast<uint16_t>((cpu->d << 8) | cpu->e);
    de += 1;
    cpu->d = de >> 8;
    cpu->e = de & 0xff;
    cpu->pc += 1;
    return 8;
}

int incHL(CPU* cpu)
{
    COUT << "INC HL" << endl;
    uint16_t hl = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    hl += 1;
    cpu->h = hl >> 8;
    cpu->l = hl & 0xff;
    cpu->pc += 1;
    return 8;
}

int incSP(CPU* cpu)
{
    COUT << "INC SP" << endl;
    cpu->sp += 1;
    cpu->pc += 1;
    return 8;
}

int addHLBC(CPU* cpu)
{
    uint16_t hl = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint16_t bc = static_cast<uint16_t>((cpu->b << 8) | cpu->c);
    uint8_t new_h_flag = (((hl & 0xfff) + (bc & 0xfff)) & 0x1000) != 0;
    uint8_t new_c_flag = ((hl + bc) & 0x10000) != 0;

    hl += bc;
    cpu->h = hl >> 8;
    cpu->l = hl & 0xff;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    if (cpu->pc == 0x6983) {
        dumpCPU(cpu);
    }
    cpu->pc += 1;

    return 8;
}
int addHLDE(CPU* cpu)
{
    uint16_t hl = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint16_t de = static_cast<uint16_t>((cpu->d << 8) | cpu->e);
    uint8_t new_h_flag = (((hl & 0xfff) + (de & 0xfff)) & 0x1000) != 0;
    uint8_t new_c_flag = ((hl + de) & 0x10000) != 0;

    hl += de;
    cpu->h = hl >> 8;
    cpu->l = hl & 0xff;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;

    return 8;
}
int addHLHL(CPU* cpu)
{
    uint16_t hl = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t new_h_flag = (((hl & 0xfff) + (hl & 0xfff)) & 0x1000) != 0;
    uint8_t new_c_flag = ((hl + hl) & 0x10000) != 0;

    hl += hl;
    cpu->h = hl >> 8;
    cpu->l = hl & 0xff;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;

    return 8;
}
int addHLSP(CPU* cpu)
{
    uint16_t hl = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    uint8_t new_h_flag = (((hl & 0xfff) + (cpu->sp & 0xfff)) & 0x1000) != 0;
    uint8_t new_c_flag = ((hl + cpu->sp) & 0x10000) != 0;

    hl += cpu->sp;
    cpu->h = hl >> 8;
    cpu->l = hl & 0xff;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 1;

    return 8;
}
int addSPe(CPU* cpu)
{
    int8_t e = cpu->mmu->read(cpu->pc + 1);
    uint8_t new_h_flag = (((e & 0xfff) + (cpu->sp & 0xfff)) & 0x1000) != 0;
    uint8_t new_c_flag = ((e + cpu->sp) & 0x10000) != 0;

    cpu->sp += e;
    cpu->h_flag = new_h_flag;
    cpu->c_flag = new_c_flag;
    cpu->pc += 2;

    return 8;
}
int decBC(CPU* cpu)
{
    COUT << "DEC BC" << endl;
    uint16_t bc = static_cast<uint16_t>((cpu->b << 8) | cpu->c);
    bc -= 1;
    cpu->b = bc >> 8;
    cpu->c = bc & 0xff;
    cpu->pc += 1;
    return 8;
}
int decDE(CPU* cpu)
{
    COUT << "DEC DE" << endl;
    uint16_t de = static_cast<uint16_t>((cpu->d << 8) | cpu->e);
    de -= 1;
    cpu->d = de >> 8;
    cpu->e = de & 0xff;
    cpu->pc += 1;
    return 8;
}
int decHL(CPU* cpu)
{
    COUT << "DEC HL" << endl;
    uint16_t hl = static_cast<uint16_t>((cpu->h << 8) | cpu->l);
    hl -= 1;
    cpu->h = hl >> 8;
    cpu->l = hl & 0xff;
    cpu->pc += 1;
    return 8;
}
int decSP(CPU* cpu)
{
    COUT << "DEC SP" << endl;
    cpu->sp -= 1;
    cpu->pc += 1;
    return 8;
}
