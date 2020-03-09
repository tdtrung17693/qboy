#include <execinfo.h>
#include <signal.h>
#include <unistd.h>

#include <QApplication>
#include <iostream>

#include "core/cpu.h"
#include "mainwindow.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

using namespace std;
int main(int argc, char* argv[])
{
    try {
        auto cpu_logger = spdlog::basic_logger_mt("cpu_logger", "LOG1.txt");
        cpu_logger->set_level(spdlog::level::off);
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
    QApplication a(argc, argv);
    MainWindow w;
    QSize size = w.size();
    cout << size.width() << endl;
    w.show();
    return a.exec();
}
