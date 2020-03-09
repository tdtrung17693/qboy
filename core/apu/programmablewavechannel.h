#ifndef PROGRAMMABLEWAVECHANNEL_H
#define PROGRAMMABLEWAVECHANNEL_H
#include "wavechannel.h"

#include <cstdint>

class ProgrammableWaveChannel : public WaveChannel {
protected:
    int positionCounter = -1;
    uint8_t currentPattern = 0;

    // WaveChannel interface
    void triggerAction();
    void tickAction();
    void resetTimerCounter();

public:
    uint8_t waveTable[16];
    // WaveChannel interface
    float getSignal();
    int volumeControlNumber;
};

#endif // PROGRAMMABLEWAVECHANNEL_H
