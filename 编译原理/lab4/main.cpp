/*
* 应用名：LR1语法分析器
* 作者：vajackye(22计师黄泽基）
* 版本：1.0
* 上一次更新日期：2024.12.2
* 开源地址：https://github.com/vajackye/SCNU-CS2022-Courses/tree/main/%E7%BC%96%E8%AF%91%E5%8E%9F%E7%90%86/lab4
*/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("LR1语法分析生成器(author:Vajackye 20222121007)");
    w.show();
    return a.exec();
}
