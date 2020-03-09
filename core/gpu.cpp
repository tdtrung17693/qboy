#include "core/gpu.h"
#include "core/mmu.h"
#include "core/utils.h"
#include <iostream>

#include <qlabel.h>
#include <qwidget.h>
#include <time.h>

GPU::GPU(Display* display)
{
    this->display = display;
    this->display->fillFrame(0xff, 0xff, 0xff);
}

void GPU::update(int cycles)
{
    if (!displayOn)
        return;

    scanlineCounter -= cycles;

    if (scanlineCounter > 0)
        return;

    scanlineCounter = 456;
    //    cout << "LY: " << dec << unsigned(ly) << endl;
    if (ly >= 144) {

        //        cpu->requestInterrupt(CPU::INT_VBLANK);
        for (auto fn : vblankCallbacks)
            fn();
        ly += 1;
        if (ly >= 154) {
            ly = 0;
            display->render();
        }

        return;
    }

    if (backgroundEnabled) {
        renderBackground();
    }

    if (windowEnabled) {
        renderWindow();
    }

    if (spriteEnabled) {
        renderSprites();
    }

    ly += 1;
}

void GPU::onVBlank(std::function<void()> fn)
{
    vblankCallbacks.push_back(fn);
}

void GPU::onLCDStat(std::function<void()> fn)
{
    statCallbacks.push_back(fn);
}

void GPU::connect(MMU* mmu)
{
    mem = mmu->mem;
    mmu->addReadInterceptor(0xff42, [&]() {
        return scy;
    });

    mmu->addReadInterceptor(0xff43, [&]() {
        return scx;
    });

    mmu->addReadInterceptor(0xff4a, [&]() {
        return wy;
    });

    mmu->addReadInterceptor(0xff4b, [&]() {
        return wx + 7;
    });

    mmu->addReadInterceptor(0xff44, [&]() {
        return ly;
    });

    mmu->addReadInterceptor(0xff45, [&]() {
        return lyc;
    });

    mmu->addReadInterceptor(0xff40, [&]() {
        return (displayOn << 7)
            | (((windowMapBaseAddress == 0x9c00) ? 1 : 0) << 6)
            | (windowEnabled << 5)
            | (((tileBaseAddress == 0x8000) ? 1 : 0) << 4)
            | (((backgroundMapBaseAddress == 0x9c00) ? 1 : 0) << 3)
            | (((spriteSize == TILE_8x16) ? 1 : 0) << 2)
            | (spriteEnabled << 1)
            | backgroundEnabled;
    });

    mmu->addReadInterceptor(0xff41, [&]() {
        return (LYCInterruptEnabled << 6)
            | (mode2InterruptEnabled << 5)
            | (mode1InterruptEnabled << 4)
            | (mode0InterruptEnabled << 3)
            | (coincidence_flag << 2)
            | (mode << 1);
    });

    mmu->addWriteInterceptor(0xff41, [&](uint8_t value) {
        //    Bit 6 - LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
        //    Bit 5 - Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
        //    Bit 4 - Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
        //    Bit 3 - Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
        //    Bit 2 - Coincidence Flag  (0:LYC<>LY, 1:LYC=LY) (Read Only)
        //    Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Read Only)
        //              0: During H-Blank
        //              1: During V-Blank
        //              2: During Searching OAM
        //              3: During Transferring Data to LCD Driver
        LYCInterruptEnabled = readBit(6, value);
        mode2InterruptEnabled = readBit(5, value);
        mode1InterruptEnabled = readBit(4, value);
        mode0InterruptEnabled = readBit(3, value);
        coincidence_flag = readBit(2, value);
        mode = value & 0x3;
    });

    mmu->addWriteInterceptor(0xff42, [&](uint8_t value) {
        scy = value;
    });

    mmu->addWriteInterceptor(0xff43, [&](uint8_t value) {
        scx = value;
    });

    mmu->addWriteInterceptor(0xff4a, [&](uint8_t value) {
        wy = value;
    });

    mmu->addWriteInterceptor(0xff4b, [&](uint8_t value) {
        wx = value - 7;
    });

    mmu->addWriteInterceptor(0xff44, [&](uint8_t) {
        ly = 0;
    });

    mmu->addWriteInterceptor(0xff45, [&](uint8_t value) {
        lyc = value;
    });

    mmu->addWriteInterceptor(0xff40, [&](uint8_t value) {
        //        Bit 7 - LCD Display Enable             (0=Off, 1=On)
        //        Bit 6 - Window Tile Map Display Select (0=9800-9BFF, 1=9C00-9FFF)
        //        Bit 5 - Window Display Enable          (0=Off, 1=On)
        //        Bit 4 - BG & Window Tile Data Select   (0=8800-97FF, 1=8000-8FFF)
        //        Bit 3 - BG Tile Map Display Select     (0=9800-9BFF, 1=9C00-9FFF)
        //        Bit 2 - OBJ (Sprite) Size              (0=8x8, 1=8x16)
        //        Bit 1 - OBJ (Sprite) Display Enable    (0=Off, 1=On)
        //        Bit 0 - BG Display (for CGB see below) (0=Off, 1=On)
        displayOn = readBit(7, value) == 1;
        windowMapBaseAddress = readBit(6, value) == 1 ? 0x9c00 : 0x9800;
        windowEnabled = readBit(5, value) == 1;
        tileBaseAddress = readBit(4, value) == 1 ? 0x8000 : 0x8800;
        printf("Tile base address: %04x\n", tileBaseAddress);
        backgroundMapBaseAddress = readBit(3, value) == 1 ? 0x9c00 : 0x9800;
        spriteSize = readBit(2, value) == 1 ? TILE_8x16 : TILE_8x8;
        spriteEnabled = readBit(1, value) == 1;
        backgroundEnabled = true;
    });
}

