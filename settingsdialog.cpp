#include "settingsdialog.h"
#include "core/joypad.h"
#include "ui_settingsdialog.h"
#include <QVariant>
#include <iostream>

SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(rejected()), SLOT(reject()));
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(reject()));
    connect(this, SIGNAL(clicked), SLOT(mousePressEvent));
    connect(ui->keyA, SIGNAL(keyChanged(Qt::Key)), SLOT(keyAChanged(Qt::Key)));
    connect(ui->keyB, SIGNAL(keyChanged(Qt::Key)), SLOT(keyBChanged(Qt::Key)));
    connect(ui->keyStart, SIGNAL(keyChanged(Qt::Key)), SLOT(keyStartChanged(Qt::Key)));
    connect(ui->keySelect, SIGNAL(keyChanged(Qt::Key)), SLOT(keySelectChanged(Qt::Key)));
    connect(ui->keyUp, SIGNAL(keyChanged(Qt::Key)), SLOT(keyUpChanged(Qt::Key)));
    connect(ui->keyDown, SIGNAL(keyChanged(Qt::Key)), SLOT(keyDownChanged(Qt::Key)));
    connect(ui->keyLeft, SIGNAL(keyChanged(Qt::Key)), SLOT(keyLeftChanged(Qt::Key)));
    connect(ui->keyRight, SIGNAL(keyChanged(Qt::Key)), SLOT(keyRightChanged(Qt::Key)));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::keyAChanged(Qt::Key key)
{
    settings->beginGroup("keys");
    settings->setValue("A", QVariant(key));
    settings->endGroup();
}

void SettingsDialog::keyBChanged(Qt::Key key)
{
    settings->beginGroup("keys");
    settings->setValue("B", QVariant(key));
    settings->endGroup();
}

void SettingsDialog::keySelectChanged(Qt::Key key)
{
    settings->beginGroup("keys");
    settings->setValue("Select", QVariant(key));
    settings->endGroup();
}

void SettingsDialog::keyStartChanged(Qt::Key key)
{
    settings->beginGroup("keys");
    settings->setValue("Start", QVariant(key));
    settings->endGroup();
}

void SettingsDialog::keyUpChanged(Qt::Key key)
{
    settings->beginGroup("keys");
    settings->setValue("Up", QVariant(key));
    settings->endGroup();
}

void SettingsDialog::keyDownChanged(Qt::Key key)
{
    settings->beginGroup("keys");
    settings->setValue("Down", QVariant(key));
    settings->endGroup();
}

void SettingsDialog::keyLeftChanged(Qt::Key key)
{
    settings->beginGroup("keys");
    settings->setValue("Left", QVariant(key));
    settings->endGroup();
}

void SettingsDialog::keyRightChanged(Qt::Key key)
{
    settings->beginGroup("keys");
    settings->setValue("Right", QVariant(key));
    settings->endGroup();
}

void SettingsDialog::setSettings(QSettings* settings)
{
    this->settings = settings;
    settings->beginGroup("keys");
    ui->keyA->setKey((settings->value("A", Qt::Key_Z).value<Qt::Key>()));
    ui->keyB->setKey((settings->value("B", Qt::Key_X).value<Qt::Key>()));
    ui->keySelect->setKey((settings->value("Select", Qt::Key_Space).value<Qt::Key>()));
    ui->keyStart->setKey((settings->value("Start", Qt::Key_Return).value<Qt::Key>()));
    ui->keyUp->setKey((settings->value("Up", Qt::Key_Up).value<Qt::Key>()));
    ui->keyDown->setKey((settings->value("Down", Qt::Key_Down).value<Qt::Key>()));
    ui->keyLeft->setKey((settings->value("Left", Qt::Key_Left).value<Qt::Key>()));
    ui->keyRight->setKey((settings->value("Right", Qt::Key_Right).value<Qt::Key>()));
    settings->endGroup();
}

void SettingsDialog::accept()
{
    settings->sync();
    emit accepted();
    close();
}

void SettingsDialog::reject()
{
    hide();
    close();
}

void SettingsDialog::mousePressEvent(QMouseEvent*)
{
    focusWidget()->clearFocus();
}
