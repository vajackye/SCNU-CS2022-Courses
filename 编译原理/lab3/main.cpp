/*
* 版本: 1.0
* 作者: SCNU计师Vajackye
* 开源: https://github.com/vajackye/SCNU-CS2022-Courses/tree/main/%E7%BC%96%E8%AF%91%E5%8E%9F%E7%90%86/lab3
*/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("TINY扩充语言的语法树生成(author:Vajackye)");
    w.show();
    return a.exec();
}
