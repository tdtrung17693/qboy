#ifndef UTILS_H
#define UTILS_H
#include "core/cpu.h"

#include <cstdint>

uint8_t readBit(uint8_t bitPosition, uint8_t number);
uint8_t setBit(uint8_t bitPosition, uint8_t number);
uint8_t resetBit(uint8_t bitPosition, uint8_t number);
void dumpCPU(CPU* cpu);

#endif // UTILS_H
