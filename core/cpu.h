#ifndef HEADER_CPU
#define HEADER_CPU
#include "core/mmu.h"
#include "core/timer.h"

#include "apu/apu.h"

#include <cstdint>
#include <qlabel.h>
#include <vector>
using namespace std;

#define COUT \
    if (0)   \
    cout
class GPU;
class CPU {
public:
    enum {
        INT_VBLANK,
        INT_LCD_STAT,
        INT_TIMER,
        INT_SERIAL,
        INT_JOYPAD
    };

    // memory
    GPU* gpu;
    MMU* mmu;
    APU* apu;
    Timer* timer;
    bool willEnableInterrupt = false;
    bool IME = false;

    // timer
    int timerCounter = 0;
    int divCounter = 0;
    uint16_t internalCounter = 0;

    // flags
    uint8_t z_flag = 0;
    uint8_t n_flag = 0;
    uint8_t h_flag = 0;
    uint8_t c_flag = 0;

    // registers
    uint8_t a = 0;
    uint8_t f = 0;
    uint8_t b = 0;
    uint8_t c = 0;
    uint8_t d = 0;
    uint8_t e = 0;
    uint8_t h = 0;
    uint8_t l = 0;
    uint16_t sp = 0xfffe;
    uint16_t pc = 0;

    // internal flag
    bool isBooting = true;
    bool willJump = false;

    vector<uint8_t> buffer;

    CPU();
    ~CPU();

    int execute(uint8_t);
    void reset();
    void step();

    void loadBootRom();
    void updateGraphic(uint8_t cycles);
    void updateTimer(uint8_t cycles);
    void handleInterrupt();
    void requestInterrupt(int interruptType);
    void setMMU(MMU* mmu);
    void setGPU(GPU* gpu);
    void loadRom(string romPath);
    void setAPU(APU* gpu);
};
#endif
