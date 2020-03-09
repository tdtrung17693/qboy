#include "mainwindow.h"
#include <QDebug>
#include <QtMath>
#include <cmath>
#include <iostream>

#include "core/cpu.h"
#include "processorThread.h"
#include "qtimer.h"
#include "settingsdialog.h"
#include "ui_mainwindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>

#include <QAudioOutput>
#include <QBuffer>
#include <QFileDialog>
#include <QKeyEvent>

#define SAMPLE_RATE 44100
#define FREQ_CONST ((2.0 * M_PI) / SAMPLE_RATE)
void MainWindow::onUpdateGUIDisplay(QImage image)
{
    QPixmap img = QPixmap::fromImage(image);

    ui->display->setPixmap(img.scaled(ui->display->width(), ui->display->height(), Qt::KeepAspectRatio));
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new QSettings("../settings", QSettings::IniFormat, this);
    processorThread = new ProcessorThread(this);
    processorThread->syncSettings(settings);
    connect(processorThread,
        SIGNAL(updateGUIDisplay(QImage)),
        SLOT(onUpdateGUIDisplay(QImage)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    processorThread->keyPressed(key);
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    int key = event->key();
    processorThread->keyUp(key);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ((key->key() == Qt::Key_Enter) || (key->key() == Qt::Key_Return)) {
            processorThread->keyPressed(Qt::Key_Return);
        } else {
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}
void MainWindow::on_actionOpen_ROM_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Gameboy ROM (*.gb)"));
    dialog.setViewMode(QFileDialog::Detail);
    if (!dialog.exec()) {
        return;
    }

    QStringList fileName = dialog.selectedFiles();
    std::cout << fileName[0].toStdString() << std::endl;
    processorThread->stop();
    processorThread->setRom(fileName[0].toStdString());
    processorThread->start();
}

void MainWindow::on_actionKey_Mapping_triggered()
{
    SettingsDialog* dialog = new SettingsDialog(this);
    dialog->setSettings(settings);
    connect(dialog, SIGNAL(accepted()), SLOT(syncSettings()));
    dialog->open();
}

void MainWindow::syncSettings()
{
    cout << "Syncing settings " << endl;
    processorThread->syncSettings(settings);
}

short audiodata[4096];
volatile bool needsData = true; // poor mans semaphore

void callback(void* userdata, Uint8* stream, int len)
{
    printf("%p,%d\n", stream, len);
    while (needsData)
        ; // yay
    short* snd = reinterpret_cast<short*>(stream);
    len /= sizeof(*snd);
    for (int i = 0; i < len; i++) {
        snd[i] = audiodata[i];
    }
    needsData = true;
}

void MainWindow::on_actionSound_triggered()
{
    SDL_AudioSpec desiredSpec;
}
