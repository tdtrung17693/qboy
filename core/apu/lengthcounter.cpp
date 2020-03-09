#include "lengthcounter.h"

void LengthCounter::tick()
{
    if (waveChannel == nullptr)
        throw "The length counter component must be connected to a wave channel";

    if (!enabled)
        return;

    --counter;
    if (counter > 0)
        return;

    waveChannel->disable();
    disable();
}

void LengthCounter::loadCounter(int data)
{
    counter = data;
}

void LengthCounter::disable()
{
    enabled = false;
}

void LengthCounter::enable()
{
    enabled = true;
}

void LengthCounter::connect(WaveChannel* waveChannel)
{
    this->waveChannel = waveChannel;
}

void LengthCounter::trigger()
{
    if (counter == 0)
        counter = defaultData;
}

void LengthCounter::setDefaultCounter(int data)
{
    defaultData = data;
}
