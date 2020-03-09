#ifndef TIMER_H
#define TIMER_H
#include "mmu.h"

#include <functional>
#include <vector>

class Timer {
private:
    static const uint16_t CLOCK_MAP[];
    bool isOn = false;
    uint8_t clockChoosingValue = 0;
    // Timer clock is relative to CPU clock
    uint16_t timerClock = 0;
    int timerUpdateCounter = 0;

    std::vector<std::function<void()>> overflowCallbacks;
    void setClock(uint16_t clock);
    void resetValue();
    void countUp();

public:
    uint16_t counter = 0;
    uint8_t TIMA = 0;
    uint8_t TMA = 0;

    Timer();
    void onTimerOverflow(std::function<void()>);
    void update(uint8_t passedClock);
    void connect(MMU* mmu);
};

#endif // TIMER_H
