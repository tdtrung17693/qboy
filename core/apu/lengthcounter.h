#ifndef LENGTHCOUNTER_H
#define LENGTHCOUNTER_H

#include "wavechannel.h"

class LengthCounter {
private:
    int counter;
    int defaultData = 63; // default to square wave channel length counter
    bool enabled = false;
    WaveChannel* waveChannel;

public:
    void tick();
    void loadCounter(int data);
    void enable();
    void disable();
    void connect(WaveChannel*);
    void trigger();
    void setDefaultCounter(int data);
};

#endif // LENGTHCOUNTER_H
