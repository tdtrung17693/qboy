#include "qkeyinput.h"
#include <QKeyEvent>
#include <iostream>

QKeyInput::QKeyInput(QWidget* parent)
    : QLineEdit(parent)
{
    setReadOnly(true);
}

void QKeyInput::keyPressEvent(QKeyEvent* event)
{
    inputKey = static_cast<Qt::Key>(event->key());

    setText(QKeySequence(event->key()).toString());
}

void QKeyInput::setKey(Qt::Key key)
{
    inputKey = key;
    setText(QKeySequence(inputKey).toString());
}

void QKeyInput::keyReleaseEvent(QKeyEvent* event)
{

    emit keyChanged(inputKey);
}

void QKeyInput::focusInEvent(QFocusEvent* event)
{
    setText("Press any key...");
}

void QKeyInput::focusOutEvent(QFocusEvent* event)
{
    setText(QKeySequence(inputKey).toString());
}
