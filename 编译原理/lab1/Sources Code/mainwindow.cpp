/*
* 完成日期：2024-9-17
* 作者：vajackye/黄泽基
* 学校：SCNU-CS-2022级
* 版本：0.1--version
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "executed.h"   //执行函数
#include <QFileDialog>  //选择文件窗口
#include <QMessageBox>
#include <QVBoxLayout>
#include <QApplication>  // 为了使用 QApplication::quit()
#include <QDialog>       // 为了使用 QDialog 弹出窗口
#include <QLabel>        // 用于显示文档内容
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


// 声明 executed.cpp 中的函数
// 之所以能使用，是因为Pro文件内的SOURCES 列出了项目中的所有源文件，HEADERS 列出了项目中的所有头文件。
// 这样使得它们都能被编译然后链接起来。
extern string doAnalysis(const string& filePath);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //窗口标题栏
    setWindowTitle("Rust基础词法分析器(author: vajackye, version: 0.1)");


    //按钮和文本框初始化
    openFileButton = new QPushButton("打开文件", this);
    viewDocButton = new QPushButton("使用说明", this);
    exitButton = new QPushButton("退出程序", this);
    resultTextEdit = new QTextEdit(this);

    //布局设置
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(openFileButton);//添加按钮控件
    layout->addWidget(viewDocButton);  // 添加使用说明按钮
        layout->addWidget(exitButton); //添加退出按钮控件
    layout->addWidget(resultTextEdit);//添加文本框控件

    //创建中心widget为QMainWindow设置中心控件并设置布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    //连接按钮点击事件到槽函数
    connect(openFileButton, &QPushButton::clicked, this, &MainWindow::on_openFileButton_clicked);
    // 连接查看文档按钮
    connect(viewDocButton, &QPushButton::clicked, this, &MainWindow::on_viewDocButton_clicked);
    // 连接退出按钮
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::on_exitButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked() //打开文件按钮
{
    //打开文件选择对话框
    QString filePath = QFileDialog::getOpenFileName(this, tr("打开文件"), "", tr("Rust源文件 (*.rs);;所有文件 (*)"));

    //如果用户未选择文件
    if(filePath.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("未选择文件！"));
        return;
    }

    //调用executed.cpp的doAnalysis()
    string analysisRes = doAnalysis(filePath.toStdString());

    //分析结果显示到 QTextEdit
    resultTextEdit->setPlainText(QString::fromStdString(analysisRes));
}

//退出程序
void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();  // 退出应用程序
}

//详细文档使用说明书
void MainWindow::on_viewDocButton_clicked()
{
    // 创建一个对话框显示文档
    QDialog *docDialog = new QDialog(this);
    docDialog->setWindowTitle("词法分析器使用说明");

    // 文档内容，可以替换为自己的使用说明
    QString docText = "声明：版权归:SCNU-CS-2022级-黄泽基(vajackye)所有.\n\n"
                      "词法分析器使用说明:\n\n"
                      "1. 点击 '打开文件' 按钮，选择需要分析的 Rust 源文件。\n"
                      "2. 文件内容将被分析，结果会显示在下方的文本框内。\n"
                      "3. 支持的特性包括: 关键字、字符串、符号、数字处理等。\n"
                      "4. 点击 '退出' 按钮可关闭程序。\n\n"
                      "注意事项:\n\n"
                      "① 未写宏专题，只特判了一个println!宏在标识符部分，而且是简单的特判。\n一行中开头的（可含空格）部分，不能有其余字符(连着写的，与println不分开的。。\n"
                      "② 未判断部分没用过的字符如 ...,只判断了一个for的 ..。\n"
                      "③ 不支持注释嵌套，如要增加，可以在注释部分增加一个计数器，统计/ *和\n* /出现次数是否相同。\n"
                      "④ 未进行浮点数的部分适配：e5,e+5,e-5等e前不含数字的都无法适配。\n"
                      "⑤ 不支持字符串换行(通过r#原生字符串或者\\换行，如需添加，可在原生字符串,\n字符串判断部分添加一个类似于多行注释的expFlag标识符标注是否换行。\n"
                      "⑥ 如果需要添加更多适配和词法分析功能，可自行补充函数或者在原有函数内\n 微调即可，所有基本词法分类均被封装为函数模块";

    QLabel *docLabel = new QLabel(docText, docDialog);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(docLabel);
    docDialog->setLayout(layout);

    docDialog->exec();  // 显示对话框并等待用户关闭
}
