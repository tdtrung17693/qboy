#ifndef LENGTHCOUNTER_H
#define LENGTHCOUNTER_H

class LengthCounter {
private:
    bool enabled = false;
    WaveChannel* waveChannel;
    int counter = 0;

public:
    LengthCounter();
    void tick();
};

#endif // LENGTHCOUNTER_H
