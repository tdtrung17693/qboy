#ifndef JOYPAD_H
#define JOYPAD_H
#include "core/mmu.h"
#include <functional>

#include <cstdint>

class Joypad {
public:
    typedef enum KEY_TYPE {
        CONTROL_KEYS,
        ARROW_KEYS
    } KEY_TYPE;

    typedef enum KEY {
        KEY_A,
        KEY_B,
        KEY_SELECT,
        KEY_START,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT
    } KEY;

    KEY_TYPE keyType;
    uint8_t arrowKeysRegister = 0xf;
    uint8_t controlKeysRegister = 0xf;

    Joypad();
    void connect(MMU* mmu);
    void keyPress(KEY key);
    void keyRelease(KEY key);
    void onKeyInput(std::function<void(KEY)>);

private:
    std::vector<std::function<void(KEY)>> keyInputCallbacks;
};

#endif // JOYPAD_H
