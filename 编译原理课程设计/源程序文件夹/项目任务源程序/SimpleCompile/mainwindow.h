#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taskonewindow.h"
#include "tasktwowindow.h"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
        void openTaskOne();
        void openTaskTwo();

private:
    Ui::MainWindow *ui;
    QPushButton *taskOneButton;
    QPushButton *taskTwoButton;
};
#endif // MAINWINDOW_H
