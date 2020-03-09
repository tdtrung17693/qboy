#include "core/mmu.h"
#include "core/cpu.h"
#include "spdlog/spdlog.h"
#include <fstream>
#include <iostream>

using namespace std;

void MMU::loadBootROM()
{
    ifstream infile("./dmg.bin", ios::binary);
    //get length of file
    infile.seekg(0, infile.end);
    size_t length = infile.tellg();
    infile.seekg(0, infile.beg);
    COUT << "Size: " << hex << length << endl;
    //read file
    if (length > 0) {
        infile.read(reinterpret_cast<char*>(&bootstrapROM[0]), length);
    }
    infile.close();
}

void MMU::loadROM(string romPath)
{
    ifstream infile(romPath, ios::binary);
    //get length of file
    infile.seekg(0, infile.end);
    size_t length = infile.tellg();
    infile.seekg(0, infile.beg);
    cout << "Size: " << hex << length << endl;
    //read file
    if (length > 0) {
        infile.read(reinterpret_cast<char*>(&mem[0]), length);
    }
    infile.close();
}

uint8_t MMU::read(uint16_t address)
{
    //    if (isBooting == false)
    //        printf("Reading from %04x\n", address);
    if (readInterceptors.find(address) != readInterceptors.end()) {
        return readInterceptors[address]();
    }

    if (isBooting && address <= 0xff)
        return bootstrapROM[address];

    return mem[address];
}

void MMU::write(uint16_t address, uint8_t value)
{
    if (writeInterceptors.find(address) != writeInterceptors.end())
        writeInterceptors[address](value);
    if (address == 0x2000) {
        auto logger = spdlog::get("cpu_logger");
        logger->info("MBC is not implemented", address);
        return;
    }
    //    if (0xff00 == address) {
    //        keyRow = value & 0x30;
    //        return;
    //    }

    mem[address] = value;
}

void MMU::addWriteInterceptor(uint16_t address, function<void(uint8_t)> fn)
{
    writeInterceptors.insert(pair<uint16_t, function<void(uint8_t)>>(address, fn));
}

void MMU::addReadInterceptor(uint16_t address, function<uint8_t()> fn)
{
    readInterceptors.insert(pair<uint16_t, function<uint8_t()>>(address, fn));
}
