#include "squarewavechannel.h"
#include "core/utils.h"
#include <math.h>

const std::vector<uint8_t> SquareWaveChannel::DUTY_MAP = { 0x1, 0x81, 0x87, 0x7e };

void SquareWaveChannel::resetTimerCounter()
{
    timerCounter = (2048 - frequency) * 4;
}

void SquareWaveChannel::tickAction()
{
    step += 1;
    step %= 8;
}

float SquareWaveChannel::getSignal()
{
    if (!enabled)
        return 0;
    uint8_t stepBit = readBit(7 - step, DUTY_MAP[duty]);

    //    printf("Channel %d - Duty %d - Step %d - Bit %d\n", number, duty, step, stepBit);
    return stepBit * static_cast<double>(getVolume()) / 15.0;
}

void SquareWaveChannel::setDuty(uint8_t duty)
{
    if (duty > 3)
        throw "Invalid duty";

    this->duty = duty;
}
