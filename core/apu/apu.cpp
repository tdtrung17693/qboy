#include "apu.h"
#include "core/utils.h"
#include <QBuffer>
#include <QtMath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <iostream>

APU::APU()
{
    soundOn = false;
    downsampleCount = round(4194304.0 / sampleFreq);
    SDL_AudioSpec audioSpec;
    audioSpec.freq = sampleFreq;
    audioSpec.format = AUDIO_U8;
    audioSpec.channels = 2;
    audioSpec.samples = sampleSize; // Adjust as needed
    audioSpec.callback = NULL;
    audioSpec.userdata = this;

    SDL_AudioSpec obtainedSpec;
    SDL_OpenAudio(&audioSpec, &obtainedSpec);
    SDL_PauseAudio(0);
    byteBuffer = new uint8_t[sampleSize];

    for (int i = 0; i < 4; ++i) {
        left_enabled_channels[i] = false;
        right_enabled_channels[i] = false;
    }

    // Frame Sequencer
    frameSequencer = new FrameSequencer();
    setUpFrameSequencer();

    // Channel 1
    square_channel_1 = new SquareWaveChannel();
    square_channel_1->number = 1;
    channel_1_envelope = new VolumeEnvelope();
    frequencySweep = new FrequencySweep();
    channel_1_lengthCounter = new LengthCounter();

    channel_1_envelope->connect(square_channel_1);
    frequencySweep->connect(square_channel_1);
    channel_1_lengthCounter->connect(square_channel_1);

    // Channel 2
    square_channel_2 = new SquareWaveChannel();
    square_channel_2->number = 2;
    channel_2_envelope = new VolumeEnvelope();
    channel_2_lengthCounter = new LengthCounter();

    channel_2_envelope->connect(square_channel_2);
    channel_2_lengthCounter->connect(square_channel_2);

    // Channel 3
    wave_channel = new ProgrammableWaveChannel();
    channel_3_lengthCounter = new LengthCounter();
    channel_3_lengthCounter->setDefaultCounter(255);
    channel_3_lengthCounter->connect(wave_channel);
}

APU::~APU()
{
    delete[] byteBuffer;
    delete frameSequencer;
    delete frequencySweep;
    delete square_channel_1;
    delete square_channel_2;
    delete channel_1_envelope;
    delete channel_2_envelope;
}

void APU::setUpFrameSequencer()
{
    std::vector<uint8_t> steps;
    steps.push_back(7);
    frameSequencer->addStepListener(steps, [&] {
        channel_1_envelope->tick();
        channel_2_envelope->tick();
    });

    steps.clear();
    steps.push_back(2);
    steps.push_back(6);
    frameSequencer->addStepListener(steps, [&] {
        frequencySweep->tick();
    });

    steps.clear();
    steps.push_back(0);
    steps.push_back(2);
    steps.push_back(4);
    steps.push_back(6);
    frameSequencer->addStepListener(steps, [&] {
        channel_1_lengthCounter->tick();
        channel_2_lengthCounter->tick();
        channel_3_lengthCounter->tick();
    });
}

void APU::connect(MMU* mmu)
{
    connectChannel_1(mmu);
    connectChannel_2(mmu);
    connectChannel_3(mmu);

    mmu->addWriteInterceptor(0xff24, [&](uint8_t value) {
        masterVolume_L = (value & 0x70) >> 4;
        masterVolume_R = value & 0x07;
        channelEnabled_L = readBit(7, value);
        channelEnabled_R = readBit(3, value);
    });

    mmu->addWriteInterceptor(0xff25, [&](uint8_t value) {
        for (uint8_t i = 0; i < 4; ++i) {
            left_enabled_channels[i] = readBit(i, (value >> 4) & 0xff);
            right_enabled_channels[i] = readBit(i, value);
        }
    });

    mmu->addWriteInterceptor(0xff26, [&](uint8_t value) {
        soundOn = readBit(7, value);
    });

    mmu->addReadInterceptor(0xff26, [&]() {
        return (soundOn << 7) | (square_channel_2->isEnable() << 1) | square_channel_1->isEnable();
    });
}

void APU::connectChannel_1(MMU* mmu)
{
    mmu->addWriteInterceptor(0xff10, [&](uint8_t value) {
        frequencySweep->period = (value >> 4) & 0x7;
        frequencySweep->shiftNumber = value & 0x7;
        frequencySweep->directionCoefficient = readBit(3, value) == 1 ? -1 : 1;
    });

    mmu->addWriteInterceptor(0xff11, [&](uint8_t value) {
        square_channel_1->setDuty((value >> 6) & 0x3);
        channel_1_lengthCounter->loadCounter(value & 0x3f);
    });

    mmu->addWriteInterceptor(0xff12, [&](uint8_t value) {
        channel_1_envelope->initialVolume = (value >> 4) & 0xf;
        channel_1_envelope->directionCoefficient = readBit(3, value) == 1 ? 1 : -1;
        channel_1_envelope->period = value & 0x7;
    });

    mmu->addWriteInterceptor(0xff13, [&](uint8_t value) {
        uint16_t hi = square_channel_1->getFrequency() & 0x700;
        square_channel_1->setFrequency(hi | value);
    });

    mmu->addWriteInterceptor(0xff14, [&](uint8_t value) {
        uint16_t lo = square_channel_1->getFrequency() & 0xff;
        square_channel_1->setFrequency(((value & 0x7) << 8) | lo);

        if (readBit(7, value) == 1) {
            square_channel_1->trigger();
            channel_1_envelope->trigger();
            frequencySweep->trigger();
            channel_1_lengthCounter->trigger();
        }

        if (readBit(6, value) == 1) {
            channel_1_lengthCounter->enable();
        } else {
            channel_1_lengthCounter->disable();
        }
    });
}

