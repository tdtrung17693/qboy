#include "core/utils.h"
#include "spdlog/spdlog.h"

uint8_t readBit(uint8_t bitPosition, uint8_t number)
{
    return (number & (1 << bitPosition)) >> bitPosition;
}

uint8_t setBit(uint8_t bitPosition, uint8_t number)
{
    return number | static_cast<uint8_t>(1 << bitPosition);
}

uint8_t resetBit(uint8_t bitPosition, uint8_t number)
{
    return number & (~(1 << bitPosition));
}

void dumpCPU(CPU* cpu)
{
    auto logger = spdlog::get("cpu_logger");

    logger->info(
        "\nCPU Dump\n"
        "A: {:04x}\n"
        "B: {:04x}\n"
        "C: {:04x}\n"
        "D: {:04x}\n"
        "E: {:04x}\n"
        "H: {:04x}\n"
        "L: {:04x}\n"
        "PC: {:04x}\n"
        "SP: {:04x}\n",
        cpu->a, cpu->b, cpu->c, cpu->d, cpu->e, cpu->h, cpu->l, cpu->pc, cpu->sp);
}
