#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core/cpu.h"
#include "processorThread.h"
#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public slots:
    void onUpdateGUIDisplay(QImage image);

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void keyReleaseEvent(QKeyEvent* event);
    void keyPressEvent(QKeyEvent* event);
    bool eventFilter(QObject* obj, QEvent* event);
    void readSettings();

public slots:
    void syncSettings();

private slots:
    void on_actionOpen_ROM_triggered();
    void on_actionKey_Mapping_triggered();

    void on_actionSound_triggered();

private:
    ProcessorThread* processorThread;
    Ui::MainWindow* ui;
    QSettings* settings;
};
#endif // MAINWINDOW_H
