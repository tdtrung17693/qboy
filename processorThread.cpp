#include "processorThread.h"
#include "core/apu/apu.h"
#include "core/gpu.h"
#include "qdisplay.h"
#include "spdlog/spdlog.h"

#include <QSettings>
#include <iostream>
#include <time.h>

ProcessorThread::ProcessorThread(QObject* parent)
    : QThread(parent)
{
    QDisplay* displayer = new QDisplay();

    MMU* mmu = new MMU();
    GPU* gpu = new GPU(displayer);
    APU* apu = new APU();
    cpu = new CPU();

    joypad = new Joypad();
    gpu->connect(mmu);
    joypad->connect(mmu);
    apu->connect(mmu);

    cpu->setMMU(mmu);
    cpu->setGPU(gpu);
    cpu->setAPU(apu);
    cpu->loadBootRom();

    connect(displayer, SIGNAL(updateFrame(QImage)), SLOT(onUpdateDisplay(QImage)));
}

void ProcessorThread::syncSettings(QSettings* settings)
{
    settings->beginGroup("keys");
    keyMap[Joypad::KEY_A] = settings->value("A", Qt::Key_Z).value<Qt::Key>();
    keyMap[Joypad::KEY_B] = settings->value("B", Qt::Key_A).value<Qt::Key>();
    keyMap[Joypad::KEY_START] = settings->value("Start", Qt::Key_Return).value<Qt::Key>();
    keyMap[Joypad::KEY_SELECT] = settings->value("Select", Qt::Key_Space).value<Qt::Key>();
    keyMap[Joypad::KEY_UP] = settings->value("Up", Qt::Key_Up).value<Qt::Key>();
    keyMap[Joypad::KEY_DOWN] = settings->value("Down", Qt::Key_Down).value<Qt::Key>();
    keyMap[Joypad::KEY_LEFT] = settings->value("Left", Qt::Key_Left).value<Qt::Key>();
    keyMap[Joypad::KEY_RIGHT] = settings->value("Right", Qt::Key_Right).value<Qt::Key>();
    settings->endGroup();
}

void ProcessorThread::onUpdateDisplay(QImage image)
{
    emit updateGUIDisplay(image);
}

void ProcessorThread::keyUp(int keyCode)
{
    if (!isRunning)
        return;

    spdlog::get("cpu_logger")->info("Key {} released", keyCode);
    if (keyCode == keyMap.value(Joypad::KEY_RIGHT)) {
        joypad->keyRelease(Joypad::KEY_RIGHT);
    } else if (keyCode == keyMap.value(Joypad::KEY_LEFT)) {
        joypad->keyRelease(Joypad::KEY_LEFT);
    } else if (keyCode == keyMap.value(Joypad::KEY_UP)) {
        joypad->keyRelease(Joypad::KEY_UP);
    } else if (keyCode == keyMap.value(Joypad::KEY_DOWN)) {
        joypad->keyRelease(Joypad::KEY_DOWN);
    } else if (keyCode == keyMap.value(Joypad::KEY_A)) {
        joypad->keyRelease(Joypad::KEY_A);
    } else if (keyCode == keyMap.value(Joypad::KEY_B)) {
        joypad->keyRelease(Joypad::KEY_B);
    } else if (keyCode == keyMap.value(Joypad::KEY_SELECT)) {
        joypad->keyRelease(Joypad::KEY_SELECT);
    } else if (keyCode == keyMap.value(Joypad::KEY_START)) {
        joypad->keyRelease(Joypad::KEY_START);
    }
}

void ProcessorThread::keyPressed(int keyCode)
{
    if (!isRunning)
        return;

    if (keyCode == keyMap.value(Joypad::KEY_RIGHT)) {
        joypad->keyPress(Joypad::KEY_RIGHT);
    } else if (keyCode == keyMap.value(Joypad::KEY_LEFT)) {
        joypad->keyPress(Joypad::KEY_LEFT);
    } else if (keyCode == keyMap.value(Joypad::KEY_UP)) {
        joypad->keyPress(Joypad::KEY_UP);
    } else if (keyCode == keyMap.value(Joypad::KEY_DOWN)) {
        joypad->keyPress(Joypad::KEY_DOWN);
    } else if (keyCode == keyMap.value(Joypad::KEY_A)) {
        joypad->keyPress(Joypad::KEY_A);
    } else if (keyCode == keyMap.value(Joypad::KEY_B)) {
        joypad->keyPress(Joypad::KEY_B);
    } else if (keyCode == keyMap.value(Joypad::KEY_SELECT)) {
        joypad->keyPress(Joypad::KEY_SELECT);
    } else if (keyCode == keyMap.value(Joypad::KEY_START)) {
        joypad->keyPress(Joypad::KEY_START);
    }
}

void ProcessorThread::setRom(string romPath)
{
    cpu->loadRom(romPath);
}

void ProcessorThread::stop()
{
    isRunning = false;
}

void ProcessorThread::run()
{
    isRunning = true;
    cpu->reset();
    while (isRunning) {
        cpu->step();
    }
}
