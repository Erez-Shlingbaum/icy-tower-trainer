#include "mainwindow.h"
#include "os_utils.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
//    std::vector<PROCESSENTRY32> process_list = OS::get_running_processes();
    OS::get_running_processes();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
