#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget* parent);
    ~SettingsDialog();

    void setSettings(QSettings* settings);

private:
    Ui::SettingsDialog* ui;
    QSettings* settings;
    // QDialog interface
public slots:
    void reject();
    void accept();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent* event);
protected slots:
    void keyAChanged(Qt::Key key);
    void keyBChanged(Qt::Key key);
    void keySelectChanged(Qt::Key key);
    void keyStartChanged(Qt::Key key);
    void keyUpChanged(Qt::Key key);
    void keyDownChanged(Qt::Key key);
    void keyRightChanged(Qt::Key key);
    void keyLeftChanged(Qt::Key key);
};

#endif // SETTINGSDIALOG_H
