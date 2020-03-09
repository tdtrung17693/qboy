#ifndef FREQUENCYSWEEP_H
#define FREQUENCYSWEEP_H
#include "wavechannel.h"
#include <cstdint>

class FrequencySweep {
protected:
    bool enabled;
    int timerCounter;
    WaveChannel* waveChannel;
    uint16_t currentFrequency;

    uint16_t calculateNewFrequency();

public:
    FrequencySweep();
    void connect(WaveChannel*);
    void tick();
    void trigger();
    uint8_t period;
    uint8_t shiftNumber;
    int8_t directionCoefficient;
};

#endif // FREQUENCYSWEEP_H
