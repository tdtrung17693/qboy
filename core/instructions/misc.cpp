#include "misc.h"
#include <iostream>

using namespace std;

int nop(CPU* cpu)
{
    COUT << "NOP" << endl;
    cpu->pc += 1;
    return 4;
}

int halt(CPU* cpu)
{
    cpu->pc += 1;
    // TODO: implement halt
    return 4;
}

int di(CPU* cpu)
{
    cpu->IME = false;
    cpu->pc += 1;
    return 4;
}

int ei(CPU* cpu)
{
    cpu->willEnableInterrupt = true;
    cpu->pc += 1;
    return 4;
}

int daa(CPU* cpu)
{
    uint8_t ls = cpu->a & 0xf;
    uint8_t ms = cpu->a >> 4;
    if (!(ms <= 9 && ls <= 9 && cpu->c_flag == 0 && cpu->h_flag == 0)) {
        if (cpu->n_flag == 0) {
            if (
                (ms <= 8 && ls >= 0xa && ls <= 0xf)
                || (ms <= 9 && ls <= 3 && cpu->h_flag == 1)) {
                cpu->a += 0x06;
            } else if (
                (ms <= 0xf && ms >= 0xa && ls <= 0x9)
                || (ms <= 0x2 && ls <= 0x9 && cpu->c_flag == 1)) {
                cpu->a += 0x60;
            } else {
                cpu->a += 0x66;
                cpu->c = 1;
            }
        } else if (cpu->n_flag == 1) {
            if (ms <= 8 && ls >= 6 && ls <= 0xf && cpu->h_flag == 1) {
                cpu->a += 0xfa;
            } else if (ms <= 0xf && ms >= 7 && ls <= 9 && cpu->c_flag == 1) {
                cpu->a += 0xa0;
            } else if (ms <= 0xf && ms >= 6 && ls <= 0xf && ls >= 6 && cpu->c_flag == 1) {
                cpu->a += 0x9a;
            }
        }
    }

    cpu->h_flag = 0;
    cpu->z_flag = static_cast<uint8_t>(cpu->a == 0);
    cpu->pc += 1;

    return 4;
}
