#ifndef QKEYINPUT_H
#define QKEYINPUT_H

#include <QLineEdit>
#include <QWidget>

class QKeyInput : public QLineEdit {
    Q_OBJECT
public:
    explicit QKeyInput(QWidget* parent = nullptr);

    void setKey(Qt::Key key);
signals:
    void keyChanged(Qt::Key);
    // QWidget interface
protected:
    Qt::Key inputKey;
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void focusInEvent(QFocusEvent* event);
    void focusOutEvent(QFocusEvent* event);
};

#endif // QKEYINPUT_H