void APU::connectChannel_2(MMU* mmu)
{
    mmu->addWriteInterceptor(0xff16, [&](uint8_t value) {
        square_channel_2->setDuty((value >> 6) & 0x3);
        channel_2_lengthCounter->loadCounter(value & 0x3f);
    });

    mmu->addWriteInterceptor(0xff17, [&](uint8_t value) {
        channel_2_envelope->initialVolume = (value >> 4) & 0xf;
        channel_2_envelope->directionCoefficient = readBit(3, value) == 1 ? 1 : -1;
        channel_2_envelope->period = value & 0x7;
    });

    mmu->addWriteInterceptor(0xff18, [&](uint8_t value) {
        uint16_t hi = square_channel_2->getFrequency() & 0x700;
        square_channel_2->setFrequency(hi | value);
    });

    mmu->addWriteInterceptor(0xff19, [&](uint8_t value) {
        uint16_t lo = square_channel_2->getFrequency() & 0xff;
        square_channel_2->setFrequency(((value & 0x7) << 8) | lo);

        if (readBit(7, value) == 1) {
            square_channel_2->trigger();
            channel_2_envelope->trigger();
            channel_2_lengthCounter->trigger();
        }

        if (readBit(6, value) == 1) {
            channel_2_lengthCounter->enable();
        } else {
            channel_2_lengthCounter->disable();
        }
    });
}

void APU::connectChannel_3(MMU* mmu)
{
    for (uint8_t i = 0; i < 16; ++i) {
        mmu->addWriteInterceptor(0xff30 + i, [&, i](uint8_t value) {
            wave_channel->waveTable[i] = value;
        });
    }

    mmu->addWriteInterceptor(0xff1a, [&](uint8_t value) {
        if (readBit(7, value) == 1) {
            wave_channel->enable();
        } else
            wave_channel->disable();
    });

    mmu->addWriteInterceptor(0xff1b, [&](uint8_t value) {
        channel_3_lengthCounter->loadCounter(value & 0xff);
    });

    mmu->addWriteInterceptor(0xff1c, [&](uint8_t value) {
        wave_channel->volumeControlNumber = (value >> 5) & 0x3;
    });

    mmu->addWriteInterceptor(0xff1d, [&](uint8_t value) {
        uint16_t hi = wave_channel->getFrequency() & 0x700;
        wave_channel->setFrequency(hi | value);
    });

    mmu->addWriteInterceptor(0xff1e, [&](uint8_t value) {
        uint16_t lo = wave_channel->getFrequency() & 0xff;
        wave_channel->setFrequency(((value & 0x7) << 8) | lo);

        if (readBit(7, value) == 1) {
            wave_channel->trigger();
            channel_3_lengthCounter->trigger();
        }

        if (readBit(6, value) == 1) {
            channel_3_lengthCounter->enable();
        } else {
            channel_3_lengthCounter->disable();
        }
    });
}

void APU::update(int cycles)
{
    if (!soundOn)
        return;
    while (cycles-- != 0) {
        frameSequencer->tick();
        square_channel_1->tick();
        square_channel_2->tick();
        wave_channel->tick();

        if (--downsampleCount <= 0) {
            downsampleCount = round(4194304.0 / sampleFreq);
            //            cout << "Step = " << dec << unsigned(step_counter) << endl;

            float sampleL = 0;
            if (left_enabled_channels[0]) {
                sampleL += square_channel_1->getSignal();
            }

            if (left_enabled_channels[1]) {
                sampleL += square_channel_2->getSignal();
            }

            if (left_enabled_channels[2]) {
                sampleL += wave_channel->getSignal();
            }

            float sampleR = 0;
            if (right_enabled_channels[0]) {
                sampleR += square_channel_1->getSignal();
            }

            if (right_enabled_channels[1]) {
                sampleR += square_channel_2->getSignal();
            }

            if (right_enabled_channels[2]) {
                sampleR += wave_channel->getSignal();
            }

            uint8_t l = static_cast<uint8_t>(round(128.0 * (sampleL / 3) * (masterVolume_L * 1.0 / 7)));
            uint8_t r = static_cast<uint8_t>(round(128.0 * (sampleR / 3) * (masterVolume_R * 1.0 / 7)));
            byteBuffer[index] = l;
            byteBuffer[index + 1] = r;

            index += 2;
        }

        if (index >= sampleSize) {
            index = 0;
            while (SDL_GetQueuedAudioSize(1) > sampleSize) {
                SDL_Delay(1);
            }
            SDL_QueueAudio(1, byteBuffer, sampleSize);
        }
    }
}
