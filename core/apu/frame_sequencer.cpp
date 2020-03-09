#include "frame_sequencer.h"

FrameSequencer::FrameSequencer()
{
    // Initialize default callbacks for all 8 steps
    for (int i = 0; i < 8; ++i) {
        stepCallbacks.push_back([] {});
    }
}

void FrameSequencer::addStepListener(uint8_t stepNumber, std::function<void()> fn)
{
    if (stepNumber >= 8)
        throw "Invalid step number. Step number must be between 0 and 7.";

    stepCallbacks[stepNumber] = fn;
}

void FrameSequencer::addStepListener(std::vector<uint8_t> stepNumbers, std::function<void()> fn)
{
    for (auto& stepNumber : stepNumbers) {
        addStepListener(stepNumber, fn);
    }
}

void FrameSequencer::tick()
{
    --timerCounter;
    if (timerCounter > 0)
        return;
    timerCounter = 8192;

    stepCallbacks[step]();
    step = (step + 1) % 8;
}

void FrameSequencer::reset()
{
    timerCounter = 8192;
    step = 0;
}
