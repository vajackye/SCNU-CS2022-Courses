/*
* 版本: 1.0
* 作者: SCNU计师Vajackye
* 开源: https://github.com/vajackye/SCNU-CS2022-Courses/tree/main/%E7%BC%96%E8%AF%91%E5%8E%9F%E7%90%86/lab3
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analysis.h"
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QTextEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Analysis start;
    QString fileName;

    void showSourceCode(); //展示源代码
    void showErrorMessages(); //展示报错信息
    void fillSyntaxTree(Node* root, QTreeWidgetItem *parentItem,int depth);
    QHBoxLayout* createSourceAndTreeLayout();

private:
    Ui::MainWindow *ui;
    QTextEdit *sourceCodeView;      // 显示源代码的区域
    QTableWidget *errorTableView;  // 显示错误信息的表格
    QTreeWidget *syntaxTreeView; // 用于展示语法树

private slots:
    QString openFile();  // 槽函数：打开文件并分析
    void startAnalysis();   // 开始分析
    void showSyntaxTree();  // 展示语法树
    void saveSourceFile();  // 保存源文件

};
#endif // MAINWINDOW_H
