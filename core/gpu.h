#ifndef GPU_H
#define GPU_H
#include "core/cpu.h"
#include "core/display.h"

class GPU {
protected:
    enum {
        WHITE,
        LIGHT_GRAY,
        DARK_GRAY,
        BLACK
    };

    enum {
        TILE_8x8,
        TILE_8x16
    };
    int mode = 0;

    CPU* cpu;
    uint8_t* mem;
    QImage image;
    Display* display;
    int scanlineCounter = 0;

    std::vector<std::function<void()>> vblankCallbacks;
    std::vector<std::function<void()>> statCallbacks;

    uint16_t getBGBaseAddress();
    uint16_t getTileBaseAddress();
    uint16_t getWindowBaseAddress();

    int getColor(int colorNum, uint16_t colorPaletteAddress);

    void renderWindow();
    void renderSprites();
    void renderBackground();

public:
    uint8_t scy = 0;
    uint8_t scx = 0;
    uint8_t wy = 0;
    uint8_t wx = 7;
    uint8_t ly = 0;
    uint8_t lyc = 0;
    uint8_t spriteSize;
    uint16_t backgroundMapBaseAddress;
    uint16_t windowMapBaseAddress;
    uint16_t tileBaseAddress;
    bool spriteEnabled = false;
    bool displayOn = false;
    bool windowEnabled = false;
    bool backgroundEnabled = false;
    bool coincidence_flag = false;
    bool LYCInterruptEnabled = false;
    bool mode0InterruptEnabled = false;
    bool mode1InterruptEnabled = false;
    bool mode2InterruptEnabled = false;

    GPU(Display* display);
    void update(int cycles);
    void onVBlank(std::function<void()>);
    void onLCDStat(std::function<void()>);
    void connect(MMU* mmu);
    void setSTAT();
};
#endif
