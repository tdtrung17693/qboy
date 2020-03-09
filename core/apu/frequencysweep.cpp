#include "frequencysweep.h"

FrequencySweep::FrequencySweep()
{
}

void FrequencySweep::connect(WaveChannel* channel)
{
    waveChannel = channel;
}

void FrequencySweep::tick()
{
    if (!enabled)
        return;

    if (period == 0)
        return;

    timerCounter -= 1;
    if (timerCounter > 0)
        return;

    timerCounter = period;
    uint16_t newFrequency = calculateNewFrequency();

    if (newFrequency >= 0x800) {
        waveChannel->disable();
        return;
    }

    currentFrequency = newFrequency;
    waveChannel->setFrequency(newFrequency);

    if (calculateNewFrequency() >= 0x800) {
        waveChannel->disable();
    }
}

void FrequencySweep::trigger()
{
    //    Square 1's frequency is copied to the shadow register.
    //    The sweep timer is reloaded.
    //    The internal enabled flag is set if either the sweep period or shift are non-zero, cleared otherwise.
    //    If the sweep shift is non-zero, frequency calculation and the overflow check are performed immediately.
    if (waveChannel == nullptr)
        throw "The frequency sweep component must be connected to a wave channel";

    currentFrequency = waveChannel->getFrequency();
    enabled = period > 0 || shiftNumber > 0;
    timerCounter = period;

    if (shiftNumber == 0)
        return;

    if (calculateNewFrequency() >= 0x800) {
        waveChannel->disable();
        return;
    }
}

uint16_t FrequencySweep::calculateNewFrequency()
{
    return static_cast<uint16_t>(currentFrequency + directionCoefficient * (currentFrequency >> shiftNumber));
}
