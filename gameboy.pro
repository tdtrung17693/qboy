QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/apu/apu.cpp \
    core/apu/frame_sequencer.cpp \
    core/apu/frequencysweep.cpp \
    core/apu/lengthcounter.cpp \
    core/apu/programmablewavechannel.cpp \
    core/apu/squarewavechannel.cpp \
    core/apu/volumeenvelope.cpp \
    core/apu/wavechannel.cpp \
    core/cpu.cpp \
    core/gpu.cpp \
    core/mmu.cpp \
    core/joypad.cpp \
    core/utils.cpp \
    core/timer.cpp \
    core/instructions/arithmetic.cpp \
    core/instructions/bitwise.cpp \
    core/instructions/jump.cpp \
    core/instructions/misc.cpp \
    core/instructions/rot_and_shift.cpp \
    core/instructions/transfer.cpp \
    main.cpp \
    mainwindow.cpp \
    processorThread.cpp \
    qdisplay.cpp \
    qkeyinput.cpp \
    settingsdialog.cpp

HEADERS += \
    core/apu/apu.h \
    core/apu/frame_sequencer.h \
    core/apu/frequencysweep.h \
    core/apu/lengthcounter.h \
    core/apu/programmablewavechannel.h \
    core/apu/squarewavechannel.h \
    core/apu/volumeenvelope.h \
    core/apu/wavechannel.h \
    core/cpu.h \
    core/display.h \
    core/gpu.h \
    core/mmu.h \
    core/utils.h \
    core/joypad.h \
    core/timer.h \
    core/instructions/arithmetic.h \
    core/instructions/bitwise.h \
    core/instructions/instructions.h \
    core/instructions/jump.h \
    core/instructions/misc.h \
    core/instructions/rot_and_shift.h \
    core/instructions/transfer.h \
    mainwindow.h \
    processorThread.h \
    qdisplay.h \
    qkeyinput.h \
    settingsdialog.h
LIBS += -lSDL2 \
    -lSDL2main \
    -lSDL2_mixer
FORMS += \
    mainwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dmg.asm \
    dmg.bin
