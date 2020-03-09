#include "programmablewavechannel.h"
#include <iostream>
#include <math.h>

void ProgrammableWaveChannel::triggerAction()
{
    positionCounter = 0;
}

void ProgrammableWaveChannel::tickAction()
{
    positionCounter = (positionCounter + 1) % 32;
    uint8_t patternIndex = static_cast<uint8_t>(floor(positionCounter / 2));
    uint8_t patternNipplePos = positionCounter % 2;

    currentPattern = (waveTable[patternIndex] >> 4 * (1 - patternNipplePos)) & 0xf;
    //    printf("Current position %d - Pattern index %d - Byte %x - Pattern %x\n", positionCounter, patternIndex, waveTable[patternIndex], currentPattern);
}

void ProgrammableWaveChannel::resetTimerCounter()
{
    timerCounter = (2048 - frequency) * 2;
}

float ProgrammableWaveChannel::getSignal()
{
    if (0 == volumeControlNumber)
        return 0;

    return ((currentPattern >> (volumeControlNumber - 1))) * 1.0 / 15;
}
