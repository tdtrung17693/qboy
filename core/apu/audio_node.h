#ifndef CHANNEL_H
#define CHANNEL_H
#include <cstdint>

class AudioNode {
public:
    AudioNode() {}
    virtual ~Channel() {}
    virtual uint8_t getSignal();
};

#endif // CHANNEL_H
