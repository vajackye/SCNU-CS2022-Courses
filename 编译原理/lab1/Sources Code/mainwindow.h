/*
* 完成日期：2024-9-17
* 作者：vajackye/黄泽基
* 学校：SCNU-CS-2022级
* 版本：0.1--version
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:  //槽函数，即接收函数?
    void on_openFileButton_clicked();
    void on_exitButton_clicked();      //退出槽函数
    void on_viewDocButton_clicked();   // 查看使用说明槽函数

private:
    Ui::MainWindow *ui;
    QPushButton *openFileButton; // 打开文件的按钮
    QPushButton *exitButton;    // 退出程序按钮
    QPushButton *viewDocButton;   // 查看详细文档按钮
    QTextEdit *resultTextEdit;  //文本框，用于显示分析结果
};
#endif // MAINWINDOW_H
