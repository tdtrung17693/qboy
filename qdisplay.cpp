#include "qdisplay.h"

QDisplay::QDisplay()
    : QObject()
    , Display()
{
    image = QImage(160, 144, QImage::Format_RGB32);
}
void QDisplay::setPixel(int x, int y, int r, int g, int b)
{
    image.setPixel(x, y, qRgb(r, g, b));
}
void QDisplay::render()
{
    emit updateFrame(image);
}

void QDisplay::fillFrame(int r, int g, int b)
{
    image.fill(qRgb(r, g, b));
    render();
}
