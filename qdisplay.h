#ifndef QDISPLAY_H
#define QDISPLAY_H
#include "core/display.h"
#include <qlabel.h>

class QDisplay : public QObject, public Display {
    Q_OBJECT
private:
    QImage image;

public:
    QDisplay();
    void setPixel(int x, int y, int r, int g, int b);
    void render();
    void fillFrame(int r, int g, int b);
signals:
    void updateFrame(QImage image);
};

#endif // QDISPLAY_H
