#include "core/joypad.h"

Joypad::Joypad()
{
}

void Joypad::connect(MMU* mmu)
{
    mmu->addWriteInterceptor(0xff00, [&](uint8_t value) {
        uint8_t row = value & 0x30;
        if (row == 0x10)
            keyType = CONTROL_KEYS;
        else
            keyType = ARROW_KEYS;
    });

    mmu->addReadInterceptor(0xff00, [&]() {
        if (keyType == CONTROL_KEYS) {
            return controlKeysRegister;
        } else {
            return arrowKeysRegister;
        }
    });
}

void Joypad::keyPress(KEY key)
{
    if (key == KEY_RIGHT) {
        arrowKeysRegister &= 0xe;
    } else if (key == KEY_LEFT) {
        arrowKeysRegister &= 0xd;
    } else if (key == KEY_UP) {
        arrowKeysRegister &= 0xb;
    } else if (key == KEY_DOWN) {
        arrowKeysRegister &= 0x7;
    } else if (key == KEY_A) {
        controlKeysRegister &= 0xe;
    } else if (key == KEY_B) {
        controlKeysRegister &= 0xd;
    } else if (key == KEY_SELECT) {
        controlKeysRegister &= 0xb;
    } else if (key == KEY_START) {
        controlKeysRegister &= 0x7;
    }

    for (auto& fn : keyInputCallbacks) {
        fn(key);
    }
}

void Joypad::keyRelease(KEY key)
{
    if (key == KEY_RIGHT) {
        arrowKeysRegister |= 0x1;
    } else if (key == KEY_LEFT) {
        arrowKeysRegister |= 0x2;
    } else if (key == KEY_UP) {
        arrowKeysRegister |= 0x4;
    } else if (key == KEY_DOWN) {
        arrowKeysRegister |= 0x8;
    } else if (key == KEY_A) {
        controlKeysRegister |= 0x1;
    } else if (key == KEY_B) {
        controlKeysRegister |= 0x2;
    } else if (key == KEY_SELECT) {
        controlKeysRegister |= 0x4;
    } else if (key == KEY_START) {
        controlKeysRegister |= 0x8;
    }
}

void Joypad::onKeyInput(std::function<void(Joypad::KEY)> fn)
{
    keyInputCallbacks.push_back(fn);
}
