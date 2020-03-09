#ifndef FRAMESEQUENCER_H
#define FRAMESEQUENCER_H
#include <cstdint>
#include <functional>
#include <vector>

class FrameSequencer {
protected:
    std::vector<std::function<void()>> stepCallbacks;
    int timerCounter = 8192;
    uint8_t step = 0;

public:
    FrameSequencer();
    void addStepListener(uint8_t stepNumber, std::function<void()> fn);
    void addStepListener(std::vector<uint8_t> stepNumbers, std::function<void()> fn);
    void tick();
    void reset();
};

#endif // FRAMESEQUENCER_H
