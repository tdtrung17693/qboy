#ifndef SQUAREWAVE_H
#define SQUAREWAVE_H

class SquareWave {
protected:
    int frequency;
    int timerCounter;

public:
    SquareWave();
    void setFrequency(int frequency);
    void setVolume(int volume);
};

#endif // SQUAREWAVE_H
