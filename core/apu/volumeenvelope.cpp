#include "volumeenvelope.h"

VolumeEnvelope::VolumeEnvelope()
{
}

void VolumeEnvelope::connect(SquareWaveChannel* channel)
{
    waveChannel = channel;
}

void VolumeEnvelope::tick()
{
    if (waveChannel == nullptr)
        throw "The volume envelope component must be connected to a wave channel";
    if (period == 0)
        return;
    --timerCounter;

    if (timerCounter > 0)
        return;

    timerCounter = period;

    uint8_t newVolume = calculateNewVolume();
    if (newVolume > 15)
        return;

    waveChannel->setVolume(newVolume);
}

uint8_t VolumeEnvelope::calculateNewVolume()
{
    return waveChannel->getVolume() + directionCoefficient;
}

void VolumeEnvelope::trigger()
{
    timerCounter = period;
    waveChannel->setVolume(initialVolume);
}
