#ifndef APU_H
#define APU_H

#include "core/mmu.h"

#include "frame_sequencer.h"
#include "frequencysweep.h"
#include "lengthcounter.h"
#include "programmablewavechannel.h"
#include "squarewavechannel.h"
#include "volumeenvelope.h"
#include "wavechannel.h"

#include <QByteArray>
#include <qaudiooutput.h>

class APU {
private:
    void connectChannel_1(MMU* mmu);
    void connectChannel_2(MMU* mmu);
    void connectChannel_3(MMU* mmu);
    void setUpFrameSequencer();
    bool left_enabled_channels[4];
    bool right_enabled_channels[4];
    int index = 0;

public:
    FrameSequencer* frameSequencer;

    // Channel 1
    SquareWaveChannel* square_channel_1;
    VolumeEnvelope* channel_1_envelope;
    FrequencySweep* frequencySweep;
    LengthCounter* channel_1_lengthCounter;

    // Channel 2
    SquareWaveChannel* square_channel_2;
    VolumeEnvelope* channel_2_envelope;
    LengthCounter* channel_2_lengthCounter;

    // Channel 3
    ProgrammableWaveChannel* wave_channel;
    LengthCounter* channel_3_lengthCounter;

    bool soundOn;
    uint8_t masterVolume_L = 7;
    uint8_t masterVolume_R = 7;

    bool channelEnabled_L = false;
    bool channelEnabled_R = false;
    int downsampleCount = 95;
    uint8_t* byteBuffer;

    int sampleFreq = 44100;
    int sampleSize = 512;

    APU();
    ~APU();
    void connect(MMU* mmu);
    void updateVolumeEnvelope();
    void update(int cycles);
};

#endif // APU_H
