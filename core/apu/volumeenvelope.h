#ifndef VOLUMEENVELOPE_H
#define VOLUMEENVELOPE_H
#include "squarewavechannel.h"

#include <functional>
class VolumeEnvelope {
protected:
    int timerCounter = 0;
    SquareWaveChannel* waveChannel;
    uint8_t calculateNewVolume();

public:
    VolumeEnvelope();
    void connect(SquareWaveChannel*);
    void tick();
    void trigger();
    uint8_t period = 0;
    uint8_t initialVolume = 0;
    int8_t directionCoefficient;
};

#endif // VOLUMEENVELOPE_H
