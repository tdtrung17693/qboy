#ifndef SQUAREWAVECHANNEL_H
#define SQUAREWAVECHANNEL_H

#include "wavechannel.h"

class SquareWaveChannel : public WaveChannel {
protected:
    const static std::vector<uint8_t> DUTY_MAP;
    uint8_t duty = 2;
    uint8_t step;
    void resetTimerCounter();
    void tickAction();

public:
    int number;
    SquareWaveChannel() {}
    ~SquareWaveChannel() {}
    float getSignal();
    void setDuty(uint8_t duty);
};

#endif // SQUAREWAVECHANNEL_H