void GPU::renderBackground()
{
    uint8_t bgBlockRow, bgBlockCol;
    uint8_t tileByte1, tileByte2;
    uint8_t colorBitNumber;
    uint16_t blockNumber;
    uint16_t blockAddress;
    uint16_t tileAddress;
    uint16_t tileNumber;
    bool signedTile = false;

    if (tileBaseAddress == 0x8800) {
        signedTile = true;
    }

    for (uint8_t pixel = 0; pixel < 160; ++pixel) {
        bgBlockRow = (ly + scy) / 8;
        bgBlockCol = (pixel + scx) / 8;
        blockNumber = bgBlockCol + bgBlockRow * 32;

        blockAddress = backgroundMapBaseAddress + blockNumber;

        if (signedTile) {
            tileNumber = 128 + static_cast<int8_t>(mem[blockAddress]);
        } else {
            tileNumber = mem[blockAddress];
        }
        uint8_t trueline = (ly + scy) % 8;
        tileAddress = tileBaseAddress + trueline * 2 + tileNumber * 16;

        tileByte1 = mem[tileAddress];
        tileByte2 = mem[tileAddress + 1];
        colorBitNumber = (pixel + scx) % 8;

        colorBitNumber = 7 - colorBitNumber;

        int color = (tileByte2 & (1 << colorBitNumber)) >> colorBitNumber;
        color = color << 1;
        color |= ((tileByte1 & (1 << colorBitNumber)) >> colorBitNumber);
        // map color to palette
        color = getColor(color, 0xff47);
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;

        if (color == GPU::WHITE) {
            r = 0xff;
            g = 0xff;
            b = 0xff;
        } else if (color == GPU::LIGHT_GRAY) {
            r = 0xaa;
            g = 0xaa;
            b = 0xaa;
        } else if (color == GPU::DARK_GRAY) {
            r = 0x55;
            g = 0x55;
            b = 0x55;
        }

        display->setPixel(pixel, ly, r, g, b);
    }
}

void GPU::renderSprites()
{
    uint8_t objHeight = 8;
    uint8_t index;
    uint8_t yPos;
    uint8_t xPos;
    uint8_t tileNumber;
    uint8_t attributes;
    uint16_t tileAddress;
    bool signedTile = false;

    if (tileBaseAddress == 0x8800) {
        signedTile = true;
    }

    if (spriteSize == TILE_8x16)
        objHeight = 16;

    for (uint8_t sprite = 0; sprite < 40; sprite++) {
        // sprite occupies 4 bytes in the sprite attributes table
        index = sprite * 4;
        yPos = mem[0xFE00 + index] - 16;
        xPos = mem[0xFE00 + index + 1] - 8;
        attributes = mem[0xFE00 + index + 3];

        tileNumber = mem[0xFE00 + index + 2];
        bool yFlip = readBit(6, attributes) == 1;
        bool xFlip = readBit(5, attributes) == 1;

        // does this sprite intercept with the scanline?
        if ((ly >= yPos) && (ly < (yPos + objHeight))) {
            uint8_t line = ly - yPos;

            // read the sprite in backwards in the y axis
            if (yFlip) {
                line = objHeight - line;
            }

            tileAddress = 0x8000 + tileNumber * 16 + line * 2;
            uint8_t data1 = mem[tileAddress];
            uint8_t data2 = mem[tileAddress + 1];

            for (uint8_t tilePixel = 0; tilePixel < 8; tilePixel++) {
                uint8_t colorBit = tilePixel;
                if (xFlip) {
                    colorBit = 7 - colorBit;
                }

                // the rest is the same as for tiles
                uint8_t colorNum = readBit(colorBit, data2);
                colorNum = colorNum << 1;
                colorNum |= readBit(colorBit, data1);

                uint16_t colorPaletteAddress = readBit(4, attributes) == 1 ? 0xFF49 : 0xFF48;
                int color = getColor(colorNum, colorPaletteAddress);

                if (color == GPU::WHITE)
                    continue;

                int r = 0;
                int g = 0;
                int b = 0;

                if (color == GPU::WHITE) {
                    r = 0xff;
                    g = 0xff;
                    b = 0xff;
                } else if (color == GPU::LIGHT_GRAY) {
                    r = 0xaa;
                    g = 0xaa;
                    b = 0xaa;
                } else if (color == GPU::DARK_GRAY) {
                    r = 0x55;
                    g = 0x55;
                    b = 0x55;
                }
                uint8_t xPix = 7 - tilePixel;

                int pixel = xPos + xPix;

                // sanity check
                if ((ly > 143) || (pixel < 0) || (pixel > 159)) {
                    continue;
                }

                display->setPixel(pixel, ly, r, g, b);
            }
        }
    }
}

