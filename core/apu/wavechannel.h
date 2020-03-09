#ifndef WAVECHANNEL_H
#define WAVECHANNEL_H
#include <cstdint>
#include <vector>

class WaveChannel {
protected:
    uint16_t frequency;
    uint8_t volume;
    int timerCounter;
    bool enabled = false;

    virtual void triggerAction() {}
    virtual void tickAction() = 0;
    virtual void resetTimerCounter() = 0;

public:
    virtual ~WaveChannel() = 0;
    virtual float getSignal() = 0;
    uint16_t getFrequency();
    uint8_t getVolume();
    void setFrequency(uint16_t newFrequency);
    void setVolume(uint8_t newVolume);
    bool isEnable();
    void enable();
    void disable();
    void trigger();
    void tick();
};

#endif // WAVECHANNEL_H
