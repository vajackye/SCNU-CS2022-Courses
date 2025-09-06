/***************************************************************
 * 版权所有 (C) 20222121007 计算机科学与技术师范 黄泽基
 * 保留所有权利
 *
 * 模块名称：taskonewindow.cpp
 * 模块功能：本模块用于实现任务一窗口交互
 *
 * 当前版本：v1.0
 * 作    者：黄泽基
 * 完成日期：2025年5月6日
 *
 * 修改历史：
 * 版本号     修改者     修改日期     修改内容
 * v1.0       黄泽基       2025/05/06   初始版本，完成模块功能实现
 *
 ***************************************************************/

#include "taskonewindow.h"
#include "QHBoxLayout"
#include "QTextEdit"

extern MainWindow *g_mainWindow; // 全局管理一下主窗口指针

/**
 * @brief TaskOneWindow::TaskOneWindow 子窗口图形化操作
 * @param parent
 */
TaskOneWindow::TaskOneWindow(QWidget *parent) : QWidget(parent)
{

    CodeMap.clear(); //清除全局映射表

    // 总体大布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 顶部按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonLayout);

    // 添加按钮
    QPushButton *backButton = new QPushButton("返回", this);
    QPushButton *inputFileBtn = new QPushButton("读入文件", this);
    QPushButton *saveFileBtn = new QPushButton("保存文件", this);
    QPushButton *analysisBtn = new QPushButton("开始分析", this);
    QPushButton *selNfaBtn = new QPushButton("转NFA", this);
    QPushButton *selDfaBtn = new QPushButton("转DFA", this);
    QPushButton *selMinDfaBtn = new QPushButton("DFA最小化", this);
    QPushButton *genSourceCode = new QPushButton("词法生成", this);
    QPushButton *showWdCode = new QPushButton("编码展示", this);

    // 把按钮加到按钮布局里
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(inputFileBtn);
    buttonLayout->addWidget(saveFileBtn);
    buttonLayout->addWidget(analysisBtn);
    buttonLayout->addWidget(selNfaBtn);
    buttonLayout->addWidget(selDfaBtn);
    buttonLayout->addWidget(selMinDfaBtn);
    buttonLayout->addWidget(genSourceCode);
    buttonLayout->addWidget(showWdCode);

    // 分三列的展示布局
    QHBoxLayout *displayLayout = new QHBoxLayout();
    mainLayout->addLayout(displayLayout);

    // ---------- 左列：正则展示 ----------
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QLabel *regexLabel = new QLabel("正则表达式展示");
    regexDisplay = new QTextEdit(this);  // 可读可写
    leftLayout->addWidget(regexLabel);
    leftLayout->addWidget(regexDisplay);

    // ---------- 中列：源代码展示 ----------
    QVBoxLayout *middleLayout = new QVBoxLayout();
    QLabel *srcLabel = new QLabel("源代码展示");
    sourceDisplay = new QTextEdit(this);
    middleLayout->addWidget(srcLabel);
    middleLayout->addWidget(sourceDisplay);

    // ---------- 右列：编码展示 ----------
    QVBoxLayout *rightLayout = new QVBoxLayout();
    QLabel *codeLabel = new QLabel("编码展示");
    codeDisplay = new QTableWidget(this);
    codeDisplay->setColumnCount(2);
    codeDisplay->setHorizontalHeaderLabels(QStringList() << "编码" << "具体值");
    codeDisplay->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自动拉伸列宽
    codeDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不可编辑
    rightLayout->addWidget(codeLabel);
    rightLayout->addWidget(codeDisplay);

    // 加入三列到主展示布局
    displayLayout->addLayout(leftLayout);
    displayLayout->addLayout(middleLayout);
    displayLayout->addLayout(rightLayout);

    // 设置每个区域的最小宽度
    regexDisplay->setMinimumWidth(200);
    codeDisplay->setMinimumWidth(200);
    sourceDisplay->setMinimumWidth(600);
    // 设置每个区域的最小高度
    regexDisplay->setMinimumHeight(650);
    codeDisplay->setMinimumHeight(650);
    sourceDisplay->setMinimumHeight(650);

    //创建连接
    connect(backButton, &QPushButton::clicked, this, &TaskOneWindow::backToMain);
    connect(inputFileBtn, &QPushButton::clicked, this, &TaskOneWindow::inputFile);
    connect(saveFileBtn, &QPushButton::clicked, this, &TaskOneWindow::saveFile);
    connect(analysisBtn, &QPushButton::clicked, this, &TaskOneWindow::analysisRegex);
    connect(selNfaBtn, &QPushButton::clicked, this, &TaskOneWindow::selectNFA);
    connect(selDfaBtn, &QPushButton::clicked, this, &TaskOneWindow::selectDFA);
    connect(selMinDfaBtn, &QPushButton::clicked, this, &TaskOneWindow::selectMinDFA);
    connect(genSourceCode, &QPushButton::clicked, this, &TaskOneWindow::generateSourceCode);
    connect(showWdCode, &QPushButton::clicked, this, &TaskOneWindow::showWordCode);

}

