#include "wavechannel.h"

WaveChannel::~WaveChannel() {}
uint16_t WaveChannel::getFrequency()
{
    return frequency;
}

uint8_t WaveChannel::getVolume()
{
    return volume;
}

void WaveChannel::setFrequency(uint16_t newFrequency)
{
    frequency = newFrequency;
}

void WaveChannel::setVolume(uint8_t newVolume)
{
    volume = newVolume;
}

bool WaveChannel::isEnable()
{
    return enabled;
}

void WaveChannel::trigger()
{
    //    Writing a value to NRx4 with bit 7 set causes the following things to occur:

    //    Channel is enabled (see length counter).
    //    If length counter is zero, it is set to 64 (256 for wave channel).
    //    Frequency timer is reloaded with period.
    //    Volume envelope timer is reloaded with period.
    //    Channel volume is reloaded from NRx2.
    //    Noise channel's LFSR bits are all set to 1.
    //    Wave channel's position is set to 0 but sample buffer is NOT refilled.
    //    Square 1's sweep does several things (see frequency sweep).
    //    Note that if the channel's DAC is off, after the above actions occur the channel will be immediately disabled again.
    enable();
    resetTimerCounter();
    triggerAction();
}

void WaveChannel::tick()
{
    if (!enabled)
        return;

    --timerCounter;
    if (timerCounter > 0)
        return;

    resetTimerCounter();
    tickAction();
}
void WaveChannel::enable()
{
    enabled = true;
}

void WaveChannel::disable()
{
    enabled = false;
}
