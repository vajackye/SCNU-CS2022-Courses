/*
* 应用名：LR1语法分析器
* 作者：vajackye(22计师黄泽基）
* 版本：1.0
* 上一次更新日期：2024.12.2
* 开源地址：https://github.com/vajackye/SCNU-CS2022-Courses/tree/main/%E7%BC%96%E8%AF%91%E5%8E%9F%E7%90%86/lab4
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 假设 ui 是指向界面对象的指针，例如 Ui::MainWindow
    connect(ui->OpenBtn, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->SaveBtn, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(ui->AnalysisBtn, &QPushButton::clicked, this, &MainWindow::Analysis);
    connect(ui->FirstBtn, &QPushButton::clicked, this, &MainWindow::showFirst);
    connect(ui->FollowBtn, &QPushButton::clicked, this, &MainWindow::showFollow);
    connect(ui->SLRBtn, &QPushButton::clicked, this, &MainWindow::judgeSLR1);
    connect(ui->LR0DfaBtn, &QPushButton::clicked, this, &MainWindow::showLR0DFA);
    connect(ui->LR1DfaBtn, &QPushButton::clicked, this, &MainWindow::showLR1DFA);
    connect(ui->LR1TabelBtn, &QPushButton::clicked, this, &MainWindow::showLR1Table);
    connect(ui->UsingText,&QAction::triggered, this, &MainWindow::showUsingText);//展示使用说明书
    connect(ui->Quit,&QAction::triggered,this,&MainWindow::close);//退出

}

MainWindow::~MainWindow()
{
    delete ui;
}

//菜单部分使用说明书
void MainWindow::showUsingText() {
    // 创建一个对话框窗口
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle(tr("使用说明书"));

    // 添加一个只读文本框
    QTextEdit *textEdit = new QTextEdit(dialog);
    textEdit->setText(tr("欢迎使用本软件！\n\n"
                         "1. 用户可在文法输入界面进行文法输入/点击打开文件读入文法\n"
                         "2. 用户输入完之后,请点击分析按钮进行分析\n"
                         "3. 之后可点击相应按钮获取相应结果。\n\n\n"
                         "注意事项:\n"
                         "①输入/读入的文法每个符号之间必须有空格(以进行区分:单词字符,详见案例:exp -> exp addop exp | exp)\n"
                         "②输入/读入的文法存在死递归,则无法进行后续分析(只可求取follow集),详见案例:E -> E + T"));
    textEdit->setReadOnly(true);

    // 设置对话框布局
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(textEdit);
    dialog->setLayout(layout);

    // 设置对话框大小为原来的两倍
    dialog->resize(500, 300);

    // 显示对话框
    dialog->exec();
}

//打开用户要分析的文本文件
void MainWindow::openFile()
{
    // 使用 QFileDialog 弹出文件选择对话框
    QString filePath = QFileDialog::getOpenFileName(this, tr("打开文件"), "", tr("Text Files (*.txt);;All Files (*.*)"));

    if (!filePath.isEmpty()) {
        // 存储文件路径到 MainWindow 内的成员变量
        this->filePath = filePath;

        // 打开文件以进行读取
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString fileContent;

            // 逐行读取文件内容
            while (!in.atEnd()) {
                QString line = in.readLine();
                fileContent.append(line + '\n'); // 将每行内容添加到字符串中，并加上换行符
            }

            // 关闭文件
            file.close();

            // 将内容显示到 QPlainTextEdit 中
            ui->InputText->setPlainText(fileContent);
        } else {
            // 如果文件无法打开，则显示错误消息
            QMessageBox::critical(this, tr("错误"), tr("无法打开文件!"));
        }
    }
}

//保存用户输入
void MainWindow::saveFile()
{
    // 打开文件保存对话框，选择保存路径和文件名
    QString filePath = QFileDialog::getSaveFileName(this, tr("保存文件"), "", tr("文本文件 (*.txt);;All Files (*.*)"));

    if (!filePath.isEmpty()) {
        // 打开文件以进行写入
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            // 将 QPlainTextEdit 的内容写入文件
            out << ui->InputText->toPlainText();

            // 关闭文件
            file.close();

            // 可选：显示一个消息框表示保存成功
            QMessageBox::information(this, tr("提示"), tr("保存成功!"));
        } else {
            // 如果文件无法打开，则显示错误消息
            QMessageBox::critical(this, tr("错误"), tr("保存文件!"));
        }
    }
}


void MainWindow::Analysis()
{
    // 检查 InputText 是否有内容
    if (ui->InputText->toPlainText().isEmpty()) {
        QMessageBox::information(this, tr("注意"), tr("请先输入文法!"));
        return;
    }

    // 清除所有 QTableWidget 的内容
    QList<QTableWidget *> tables = {
        ui->FirstText,     // First 集合的表格
        ui->FollowText,    // Follow 集合的表格
        ui->LR0Text,       // LR0 表格
        ui->LR1DfaText,     // LR1 表格
        ui->LR1ToTabel
    };

    for (QTableWidget *table : tables) {
        if (table) {
            table->clear();                      // 清除所有数据
            table->setRowCount(0);               // 重置行数
            table->setColumnCount(0);            // 重置列数
        }
    }

    // 如果有内容，将其传入分析函数
    start.analysis(ui->InputText);
//    qDebug()<<"我准备展示扩充文法";
    this->GramId.clear(); //清除产生式的记忆
    ExternGrammer(); //同时展示扩充后文法
    return;
}

// 展示扩充文法集
void MainWindow::ExternGrammer()
{
    // 判断 langMp 是否为空
    //一般用不上，加个预防报错
    if (start.langMp.empty()) {
        QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法展示扩充文法集合"));
        return;
    }
    // 获取 LR1 对象的 langMp
    QStringList grammerLines;
    int idCounter = 1; //给每个产生式一个编号

    //给首个产生式子最小的编号。
    const auto &firstId = start.langMp[start.startLang];
    QString leftSide = QString::fromStdString(start.startLang);
    QString rightSide = QString::fromStdString(join(firstId[0], ' ')); // 将 vector<string> 转为单个字符串，中间用空格分隔

    // 格式化为 "左部规则 -> 右部规则"
    QString line = leftSide + " -> " + rightSide;

    //记录产生式的编号
    ItemLR0 item = {start.startLang, firstId[0], 0};
    GramId[item] = idCounter++;

    // 将格式化后的文法规则添加到 grammerLines 中
    grammerLines.append(line);

    // 遍历 langMp 并将每一行文法转换为 QString
    for (const auto &pair : start.langMp) {
        if(pair.first == start.startLang) continue; //开头符号已经给编号了
        // 将左部规则转换为 QString
        QString leftSide = QString::fromStdString(pair.first);

        // 遍历右部的所有规则
        for (const auto &rule : pair.second) {
            // 将右部的每一条规则转换为 QString
            QString rightSide = QString::fromStdString(join(rule, ' ')); // 将 vector<string> 转为单个字符串，中间用空格分隔

            // 格式化为 "左部规则 -> 右部规则"
            QString line = leftSide + " -> " + rightSide;

            //记录产生式的编号
            ItemLR0 item = {pair.first, rule,0};
            GramId[item] = idCounter++;

            // 将格式化后的文法规则添加到 grammerLines 中
            grammerLines.append(line);
        }
    }
    // 将 grammerLines 内容设置到 GrammerText 控件中
    ui->GrammerText->setPlainText(grammerLines.join('\n'));
}

// 辅助函数：将 vector<string> 转换为以分隔符连接的字符串
std::string MainWindow::join(const std::vector<std::string> &vec, char delimiter) {
    if (vec.empty()) return "";

    std::string result;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        result += vec[i];
        result += delimiter;
    }
    result += vec.back();
    return result;
}

//展示first集合。
void MainWindow::showFirst()
{
    // 如果不是正确的文法，那么弹出框，标明是死递归
   if (!start.isRightGram) {
       QMessageBox::information(this, tr("错误"), tr("该文法错误,存在死递归!"));
       return;
   }

   // 获取 First 集合的大小来设置表格行数
   int rowCount = start.firstSet.size();
   ui->FirstText->setRowCount(rowCount); //设置行数
   ui->FirstText->setColumnCount(2); //设置列数

   // 设置表格头部
   ui->FirstText->setHorizontalHeaderLabels({tr("非终结符"), tr("First集")});

   // 填充表格内容
   int row = 0;
   for (const auto &pair : start.firstSet) {
       // 将左部非终结符和其 first 集合格式化为字符串
       QString nonTerminal = QString::fromStdString(pair.first);

       QString firstSetStr = "{ ";
       QStringList firstSetItems;
       for (const auto &item : pair.second) {
           firstSetItems.append(QString::fromStdString(item));
       }

       // 将 `QStringList` 转换为以逗号分隔的字符串
       firstSetStr += firstSetItems.join(", ") + " }";

       // 设置每一行的内容
       ui->FirstText->setItem(row, 0, new QTableWidgetItem(nonTerminal));
       ui->FirstText->setItem(row, 1, new QTableWidgetItem(firstSetStr));

       row++;
   }

   // 调整列宽以适应内容
   ui->FirstText->resizeColumnsToContents();
}

//展示follow集合。
void MainWindow::showFollow()
{

    // 获取 Follow 集合的大小来设置表格行数
    int rowCount = start.followSet.size();
    ui->FollowText->setRowCount(rowCount);
    ui->FollowText->setColumnCount(2);

    // 设置表格头部
    ui->FollowText->setHorizontalHeaderLabels({tr("非终结符"), tr("Follow集")});

    // 填充表格内容
    int row = 0;
    for (const auto &pair : start.followSet) {
        // 将左部非终结符和其 follow 集合格式化为字符串
        QString nonTerminal = QString::fromStdString(pair.first);

        QString followSetStr = "{ ";
        QStringList followSetItems;
        for (const auto &item : pair.second) {
            followSetItems.append(QString::fromStdString(item));
        }

        // 将 `QStringList` 转换为以逗号分隔的字符串
        followSetStr += followSetItems.join(", ") + " }";

        // 设置每一行的内容
        ui->FollowText->setItem(row, 0, new QTableWidgetItem(nonTerminal));
        ui->FollowText->setItem(row, 1, new QTableWidgetItem(followSetStr));

        row++;
    }

    // 调整列宽以适应内容
    ui->FollowText->resizeColumnsToContents();
}

//展示是否文SLR1的分析结果
void MainWindow::judgeSLR1()
{
    // 如果不是正确的文法，那么弹出框，告知不能进行分析
   if (!start.isRightGram) {
       QMessageBox::information(this, tr("错误"), tr("该文法错误,不可进行分析!"));
       return;
   }
   //如果还没有进行分析
   if (start.langMp.empty()) {
       QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法判断是否为SLR1文法!"));
       return;
   }

   // 调用 IsSLR1 判断是否为 SLR1 文法
   string result = start.IsSLR1();

   // 将结果转换为 QString 并显示到 SLRText 控件中
   ui->SLRText->setPlainText(QString::fromStdString(result));

}

//展示LR0的DFA状态表
void MainWindow::showLR0DFA()
{
    // 如果不是正确的文法，那么弹出框，告知不能进行分析
    if (!start.isRightGram) {
        QMessageBox::information(this, tr("错误"), tr("该文法错误,不可进行分析!"));
        return;
    }
    // 如果还没有进行分析
    if (start.LR0DfaStates.empty()) {
        QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法展示LR0 DFA表!"));
        return;
    }

    // 设置表格的行数
    int rowCount = start.LR0DfaStates.size();
    ui->LR0Text->setRowCount(rowCount);

    // 计算表格的列数：状态ID + 项目集 + 所有的符号列
    QSet<QString> allSymbols;
    for (const auto &statePair : start.LR0TransTable) {
        for (const auto &transPair : statePair.second) {
            allSymbols.insert(QString::fromStdString(transPair.first));
        }
    }

    // 设置表格列数：状态ID, 项目集, 及所有符号列
    ui->LR0Text->setColumnCount(2 + allSymbols.size());
    QStringList headerLabels = {tr("状态ID"), tr("项目集")};
    for (const auto &symbol : allSymbols) {
        headerLabels.append(symbol);
    }
    ui->LR0Text->setHorizontalHeaderLabels(headerLabels);

    // 填充表格内容
    int row = 0;
    for (const auto &statePair : start.LR0DfaStates) {
        int stateID = statePair.first;
        const auto &itemSet = statePair.second;

        // 将项目集格式化为字符串
        QString itemSetStr;
        for (const auto &item : itemSet) {
            QString itemStr = QString::fromStdString(item.left) + " -> ";
            for (int i = 0; i < item.right.size(); ++i) {
                if (i == item.dotPos) {
                    itemStr += ".";
                }
                itemStr += QString::fromStdString(item.right[i]) + " ";
            }
            if (item.dotPos == item.right.size()) {
                itemStr += ".";
            }
            itemSetStr += itemStr.trimmed() + "  ";
        }

        // 设置状态ID和项目集
        ui->LR0Text->setItem(row, 0, new QTableWidgetItem(QString::number(stateID)));
        ui->LR0Text->setItem(row, 1, new QTableWidgetItem(itemSetStr.trimmed()));

        // 获取当前状态的转移信息
        if (start.LR0TransTable.find(stateID) != start.LR0TransTable.end()) {
            const auto &transitions = start.LR0TransTable[stateID];
            int col = 2; // 从第三列开始填充符号信息
            for (const auto &transPair : transitions) {
                QString symbol = QString::fromStdString(transPair.first);
                int nextState = transPair.second;
                // 找到符号对应的列索引
                int symbolIndex = headerLabels.indexOf(symbol);
                if (symbolIndex != -1) {
                    ui->LR0Text->setItem(row, symbolIndex, new QTableWidgetItem(QString::number(nextState)));
                }
            }
        }

        ++row;
    }

    // 调整列宽以适应内容
    ui->LR0Text->resizeColumnsToContents();
}

//展示LR1的DFA表
void MainWindow::showLR1DFA()
{
    // 如果不是正确的文法，那么弹出框，告知不能进行分析
    if (!start.isRightGram) {
        QMessageBox::information(this, tr("错误"), tr("该文法错误,不可进行分析!"));
        return;
    }
    // 如果还没有进行分析
    if (start.LR1DfaStates.empty()) {
        QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法展示LR1 DFA表!"));
        return;
    }

    // 设置表格的行数
    int rowCount = start.LR1DfaStates.size();
    ui->LR1DfaText->setRowCount(rowCount);

    // 计算表格的列数：状态ID + 项目集 + 所有的符号列
    QSet<QString> allSymbols;
    for (const auto &statePair : start.LR1TransTable) {
        for (const auto &transPair : statePair.second) {
            allSymbols.insert(QString::fromStdString(transPair.first));
        }
    }

    // 设置表格列数：状态ID, 项目集, 及所有符号列
    ui->LR1DfaText->setColumnCount(2 + allSymbols.size());
    QStringList headerLabels = {tr("状态ID"), tr("项目集")};
    for (const auto &symbol : allSymbols) {
        headerLabels.append(symbol);
    }
    ui->LR1DfaText->setHorizontalHeaderLabels(headerLabels);

    // 填充表格内容
    int row = 0;
    for (const auto &statePair : start.LR1DfaStates) {
        int stateID = statePair.first;
        const auto &itemSet = statePair.second;

        // 将项目集格式化为字符串
        QString itemSetStr;
        for (const auto &item : itemSet) {
            QString itemStr = "[" + QString::fromStdString(item.left) + " -> ";
            for (int i = 0; i < item.right.size(); ++i) {
                if (i == item.dotPos) {
                    itemStr += ".";
                }
                itemStr += QString::fromStdString(item.right[i]) + " ";
            }
            if (item.dotPos == item.right.size()) {
                itemStr += ".";
            }
            itemStr += ", ";

            itemStr += QString::fromStdString(item.lookahead) + "]";

            itemSetStr += itemStr.trimmed() + " ";
        }

        // 设置状态ID和项目集
        ui->LR1DfaText->setItem(row, 0, new QTableWidgetItem(QString::number(stateID)));
        ui->LR1DfaText->setItem(row, 1, new QTableWidgetItem(itemSetStr.trimmed()));

        QSet<QString> terminalSymbols;  // 终结符号
        QSet<QString> nonTerminalSymbols;  // 非终结符号

        // 获取当前状态的转移信息
        if (start.LR1TransTable.find(stateID) != start.LR1TransTable.end()) {
            const auto &transitions = start.LR1TransTable[stateID];
            int col = 2; // 从第三列开始填充符号信息
            for (const auto &transPair : transitions) {
                QString symbol = QString::fromStdString(transPair.first);
                int nextState = transPair.second;
                // 找到符号对应的列索引
                int symbolIndex = headerLabels.indexOf(symbol);
                if (symbolIndex != -1) {
                    ui->LR1DfaText->setItem(row, symbolIndex, new QTableWidgetItem(QString::number(nextState)));
                }
            }
        }

        ++row;
    }

    // 调整列宽以适应内容
    ui->LR1DfaText->resizeColumnsToContents();
}

//展示LR1的分析表
void MainWindow::showLR1Table()
{

    //移进规则记录咱们用TransTable
    //规约记录咱们用GramId，和当前规约项目的整个式子比较。（只比较左部和右部，不比较"."和lookahead)
    // 如果不是正确的文法，那么弹出框，告知不能进行分析
    if (!start.isRightGram) {
        QMessageBox::information(this, tr("错误"), tr("该文法错误,不可进行分析!"));
        return;
    }
    // 如果还没有进行分析
    if (start.LR1DfaStates.empty()) {
        QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法展示LR1 分析表!"));
        return;
    }

    // 设置表格的行数
    int rowCount = start.LR1DfaStates.size();
    ui->LR1ToTabel->setRowCount(rowCount);

    // 计算表格的列数：状态ID + 所有的符号列
    QSet<QString> terminal;
    QSet<QString> nonTerminal;

    for (const auto &statePair : start.LR1TransTable) {
        for (const auto &transPair : statePair.second) {
            if (transPair.first == "@") continue;
            if (start.langMp.find(transPair.first) == start.langMp.end()) { // 如果是终结符号
                terminal.insert(QString::fromStdString(transPair.first));
            } else {
                nonTerminal.insert(QString::fromStdString(transPair.first));
            }
        }
    }
    // 手动加一个转移规约终结符
    terminal.insert("$");

    // 设置表格列数：状态ID + 所有符号列
    ui->LR1ToTabel->setColumnCount(1 + terminal.size() + nonTerminal.size());

    QStringList headerLabels = {tr("状态ID")};  // 初始化标题
    for (const auto &TerminalSymbol : terminal) { // 增加终结符
        headerLabels.append(TerminalSymbol);
    }
    for (const auto &nonTerminalSymbol : nonTerminal) { // 增加非终结符号
        headerLabels.append(nonTerminalSymbol);
    }
    ui->LR1ToTabel->setHorizontalHeaderLabels(headerLabels); // 设置标题

    // 设置每行的状态ID内容
    for (const auto& item : start.LR1DfaStates) {
        int stateId = item.first;
        // 在第一列填入 stateId
        ui->LR1ToTabel->setItem(stateId, 0, new QTableWidgetItem(QString::number(stateId)));
    }

    // 处理移进部分
    for (const auto& item : start.LR1DfaStates) { // 获取每个状态的项目集合
        int stateId = item.first;
        for (const auto& states : start.LR1TransTable[stateId]) { // 遍历该状态的所有转移
            string symbol = states.first;
            int nextState = states.second; // 下一个状态ID号

            if (start.langMp.find(symbol) == start.langMp.end()) {  // 如果是终结符号
                // 找到符号对应的列索引
                int col = terminal.values().indexOf(QString::fromStdString(symbol)) + 1;  // 无项目集列，调整索引
                ui->LR1ToTabel->setItem(stateId, col, new QTableWidgetItem("s" + QString::number(nextState)));
            } else {  // 如果是非终结符号
                int col = terminal.size() + nonTerminal.values().indexOf(QString::fromStdString(symbol)) + 1;
                ui->LR1ToTabel->setItem(stateId, col, new QTableWidgetItem(QString::number(nextState)));
            }
        }
    }

    // 处理规约部分
    for (const auto& item : start.LR1DfaStates) {
        int stateId = item.first;
        for (const auto& Gram : item.second) { // 遍历该状态的项目集
            if (Gram.right.size() == 1 && Gram.right[0] == "@") continue; // 跳过空产生式
            if (Gram.dotPos == Gram.right.size()) { // 如果是规约项目
                string finalSymbol = Gram.lookahead; // 获取规约符号
                ItemLR0 WhichGram = {Gram.left, Gram.right, 0}; // 获取与产生式比较的内容
                int getGramID = GramId[WhichGram];

                // 找到规约符号对应的列索引
                int col = terminal.values().indexOf(QString::fromStdString(finalSymbol));

                if(getGramID == 1)//第一条规约式子
                    ui->LR1ToTabel->setItem(stateId, col + 1, new QTableWidgetItem("ACC"));
                else
                    // 填入："r+getGramID"
                    ui->LR1ToTabel->setItem(stateId, col + 1, new QTableWidgetItem("r" + QString::number(getGramID)));
            }
        }
    }

}