/**
 * @brief TaskOneWindow::backToMain 返回主页面
 */
void TaskOneWindow::backToMain()
{
    g_mainWindow->show();
    this->close();
}

/**
 * @brief TaskOneWindow::inputFile 打开正则文件
 */
void TaskOneWindow::inputFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开正则文件", "", "Text Files (*.txt);;All Files (*)");
    if(!fileName.isEmpty()) {
        QFile file(fileName); //读取文件内容
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString content = file.readAll();
            regexDisplay->clear(); //先清空
            regexDisplay->setPlainText(content);
            file.close();
        }
    }
}

/**
 * @brief TaskOneWindow::saveFile 将正则文件进行保存
 */
void TaskOneWindow::saveFile()
{
    // 获取当前正则内容
    QString content = regexDisplay->toPlainText();

    if(content.isEmpty()) {
        QMessageBox::warning(this,"注意","要保存的正则内容为空!");
        return;
    }
    // 弹出保存文件对话框
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存正则文件"), "", tr("文本文件 (*.txt);;所有文件 (*)"));
    if (fileName.isEmpty()) {
       return; // 用户取消保存
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
       QMessageBox::warning(this, tr("保存失败"), tr("无法打开文件:\n%1").arg(file.errorString()));
       return;
    }

    QTextStream out(&file);
    out << content;
    file.close();

    QMessageBox::information(this, tr("保存成功"), tr("文件已成功保存至:\n%1").arg(fileName));
}

/**
 * @brief TaskOneWindow::analysisRegex 开始分析
 */
void TaskOneWindow::analysisRegex()
{
    //先清空旧数据
    p.clear();
    nf.clear();
    df.clear();
    mindf.clear();
    doneNfa = false;
    doneDfa = false;
    donePre = false;
    doneMinDfa = false;

    //开始转后缀表达式
    QString text = regexDisplay->toPlainText();// 获取完整文本框内容
    if(text.isEmpty()) {
        QMessageBox::warning(this, "警告","请先点击导入正则表达式!");
        return ;
    }
    QStringList lines = text.split('\n'); // 按行分割，跳过空行

    for (const QString &line : lines) {
        QString trimmed = line.trimmed();  // 去除前后空白符
        if (trimmed.isEmpty()) continue;  // 跳过空行
        std::string stdLine = trimmed.toStdString();
        p.predoName(stdLine);
    }
    p.dealAllPoint(); //加连接符号
    p.dealAllPostfix(); //转后缀表达式
    donePre = true;

    //增加处理：CodeMap映射
    for(const auto &pair: p.ruleMap) {
        std::string name = pair.first;
        if(name.size() <= 0) continue;
        if(!name[0] == '_') continue;
        CodeMap[pair.second.code] = name.substr(1); //全局映射表使用
    }
}

/**
 * @brief TaskOneWindow::selectNFA 可视化NFA
 */
