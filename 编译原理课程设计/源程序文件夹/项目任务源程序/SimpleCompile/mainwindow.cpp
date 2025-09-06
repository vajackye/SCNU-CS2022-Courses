#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建按钮
    taskOneButton = new QPushButton("lex词法分析", this);
    taskTwoButton = new QPushButton("语法分析", this);

    // 设置按钮固定大小（可选，可删掉以自动适应布局）
    taskOneButton->setFixedSize(150, 60);
    taskTwoButton->setFixedSize(150, 60);

    // 创建水平布局用于水平排列两个按钮
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch();                 // 左侧留空
    hLayout->addWidget(taskOneButton);
    hLayout->addSpacing(30);              // 两按钮间距
    hLayout->addWidget(taskTwoButton);
    hLayout->addStretch();                // 右侧留空

    // 创建垂直布局用于整体居中
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addStretch();                // 上方留空
    vLayout->addLayout(hLayout);          // 中间水平布局
    vLayout->addStretch();                // 下方留空

    // 设置主窗口的中央布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);

    // 连接信号与槽
    connect(taskOneButton, &QPushButton::clicked, this, &MainWindow::openTaskOne);
    connect(taskTwoButton, &QPushButton::clicked, this, &MainWindow::openTaskTwo);
}

void MainWindow::openTaskOne() {
    CodeMap.clear();
    TaskOneWindow *taskOne = new TaskOneWindow();
    taskOne->setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭后自动delete
    taskOne->show();
    this->hide();
}

void MainWindow::openTaskTwo() {
    TaskTwoWindow *taskTwo = new TaskTwoWindow();
    taskTwo->setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭后自动delete
    taskTwo->show();
    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

