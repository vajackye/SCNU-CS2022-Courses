/*
* 版本: 1.0
* 作者: SCNU计师Vajackye
* 开源: https://github.com/vajackye/SCNU-CS2022-Courses/tree/main/%E7%BC%96%E8%AF%91%E5%8E%9F%E7%90%86/lab3
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建按钮
    QPushButton *openButton = new QPushButton("打开文件", this);
    QPushButton *startAnalysisButton = new QPushButton("开始分析", this);
    QPushButton *showSyntaxTreeButton = new QPushButton("展示语法树", this);
    QPushButton *saveSourceFileButton = new QPushButton("保存源文件", this);

    // 设置按钮大小
    openButton->setFixedSize(100, 30);
    startAnalysisButton->setFixedSize(120, 30);
    showSyntaxTreeButton->setFixedSize(150, 30);
    saveSourceFileButton->setFixedSize(120, 30);

    // 创建错误信息显示区域
    errorTableView = new QTableWidget(this);
    errorTableView->setColumnCount(3);
    errorTableView->setHorizontalHeaderLabels(QStringList() << "说明" << "文件" << "行");
    errorTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
    errorTableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选择
    errorTableView->horizontalHeader()->setStretchLastSection(true); // 使表格列宽自适应
    errorTableView->setColumnWidth(0, 400); // 将第一列宽度设置为 300 像素

    // 创建源代码显示区域
    sourceCodeView = new QTextEdit(this);
    sourceCodeView->setReadOnly(true); // 设置为只读
    sourceCodeView->setPlaceholderText("源代码将显示在此处...");

    // 创建语法树显示区域
    syntaxTreeView = new QTreeWidget(this);
    syntaxTreeView->setColumnCount(1); // 设置列数为 1，适应树形结构
    syntaxTreeView->setHeaderLabel("语法树"); // 设置树的标题

    // 创建按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(startAnalysisButton);
    buttonLayout->addWidget(showSyntaxTreeButton);
    buttonLayout->addWidget(saveSourceFileButton);

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout); // 保持按钮在顶部
    mainLayout->addWidget(errorTableView, 1); // 报错信息区域，调整大小为1
    mainLayout->addLayout(createSourceAndTreeLayout(), 3); // 源代码和语法树区域，调整大小为3

    // 设置主布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // 连接按钮的点击信号到槽函数
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(startAnalysisButton, &QPushButton::clicked, this, &MainWindow::startAnalysis);
    connect(showSyntaxTreeButton, &QPushButton::clicked, this, &MainWindow::showSyntaxTree);
    connect(saveSourceFileButton, &QPushButton::clicked, this, &MainWindow::saveSourceFile);
}

// 创建源代码和语法树的水平布局
QHBoxLayout* MainWindow::createSourceAndTreeLayout() {
    QHBoxLayout *sourceAndTreeLayout = new QHBoxLayout;

    // 左侧是源代码显示区域
    sourceAndTreeLayout->addWidget(sourceCodeView, 1);

    // 右侧是语法树显示区域
    sourceAndTreeLayout->addWidget(syntaxTreeView, 1);

    return sourceAndTreeLayout;
}


QString MainWindow::openFile() {
    // 弹出文件对话框，获取文件路径
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (filename.isEmpty()) return "";  // 用户未选择文件时返回空字符串


    // 保存文件路径为成员变量
    this->fileName = filename;

    return filename;
}

void MainWindow::startAnalysis() {
    if (this->fileName.isEmpty()) {
       QMessageBox::warning(this, tr("错误"), tr("请先选择文件!"));
       return;
    }
    // 每次分析前先清空原语法树
    if(start.root != nullptr)
        start.clear(start.root);

    // 初始化所有操作
    start.init();

    start.fileName = this->fileName;

    start.analysis(start.fileName);

    //展示源文件
    showSourceCode();

    //展示报错
    showErrorMessages();
}

//展示源代码
void MainWindow::showSourceCode() {
    // 确保源代码展示区域更新内容
    sourceCodeView->setText(QString::fromStdString(start.InputCode));
}

//展示报错信息
void MainWindow::showErrorMessages() {
    // 清空原有的表格内容
    errorTableView->setRowCount(0);

    // 有点小bug，在analysis内没存到文件夹信息。
    QStringList filen = this->fileName.split('/'); // 使用双反斜杠分割路径
    QString fileNameOnly = filen.isEmpty() ? QString() : filen.last(); // 获取最后的文件名

    for(int i = 0; i < start.errorList.size(); ++i) {
        auto& error = start.errorList[i]; // 引用当前的 tuple
        std::get<1>(error) = fileNameOnly; // 更新第二个元素（文件名部分）
    }

    // 填充表格数据
    errorTableView->setRowCount(start.errorList.size());
    for (int i = 0; i < start.errorList.size(); ++i) {
        const auto& [description, file, line] = start.errorList[i]; //类似于js或py的解包操作。
        errorTableView->setItem(i, 0, new QTableWidgetItem(description));
        errorTableView->setItem(i, 1, new QTableWidgetItem(file));
        errorTableView->setItem(i, 2, new QTableWidgetItem(QString::number(line)));
    }
}

// 展示语法树按钮的槽函数
void MainWindow::showSyntaxTree() {
    if (this->fileName.isEmpty()) {
          QMessageBox::warning(this, tr("错误"), tr("请先选择文件!"));
          return;
      }

      // 清空现有的语法树展示区域
      syntaxTreeView->clear();

      // 创建根节点，并添加到 QTreeWidget
      QTreeWidgetItem *rootItem = new QTreeWidgetItem();
      rootItem->setText(0, QString::fromStdString("点击展开")); //问题出现在这里，多写了一层start节点
      syntaxTreeView->addTopLevelItem(rootItem); // 将根节点添加到树形视图中

      // 调用递归函数填充语法树
      fillSyntaxTree(start.root, rootItem, 0);
}

// 递归地填充语法树到 QTreeWidgetItem
void MainWindow::fillSyntaxTree(Node* root, QTreeWidgetItem *parentItem, int depth) {
    if (!root) return;

    // 创建当前节点的 QTreeWidgetItem
    QTreeWidgetItem *currentItem = new QTreeWidgetItem(parentItem);
    currentItem->setText(0, QString::fromStdString(root->ch));

    // 为当前节点添加适当的缩进（可以选做，用于显示深度）
    QString indentation = QString("  ").repeated(depth);
    currentItem->setText(0, indentation + QString::fromStdString(root->ch));

    // 递归遍历子节点
    for (int i = 0; i < root->SIZE; ++i) {
        if (root->child[i]) {
            fillSyntaxTree(root->child[i], currentItem, depth + 1); // 递归子节点
        }
    }

    // 递归遍历兄弟节点
    if (root->sibling) {
        fillSyntaxTree(root->sibling, parentItem, depth);
    }
}



//保存源代码
void MainWindow::saveSourceFile() {
    // 获取源代码内容
    QString code = QString::fromStdString(start.InputCode);
    if (code.isEmpty()) {
        QMessageBox::warning(this, tr("错误"), tr("源代码为空，无法保存！"));
        return;
    }

    // 打开文件保存对话框，让用户选择文件路径
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存源代码"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) return;  // 用户取消保存

    // 创建并打开文件
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("无法打开文件进行保存！"));
        return;
    }

    // 创建文本流对象，将源代码写入文件
    QTextStream out(&file);
    out << code;  // 将源代码写入文件

    // 关闭文件
    file.close();

    // 显示保存成功的提示
    QMessageBox::information(this, tr("保存成功"), tr("源代码已成功保存！"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