void GPU::renderWindow()
{
    uint8_t bgBlockRow, bgBlockCol;
    uint8_t tileByte1, tileByte2;
    uint8_t colorBitNumber;
    uint16_t blockNumber;
    uint16_t blockAddress;
    uint16_t tileAddress;
    uint16_t tileNumber;
    bool signedTile = false;

    if (tileBaseAddress == 0x8800) {
        signedTile = true;
    }

    for (uint8_t pixel = 0; pixel < 160; ++pixel) {
        bgBlockRow = (ly - wy) / 8;
        if (pixel + scx >= wx) {
            bgBlockCol = (pixel + scx - wx) / 8;
        } else {
            bgBlockCol = (pixel + scx) / 8;
        }
        blockNumber = bgBlockCol + bgBlockRow * 32;

        blockAddress = windowMapBaseAddress + blockNumber;

        if (signedTile) {
            tileNumber = 128 + static_cast<int8_t>(mem[blockAddress]);
        } else {
            tileNumber = mem[blockAddress];
        }
        uint8_t trueline = (ly + scy) % 8;
        tileAddress = tileBaseAddress + trueline * 2 + tileNumber * 16;

        tileByte1 = mem[tileAddress];
        tileByte2 = mem[tileAddress + 1];
        colorBitNumber = (pixel + scx) % 8;

        colorBitNumber = 7 - colorBitNumber;

        int color = (tileByte2 & (1 << colorBitNumber)) >> colorBitNumber;
        color = color << 1;
        color |= ((tileByte1 & (1 << colorBitNumber)) >> colorBitNumber);
        // map color to palette
        color = getColor(color, 0xff47);
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;

        if (color == GPU::WHITE) {
            r = 0xff;
            g = 0xff;
            b = 0xff;
        } else if (color == GPU::LIGHT_GRAY) {
            r = 0xaa;
            g = 0xaa;
            b = 0xaa;
        } else if (color == GPU::DARK_GRAY) {
            r = 0x55;
            g = 0x55;
            b = 0x55;
        }

        display->setPixel(pixel, ly, r, g, b);
    }
}

int GPU::getColor(int colorNum, uint16_t colorPaletteAddress)
{
    int pal = mem[colorPaletteAddress];
    int hi, lo;

    if (colorNum == 0) {
        hi = 1;
        lo = 0;
    } else if (colorNum == 1) {
        hi = 3;
        lo = 2;
    } else if (colorNum == 2) {
        hi = 5;
        lo = 4;
    } else {
        hi = 7;
        lo = 6;
    }

    int color = 0;
    color = ((pal & (1 << hi)) >> hi) << 1;
    color |= ((pal & (1 << lo)) >> lo);

    if (color == 0) {
        return GPU::WHITE;
    } else if (color == 1) {
        return GPU::LIGHT_GRAY;
    } else if (color == 2) {
        return GPU::DARK_GRAY;
    }

    return GPU::BLACK;
}

void GPU::setSTAT()
{
    if (!displayOn) {
        // set the mode to 1 during lcd disabled and reset scanline
        scanlineCounter = 456;
        ly = 0;
        mode = 1;
        return;
    }

    int currentmode = mode;

    bool reqInt = false;

    // in vblank so set mode to 1
    if (ly >= 144) {
        mode = 1;

        reqInt = mode1InterruptEnabled;
        // enable vblank interrupt
        //TODO: interrupt callback
    } else {
        int mode2bounds = 456 - 80;
        int mode3bounds = mode2bounds - 172;

        // mode 2
        if (scanlineCounter >= mode2bounds) {
            mode = 2;
            // reqInt = TestBit(status, 5);
            reqInt = mode2InterruptEnabled;
            // enable mode 2 interrupt
        }
        // mode 3
        else if (scanlineCounter >= mode3bounds) {
            mode = 3;
        }
        // mode 0
        else {
            mode = 0;
            reqInt = mode0InterruptEnabled;
        }
    }

    // just entered a new mode so request interupt
    if (reqInt && (mode != currentmode)) {
        //        RequestInterupt(1);
        for (auto fn : vblankCallbacks)
            fn();
    }

    // check the conincidence flag
    if (ly == lyc) {
        coincidence_flag = true;
        if (LYCInterruptEnabled)
            for (auto fn : vblankCallbacks)
                fn();
    } else {
        coincidence_flag = false;
    }
}
