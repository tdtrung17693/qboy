#ifndef CPUTHREAD_H
#define CPUTHREAD_H

#include "core/cpu.h"
#include "core/joypad.h"

#include <QLabel>
#include <QMap>
#include <QSettings>
#include <QThread>

class ProcessorThread : public QThread {
    Q_OBJECT
protected:
    bool isRunning = false;
    CPU* cpu;
    Joypad* joypad;
    QMap<Joypad::KEY, Qt::Key> keyMap;
    void run() override;

private slots:
    void onUpdateDisplay(QImage image);

public:
    ProcessorThread(QObject* parent = nullptr);
    void setRom(string romPath);
    void stop();
    void keyPressed(int keyCode);
    void keyUp(int keyCode);
    void syncSettings(QSettings* settings);
signals:
    void updateGUIDisplay(QImage image);
};

#endif // CPUTHREAD_H
