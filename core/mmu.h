#ifndef HEADER_MMU
#define HEADER_MMU
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <vector>
using namespace std;
class MMU {
    uint8_t keyRow = 0;
    map<uint16_t, function<void(uint8_t)>> writeInterceptors;
    map<uint16_t, function<uint8_t()>> readInterceptors;

public:
    MMU()
    {
        writeInterceptors.insert(pair<uint16_t, function<void(uint8_t)>>(0xff50, [&](uint8_t) {
            isBooting = false;
        }));

        writeInterceptors.insert(pair<uint16_t, function<void(uint8_t)>>(0xff46, [&](uint8_t value) {
            uint16_t startAddress = static_cast<uint16_t>(value << 8);

            for (uint8_t i = 0; i <= 0x9f; ++i) {
                write(0xfe00 + i, mem[startAddress + i]);
            }
            int i = 1;
            while (i-- > 0) {
            }
        }));
    }
    uint8_t keyControlReg = 0xf;
    uint8_t keyArrReg = 0xf;

    void loadBootROM();
    void loadROM(string romPath);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

    bool isBooting = true;
    uint8_t bootstrapROM[0x100];
    uint8_t mem[0xffff];

    void addWriteInterceptor(uint16_t address, function<void(uint8_t)>);
    void addReadInterceptor(uint16_t address, function<uint8_t()>);
};

#endif
