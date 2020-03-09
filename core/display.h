#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
    Display() {}
    virtual ~Display() {}
    virtual void setPixel(int x, int y, int r, int g, int b) = 0;
    virtual void fillFrame(int r, int g, int b) = 0;
    virtual void render() = 0;
};

#endif // DISPLAY_H
