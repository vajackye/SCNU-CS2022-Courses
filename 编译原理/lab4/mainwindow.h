/*
* 应用名：LR1语法分析器
* 作者：vajackye(22计师黄泽基）
* 版本：1.0
* 上一次更新日期：2024.12.2
* 开源地址：https://github.com/vajackye/SCNU-CS2022-Courses/tree/main/%E7%BC%96%E8%AF%91%E5%8E%9F%E7%90%86/lab4
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include "LR1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LR1 start;
    QString filePath;
    //专门存储每一条产生式的编号
    unordered_map<ItemLR0, int> GramId;

private slots:
    void openFile();
    void saveFile();
    void Analysis();
    void ExternGrammer(); //扩充文法集展示
    string join(const vector<std::string> &vec, char delimiter); //辅助展示扩充文法集的函数
    void showFirst();
    void showFollow();
    void judgeSLR1();
    void showLR0DFA();
    void showLR1DFA();
    void showLR1Table();
    void showUsingText(); //使用说明书

};
#endif // MAINWINDOW_H
