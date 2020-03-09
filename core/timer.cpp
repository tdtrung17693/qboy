#include "timer.h"
#include "core/utils.h"
#include <iostream>

const uint16_t Timer::CLOCK_MAP[] = { 1024, 16, 64, 256 };
Timer::Timer()
{
}

void Timer::onTimerOverflow(std::function<void()> fn)
{
    overflowCallbacks.push_back(fn);
}

void Timer::resetValue()
{
    counter = TMA;
}

void Timer::setClock(uint16_t clock)
{
    timerClock = clock;
}

void Timer::update(uint8_t passedCycles)
{
    if (!isOn)
        return;

    timerUpdateCounter -= passedCycles;

    if (timerUpdateCounter > 0)
        return;

    timerUpdateCounter += timerClock;

    countUp();
}

void Timer::connect(MMU* mmu)
{
    mmu->addWriteInterceptor(0xff05, [&](uint8_t value) {
        printf("Load timer with %04x\n", value);
        counter = value;
    });

    mmu->addWriteInterceptor(0xff06, [&](uint8_t value) {
        printf("Load TMA with %04x\n", value);
        TMA = value;
    });

    mmu->addWriteInterceptor(0xff07, [&](uint8_t value) {
        isOn = readBit(2, value);
        clockChoosingValue = value & 0x3;
        if (clockChoosingValue == 0) {
            timerClock = 1024;
        } else if (clockChoosingValue == 1) {
            timerClock = 16;
        } else if (clockChoosingValue == 2) {
            timerClock = 64;
        } else {
            timerClock = 256;
        }
    });

    mmu->addReadInterceptor(0xff05, [&]() {
        return counter;
    });

    mmu->addReadInterceptor(0xff06, [&]() {
        return TMA;
    });

    mmu->addReadInterceptor(0xff07, [&]() {
        return (static_cast<uint8_t>(isOn) << 2) | clockChoosingValue;
    });
}

void Timer::countUp()
{
    if (counter + 1 >= 0xff) {
        resetValue();
        for (auto& fn : overflowCallbacks) {
            fn();
        }
    }

    counter += 1;
}
