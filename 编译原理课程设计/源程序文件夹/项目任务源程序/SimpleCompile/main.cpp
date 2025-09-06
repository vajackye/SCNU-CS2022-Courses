#include "mainwindow.h"

#include <QApplication>

MainWindow *g_mainWindow = nullptr; // 全局主窗口指针

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    g_mainWindow = &w;
    w.show();
    return a.exec();
}