void TaskOneWindow::selectNFA()
{
    if(!donePre)
    {
        QMessageBox::warning(this, "警告","请先点击分析按钮!");
        return ;
    }
    //先批量处理所有后缀表达式转NFA
    for (const auto& rule : p.postfixMap) {
        nf.finalNFA[rule.first] = nf.buildNFA(rule.second,rule.first);
    }
    doneNfa = true; //已经执行过nfa，允许执行dfa
    auto *dialog = new NodeTable(nf.finalNFA, df.finalDFA, df.miniNodeMap,mindf.finalMiniDFA, nf.symbols, 1, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动delete
    dialog->show(); // 不用 exec()，支持异步打开
}

/**
 * @brief TaskOneWindow::selectDFA 可视化DFA
 */
void TaskOneWindow::selectDFA()
{
    if(!doneNfa)
    {
        QMessageBox::warning(this,"警告", "请先执行转NFA操作!");
        return ;
    }
    //转DFA
    std::unordered_map<std::string, std::unordered_set<std::string>> tableSymbol;
    for (const pair<string, TokenRule> pr : p.ruleMap) {
        //过滤出可转DFA的部分
        if (!pr.second.generateDFA)continue;
        //是则进行转DFA
        tableSymbol[pr.first] = nf.symbols[pr.first];
        NFA fn = nf.finalNFA[pr.first];
        unordered_set<string> symbol = nf.symbols[pr.first];
        //转DFA
        df.NTDFA(pr.first, fn, symbol);
    }
    doneDfa = true;
    auto *dialog = new NodeTable(nf.finalNFA, df.finalDFA, df.miniNodeMap,mindf.finalMiniDFA, tableSymbol, 2, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

/**
 * @brief TaskOneWindow::selectMinDFA 可视化最小化DFA
 */
void TaskOneWindow::selectMinDFA()
{
    if(!doneDfa)
    {
        QMessageBox::warning(this,"警告", "请先执行转DFA操作!");
        return ;
    }
    //DFA批量最小化
    std::unordered_map<std::string, std::unordered_set<std::string>> tableSymbol;
    for (const auto& pair : df.miniNodeMap) {
        const string& ruleName = pair.first;
        const vector<DFANode>& dfaNodes = pair.second;
        //转移符号
        unordered_set<string> symbols = df.finalDFA[ruleName].symbol;
        tableSymbol[ruleName] = symbols;
        //最小化处理
        mindf.minimize(ruleName, dfaNodes, symbols);
        //构建转换表
        mindf.buildMinimizedDFA(ruleName);
    }
    doneMinDfa = true;
    auto *dialog = new NodeTable(nf.finalNFA, df.finalDFA, df.miniNodeMap, mindf.finalMiniDFA, tableSymbol, 3, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

/**
 * @brief TaskOneWindow::generateSourceCode 生成词法分析源程序
 */
void TaskOneWindow::generateSourceCode()
{
    if(!doneMinDfa)
    {
        QMessageBox::warning(this,"警告", "请先执行转最小化DFA操作!");
        return ;
    }
    // 获取词法分析源程序代码
    QString lexerCode = QString::fromStdString(lex.generateLexerCode(mindf.finalMiniDFA, p.ruleMap));

    sourceDisplay->setPlainText(lexerCode);
    // 写入路径
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save Generated Code",
                                                    QDir::currentPath(),
                                                    "Cpp Files (*.cpp);;Text Files (*.txt)");
    // 取消
    if (fileName.isEmpty())
    {
        return;
    }

    // 打开文件写
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "错误", "无法打开文件写 " + file.errorString());
        return;
    }

    // 写入文件
    QTextStream out(&file);
    out << lexerCode;

    // 关闭文件
    file.close();

    // 导出成功
    QMessageBox::information(this, "成功", "文件已导出到：" + fileName);
}

/**
 * @brief TaskOneWindow::showWordCode 将词法分析源程序可视化展示并保存到文件中
 */
void TaskOneWindow::showWordCode()
{
    QString filePath = QFileDialog::getOpenFileName(this, "打开词法分析输出文件", QDir::currentPath(), "Text Files (*.txt *.lex *.minic)");
    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件读取 " + file.errorString());
        return;
    }

    codeDisplay->setRowCount(0); // 清空表格
    QTextStream in(&file);
    int row = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        // 拆分空格
        QStringList parts = line.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);
        for (int i = 0; i + 1 < parts.size(); i += 2) {
            QString type = parts[i];
            QString value = parts[i + 1];

            codeDisplay->insertRow(row);
            codeDisplay->setItem(row, 0, new QTableWidgetItem(type));
            codeDisplay->setItem(row, 1, new QTableWidgetItem(value));
            row++;
        }
    }

    file.close();
}

