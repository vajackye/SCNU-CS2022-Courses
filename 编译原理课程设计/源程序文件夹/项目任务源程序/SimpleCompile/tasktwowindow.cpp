/***************************************************************
 * 版权所有 (C) 20222121007 计算机科学与技术师范 黄泽基
 * 保留所有权利
 *
 * 模块名称：tasktwowindow.cpp
 * 模块功能：本模块用于实现任务二窗口交互
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

#include "tasktwowindow.h"

extern MainWindow *g_mainWindow; // 全局管理一下主窗口指针

/**
 * @brief TaskTwoWindow::TaskTwoWindow 窗口操作函数
 * @param parent
 */
TaskTwoWindow::TaskTwoWindow(QWidget *parent) : QWidget(parent)
{
    // 总体大布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // === 使用说明 + 分割线区域 ===
    QVBoxLayout *headerLayout = new QVBoxLayout(); // 上方头部区域：说明按钮 + 分割线
    QPushButton *helpBtn = new QPushButton("使用说明", this);
    helpBtn->setFixedWidth(100);
    helpBtn->setCursor(Qt::PointingHandCursor);
    headerLayout->addWidget(helpBtn, 0, Qt::AlignLeft);

    // 分割线
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);     // 水平线
    line->setFrameShadow(QFrame::Sunken);  // 下凹效果
    headerLayout->addWidget(line);

    // 将 headerLayout 插入到主布局最前面
    mainLayout->insertLayout(0, headerLayout);

    connect(helpBtn, &QPushButton::clicked, this, [=]() {
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle("使用说明");

        QTextEdit *textEdit = new QTextEdit(dialog);
        textEdit->setText(tr("【TaskTwo 使用说明】\n\n"
                             "1. 点击“读入文法文件”读取文法\n"
                             "2. 点击“开始分析”处理文法，生成扩展文法、first/follow集\n"
                             "3. 查看 LR0 / SLR1 / LR1 的 DFA 图及分析表\n"
                             "4. 点击“读入源程序文件”，再点击“分析源程序”\n"
                             "5. 可查看语法分析树\n\n"
                             "注意事项：\n"
                             "• 文法符号间需用空格隔开\n"
                             "• 文法不能左递归或存在二义性"
                             "• 如果要查看语法树，请先导入语义规则，具体规则见readme.txt"));
        textEdit->setReadOnly(true);

        QVBoxLayout *layout = new QVBoxLayout(dialog);
        layout->addWidget(textEdit);
        dialog->setLayout(layout);
        dialog->resize(500, 300);
        dialog->exec();
    });

    // === 主体按钮 + 内容展示区域 ===
    // 顶部按钮行
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonLayout);

    // 添加按钮
    QPushButton *backButton = new QPushButton("返回", this);
    QPushButton *inputFileBtn = new QPushButton("读入文法文件", this);
    QPushButton *analysisBtn = new QPushButton("开始分析", this);
    QPushButton *showFirstBtn = new QPushButton("展示First集合", this);
    QPushButton *showFollowBtn = new QPushButton("展示Follow集合", this);
    QPushButton *showLR0Btn = new QPushButton("展示LR0-DFA", this);
    QPushButton *judgeSLR1Btn = new QPushButton("判断SLR1", this);
    QPushButton *showLR1Btn = new QPushButton("展示LR1-DFA", this);
    QPushButton *showLR1ATb = new QPushButton("展示LR1-分析表", this);
    QPushButton *inputSrcBtn = new QPushButton("读入编码文件", this);
    QPushButton *inputActionBtn = new QPushButton("读入语义动作表", this);
    QPushButton *showPrcBtn = new QPushButton("分析编码", this);
    QPushButton *showTree = new QPushButton("展示语法树", this);

    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(inputFileBtn);
    buttonLayout->addWidget(analysisBtn);
    buttonLayout->addWidget(showFirstBtn);
    buttonLayout->addWidget(showFollowBtn);
    buttonLayout->addWidget(showLR0Btn);
    buttonLayout->addWidget(judgeSLR1Btn);
    buttonLayout->addWidget(showLR1Btn);
    buttonLayout->addWidget(showLR1ATb);
    buttonLayout->addWidget(inputSrcBtn);
    buttonLayout->addWidget(inputActionBtn);
    buttonLayout->addWidget(showPrcBtn);
    buttonLayout->addWidget(showTree);

    // ================== 三列横排布局 ====================
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    mainLayout->addLayout(horizontalLayout);

    // -------- 左列：上 文法展示，下 扩展文法 ----------
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QLabel *grammarLabel = new QLabel("文法文件内容");
    grammarDisplay = new QTextEdit(this);
    leftLayout->addWidget(grammarLabel);
    leftLayout->addWidget(grammarDisplay);

    QLabel *externGram = new QLabel("扩展文法集展示");
    externGrDis = new QTextEdit(this);
    leftLayout->addWidget(externGram);
    leftLayout->addWidget(externGrDis);
    horizontalLayout->addLayout(leftLayout);

    // -------- 中列：上 SLR1，下 源程序 ----------
    QVBoxLayout *middleLayout = new QVBoxLayout();

    // 上：SLR1 判断结果
    QLabel *slr1Label = new QLabel("SLR(1) 判断结果");
    slr1Result = new QTextEdit(this);
    slr1Result->setMaximumHeight(100);
    middleLayout->addWidget(slr1Label);
    middleLayout->addWidget(slr1Result);

    // 下：源程序文件展示
    QLabel *sourceLabel = new QLabel("编码文件内容");
    sourceDisplay = new QTableWidget(this);
    sourceDisplay->setColumnCount(2);
    sourceDisplay->setHorizontalHeaderLabels(QStringList() << "编码" << "具体值");
    sourceDisplay->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自动拉伸列宽
    sourceDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不可编辑
    middleLayout->addWidget(sourceLabel);
    middleLayout->addWidget(sourceDisplay);

    horizontalLayout->addLayout(middleLayout);

    // -------- 右列：语法树展示 ----------
    QVBoxLayout *rightLayout = new QVBoxLayout();
    QLabel *treeLabel = new QLabel("语法树展示");

    treeWidget = new QTreeWidget(this);
    treeWidget->setColumnCount(1);

    rightLayout->addWidget(treeLabel);
    rightLayout->addWidget(treeWidget);

    horizontalLayout->addLayout(rightLayout);

    // 设置各区最小宽高
    grammarDisplay->setMinimumWidth(250);
    sourceDisplay->setMinimumHeight(500);
//    treeWidget->setMinimumWidth(250);
//    treeWidget->setMinimumHeight(500);

    connect(backButton, &QPushButton::clicked, this, &TaskTwoWindow::backToMain);
    connect(inputFileBtn, &QPushButton::clicked, this, &TaskTwoWindow::inputFile);
    connect(analysisBtn, &QPushButton::clicked, this, &TaskTwoWindow::analysisGram);
    connect(showFirstBtn, &QPushButton::clicked, this, &TaskTwoWindow::showFirst);
    connect(showFollowBtn, &QPushButton::clicked, this, &TaskTwoWindow::showFollow);
    connect(showLR0Btn, &QPushButton::clicked, this, &TaskTwoWindow::showLR0Dfa);
    connect(judgeSLR1Btn, &QPushButton::clicked, this, &TaskTwoWindow::judgeSLR1);
    connect(showLR1Btn, &QPushButton::clicked, this, &TaskTwoWindow::showLR1Dfa);
    connect(showLR1ATb, &QPushButton::clicked, this, &TaskTwoWindow::showLR1Tab);
    connect(inputSrcBtn, &QPushButton::clicked, this, &TaskTwoWindow::inputSrc);
    connect(inputActionBtn, &QPushButton::clicked, this, &TaskTwoWindow::getAction);
    connect(showPrcBtn, &QPushButton::clicked, this, &TaskTwoWindow::showProc);
    connect(showTree, &QPushButton::clicked, this, &TaskTwoWindow::showTree);
}


/**
 * @brief TaskTwoWindow::backToMain
 * 返回主页面函数
 */
void TaskTwoWindow::backToMain()
{
    g_mainWindow->show();
    this->close();
}

/**
 * @brief TaskTwoWindow::inputFile
 * 处理文法输入文件
 */
void TaskTwoWindow::inputFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文法文件", "", "Text Files (*.txt);;All Files (*)");
    if(!fileName.isEmpty()) {
        QFile file(fileName); //读取文件内容
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString content = file.readAll();
            grammarDisplay->setPlainText(content);
            file.close();
        }
    }
}


/**
 * @brief TaskTwoWindow::analysisGram
 * 处理文法并分析文法
 */
void TaskTwoWindow::analysisGram() {
    // 从界面获取文法输入内容
    QStringList lines = grammarDisplay->toPlainText().split('\n', QString::SkipEmptyParts);
    //如果还没有导入文法
    if (lines.isEmpty()) {
        QMessageBox::information(this, tr("注意"), tr("请先导入文法!"));
        return;
    }

    lr.init(); //先清空所有旧数据
    tokens.clear(); //token也清除
    GraActionMap.clear(); //语义动作也清除
    bool flag = true; //标记是否为第一条文法

    for(const QString &line : lines) {
        QString clearSpaceLine = line.trimmed();
        string ss = clearSpaceLine.toStdString();
        if(ss.empty()) continue;
        string lrname = lr.splitLang(ss);
        if(flag) {
            flag = false;
            lr.startLang = lrname; //存储文法开始符号
        }
        lr.lgName.push_back(lrname); //存储所有非终结符号
    }


    // 收集所有终结符
    lr.collectGrammarTerminals();

    // 计算 FIRST/FOLLOW 集
    lr.getFirstSet();
    lr.getFollowSet();

    // 判断文法正确性
    lr.isRightGram = lr.judgeDieFirst();

    // 判断是否需新增 S' -> S 规则
    lr.newStart();
    // 展示扩充文法
    showExternGram();

    // 构建 LR(0) 自动机和 LR(1) 自动机
    lr.DfaLR0();
    lr.DfaLR1();

    // 构建 LR1 分析表
    lr.buildGramId();
    lr.buildLR1Table();

    return;
}

/**
 * @brief TaskTwoWindow::showExternGram
 * 对扩充文法集进行展示
 */
void TaskTwoWindow::showExternGram()
{
    // 清空原有文本
    externGrDis->clear();

    // 获取LR1 对象的 langMp
    QStringList grammerList;
    //给每条产生式一个编号
    int idCount = 1;

    //给首个产生式最小编号
    const auto & firstId = lr.langMp[lr.startLang];
    QString left = QString::fromStdString(lr.startLang);
    QString right = QString::fromStdString(join(firstId[0], ' '));

    //格式化
    QString line = left + " -> " + right;

    //记录产生式编号
    ItemLR0 item = {lr.startLang, firstId[0], 0};
    lr.GramId[item] = idCount++;

    //将格式化后文法加导grammerLines中
    grammerList.append(line);

    //遍历langMp 并将每一行文法撰文QString
    for(const auto &pair : lr.langMp) {
        if(pair.first == lr.startLang) continue;
        //左部规则转为QString
        QString left = QString::fromStdString(pair.first);

        //遍历所有右部规则
        for(const auto & rule : pair.second) {
            QString right = QString::fromStdString(join(rule,' '));

            QString line = left + " -> " + right;

            ItemLR0 item = {pair.first, rule, 0};
            lr.GramId[item] = idCount++;

            grammerList.append(line);
        }
        externGrDis->setPlainText(grammerList.join('\n'));
    }
}

/**
 * @brief MainWindow::join 辅助函数：将 vector<string> 转换为以分隔符连接的字符串
 * @param vec
 * @param delimiter
 * @return
 */
std::string TaskTwoWindow::join(const std::vector<std::string> &vec, char delimiter) {
    if (vec.empty()) return "";

    std::string result;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        result += vec[i];
        result += delimiter;
    }
    result += vec.back();
    return result;
}

/**
 * @brief TaskTwoWindow::showFirst
 * 展示文法的first集合
 */
void TaskTwoWindow::showFirst()
{
    if (lr.LR0DfaStates.empty()) {
        QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法展示first集合!"));
        return;
    }
    // 如果文法错误，弹出提示
   if (!lr.isRightGram) {
       QMessageBox::information(this, tr("错误"), tr("该文法错误,存在死递归!"));
       return;
   }

   // 创建 GramTable 弹窗，标题为 First 集合
   auto* popup = new GramTable("First 集合", this);
   int rowCount = lr.firstSet.size();
   popup->setTable(rowCount, 2, {"非终结符", "First集"});
   QTableWidget *table = popup->getTableWidget();

   // 填充每一行
   int row = 0;
   for (const auto &pair : lr.firstSet) {
       QString nonTerminal = QString::fromStdString(pair.first);

       QStringList firstSetItems;
       for (const auto &item : pair.second) {
           firstSetItems.append(QString::fromStdString(item));
       }
       QString firstSetStr = "{ " + firstSetItems.join(", ") + " }";

       table->setItem(row, 0, new QTableWidgetItem(nonTerminal));
       table->setItem(row, 1, new QTableWidgetItem(firstSetStr));

       ++row;
   }

   // 调整列宽并展示
   table->resizeColumnsToContents();
   table->horizontalHeader()->setStretchLastSection(true);
   popup->exec();
   popup->deleteLater();
}

/**
 * @brief TaskTwoWindow::showFollow
 * 展示文法的follow集合
 */
void TaskTwoWindow::showFollow()
{
    // 创建 GramTable 弹窗，标题为 Follow 集合
    auto * popup = new GramTable("Follow 集合", this);
    int rowCount = lr.followSet.size();
    popup->setTable(rowCount, 2, {"非终结符", "Follow集"});
    QTableWidget *table = popup->getTableWidget();

    // 填充每一行
    int row = 0;
    for (const auto &pair : lr.followSet) {
        QString nonTerminal = QString::fromStdString(pair.first);

        QStringList followSetItems;
        for (const auto &item : pair.second) {
            followSetItems.append(QString::fromStdString(item));
        }
        QString followSetStr = "{ " + followSetItems.join(", ") + " }";

        table->setItem(row, 0, new QTableWidgetItem(nonTerminal));
        table->setItem(row, 1, new QTableWidgetItem(followSetStr));

        ++row;
    }

    // 调整列宽并展示
    table->resizeColumnsToContents();
    table->horizontalHeader()->setStretchLastSection(true);

    popup->exec();
    popup->deleteLater();
}

/**
 * @brief TaskTwoWindow::showLR0Dfa
 * 展示LR0DFA
 */
void TaskTwoWindow::showLR0Dfa(){
    if (lr.LR0DfaStates.empty()) {
        QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法展示LR0 DFA表!"));
        return;
    }
    if (!lr.isRightGram) {
        QMessageBox::information(this, tr("错误"), tr("该文法错误,不可进行分析!"));
        return;
    }

    // 创建弹窗表格窗口
    auto *popup = new GramTable("LR(0) DFA 状态表", this);

    // 收集所有符号（列头）
    QSet<QString> allSymbols;
    for (const auto &statePair : lr.LR0TransTable) {
        for (const auto &transPair : statePair.second) {
            allSymbols.insert(QString::fromStdString(transPair.first));
        }
    }

    // 设置列数（状态编号 + 项目集 + 所有符号）
    int colCount = 2 + allSymbols.size();
    QStringList headers = {"状态ID", "项目集"};
    for (const QString &sym : allSymbols) {
        headers.append(sym);
    }

    int rowCount = lr.LR0DfaStates.size();
    popup->setTable(rowCount, colCount, headers);

    QTableWidget *table = popup->getTableWidget();

    int row = 0;
    for (const auto &statePair : lr.LR0DfaStates) {
        int stateID = statePair.first;
        const auto &itemSet = statePair.second;

        // 设置状态ID
        table->setItem(row, 0, new QTableWidgetItem(QString::number(stateID)));

        // 构造项目集字符串
        QString itemSetStr;
        for (const auto &item : itemSet) {
            QString oneItem = QString::fromStdString(item.left) + " -> ";
            for (int i = 0; i < item.right.size(); ++i) {
                if (i == item.dotPos) {
                    oneItem += ".";
                }
                oneItem += QString::fromStdString(item.right[i]) + " ";
            }
            if (item.dotPos == item.right.size()) {
                oneItem += ".";
            }
            itemSetStr += oneItem.trimmed() + "  ";
        }

        table->setItem(row, 1, new QTableWidgetItem(itemSetStr.trimmed()));

        // 填充转移信息
        if (lr.LR0TransTable.count(stateID)) {
            const auto &trans = lr.LR0TransTable.at(stateID);
            for (const auto &pair : trans) {
                QString symbol = QString::fromStdString(pair.first);
                int targetState = pair.second;
                int colIndex = headers.indexOf(symbol);
                if (colIndex != -1) {
                    table->setItem(row, colIndex, new QTableWidgetItem(QString::number(targetState)));
                }
            }
        }

        ++row;
    }

    table->resizeColumnsToContents();
    popup->exec();
    popup->deleteLater();
}

/**
 * @brief TaskTwoWindow::judgeSLR1
 * 判别是否为SLR1
 */
void TaskTwoWindow::judgeSLR1(){
    //如果还没有进行分析
    if (lr.langMp.empty()) {
        QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法判断是否为SLR1文法!"));
        return;
    }
    // 如果不是正确的文法，那么弹出框，告知不能进行分析
   if (!lr.isRightGram) {
       QMessageBox::information(this, tr("错误"), tr("该文法错误,不可进行分析!"));
       return;
   }

   // 调用 IsSLR1 判断是否为 SLR1 文法
   QString result = QString::fromStdString(lr.IsSLR1());

   slr1Result->setPlainText(result);
}

/**
 * @brief TaskTwoWindow::showLR1Dfa
 * 展示LR1DFA
 */
void TaskTwoWindow::showLR1Dfa(){
    if (lr.LR1DfaStates.empty()) {
        QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法展示LR1 DFA表!"));
        return;
    }
    if (!lr.isRightGram) {
        QMessageBox::information(this, tr("错误"), tr("该文法错误,不可进行分析!"));
        return;
    }

    // 收集所有出现的符号作为列头
    QSet<QString> allSymbols;
    for (const auto &statePair : lr.LR1TransTable) {
        for (const auto &transPair : statePair.second) {
            allSymbols.insert(QString::fromStdString(transPair.first));
        }
    }

    // 创建表头：状态ID、项目集、各符号
    QStringList headers = {"状态ID", "项目集"};
    QList<QString> sortedSymbols = allSymbols.values();
    std::sort(sortedSymbols.begin(), sortedSymbols.end());
    headers.append(sortedSymbols);

    // 创建 GramTable 弹窗
    auto *popup = new GramTable("LR(1) DFA 状态表", this);
    popup->setTable(lr.LR1DfaStates.size(), headers.size(), headers);
    QTableWidget *table = popup->getTableWidget();

    // 填充表格内容
    int row = 0;
    for (const auto &statePair : lr.LR1DfaStates) {
        int stateID = statePair.first;
        const auto &itemSet = statePair.second;

        // 项目集字符串拼接
        QString itemSetStr;
        for (const auto &item : itemSet) {
            QString itemStr = QString::fromStdString(item.left) + " -> ";
            for (int i = 0; i < item.right.size(); ++i) {
                if (i == item.dotPos) itemStr += ".";
                itemStr += QString::fromStdString(item.right[i]) + " ";
            }
            if (item.dotPos == item.right.size()) {
                itemStr += ".";
            }
            itemStr += ", " + QString::fromStdString(item.lookahead);
            itemSetStr += "[" + itemStr.trimmed() + "]  ";
        }

        // 设置状态ID 和 项目集内容
        table->setItem(row, 0, new QTableWidgetItem(QString::number(stateID)));
        table->setItem(row, 1, new QTableWidgetItem(itemSetStr.trimmed()));

        // 填入符号转移状态
        if (lr.LR1TransTable.count(stateID)) {
            const auto &trans = lr.LR1TransTable.at(stateID);
            for (const auto &pair : trans) {
                QString symbol = QString::fromStdString(pair.first);
                int colIndex = headers.indexOf(symbol);
                if (colIndex != -1) {
                    table->setItem(row, colIndex, new QTableWidgetItem(QString::number(pair.second)));
                }
            }
        }

        ++row;
    }

    // 调整列宽，展示对齐
    table->resizeColumnsToContents();
    table->horizontalHeader()->setStretchLastSection(true);

    // 弹出窗口
    popup->exec();
    popup->deleteLater();
}

/**
 * @brief TaskTwoWindow::showLR1Tab
 * 展示LR1分析表
 */
void TaskTwoWindow::showLR1Tab()
{
    if (lr.LR0DfaStates.empty()) {
        QMessageBox::information(this, tr("注意"), tr("你还没有进行分析,无法生成分析表!"));
        return;
    }
    // 如果不是正确的文法，那么弹出框，告知不能进行分析
    if (!lr.isRightGram) {
        QMessageBox::information(this, tr("错误"), tr("该文法错误,不可进行分析!"));
        return;
    }
    // 1. 创建弹窗表格
    auto *popup = new GramTable("LR(1) 分析表", this);

    // 2. 提取所有符号（终结符 + 非终结符 + '$'）作为表头（不包含状态列）
    QSet<QString> allSymbols;
    for (const auto &row : lr.lr1Table) {
        for (const auto &cell : row.second) {
            allSymbols.insert(QString::fromStdString(cell.first));
        }
    }

    // 3. 设置表头
    QStringList headers;
    headers << "状态";  // 第一列是状态编号
    for (const auto &sym : allSymbols) {
        headers << sym;
    }

    // 4. 设置表格行列
    int rowCount = lr.lr1Table.size();
    int colCount = headers.size();
    popup->setTable(rowCount, colCount, headers);

    QTableWidget *widget = popup->getTableWidget();

    // 5. 填充表格内容
    int row = 0;
    for (const auto &rowPair : lr.lr1Table) {
        int stateId = rowPair.first;
        const auto &actions = rowPair.second;

        // 设置状态编号
        widget->setItem(row, 0, new QTableWidgetItem(QString::number(stateId)));

        for (const auto &actPair : actions) {
            QString symbol = QString::fromStdString(actPair.first);
            const Action &action = actPair.second;

            QString text;
            switch (action.type) {
                case SHIFT:
                    text = "s" + QString::number(action.target);
                    break;
                case REDUCE: {
                    // 取得产生式
                    text = "r" + QString::number(action.target);
                    break;
                }
                case GOTO:
                    text = "g" + QString::number(action.target);
                    break;
                case ACCEPT:
                    text = "接受";
                    break;
                case ERROR:
                default:
                    cerr<<"有bug"<<endl;
                    break;
            }

            int col = headers.indexOf(symbol);
            if (col != -1 && !text.isEmpty()) {
                widget->setItem(row, col, new QTableWidgetItem(text));
            }
        }

        ++row;
    }

    // 6. 自动适应列宽
    widget->resizeColumnsToContents();
    popup->exec();
    popup->deleteLater();
}

/**
 * @brief TaskTwoWindow::inputSrc
 * 打开源代码
*/
void TaskTwoWindow::inputSrc()
{
    QString filePath = QFileDialog::getOpenFileName(this, "打开编码文件", QDir::currentPath(), "Text Files (*.txt *.lex *.minic)");
    if (filePath.isEmpty())
       return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QMessageBox::warning(this, "错误", "无法打开文件读取 " + file.errorString());
       return;
    }

    sourceDisplay->setRowCount(0); // 清空表格
    tokens.clear();
    QTextStream in(&file);
    int row = 0;

    while (!in.atEnd()) {
       QString line = in.readLine().trimmed();
       if (line.isEmpty()) continue;

       // 格式为：type value
       QStringList parts = line.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);
       for (int i = 0; i + 1 < parts.size(); i += 2) {
           QString codeStr = parts[i];
           QString valueStr = parts[i + 1];

           // 插入表格
           sourceDisplay->insertRow(row);
           sourceDisplay->setItem(row, 0, new QTableWidgetItem(codeStr));
           sourceDisplay->setItem(row, 1, new QTableWidgetItem(valueStr));
           row++;

           // 插入 token 向量
           tokens.push_back(Token{codeStr.toInt(), valueStr.toStdString()});
        }
    }
    file.close();

}


/**
 * @brief TaskTwoWindow::buildInputQueue 输入队列拼接（字符串形式展示）
 * @param tokens
 * @return
 */
QString TaskTwoWindow::buildInputQueue(const std::vector<Token> &tokens)
{
    QStringList tokenStrs;
    for (const auto &tk : tokens) {
        tokenStrs << QString::fromStdString(tk.value);  // value 是识别出的具体单词
    }
    return tokenStrs.join(" ");
}

/**
 * @brief TaskTwoWindow::getStackContent 用于拼接分析栈展示
 * @param states
 * @param symbols
 * @return
 */
QString TaskTwoWindow::getStackContent(const std::stack<int> &states, const std::stack<QString> &symbols) {
    std::stack<int> stateCopy = states;
    std::stack<QString> symCopy = symbols;
    QStringList out;

    std::vector<std::pair<QString, int>> stackItems;
    while (!stateCopy.empty()) {
        int s = stateCopy.top(); stateCopy.pop();
        QString sym = symCopy.top(); symCopy.pop();
        stackItems.push_back({sym, s});
    }
    std::reverse(stackItems.begin(), stackItems.end());

    for (const auto &item : stackItems)
        out << item.first << QString::number(item.second);

    return out.join(" ");
}

/**
 * @brief TaskTwoWindow::getInputTail 用于拼接剩余待分析文法
 * @param tokens
 * @param startIdx
 * @return
 */
QString TaskTwoWindow::getInputTail(const std::vector<Token> &tokens, int startIdx) {
    QStringList inputTail;
    for (int i = startIdx; i < tokens.size(); ++i)
        inputTail << QString::fromStdString(tokens[i].value);
    inputTail << "$";
    return inputTail.join(" ");
}


/**
 * @brief TaskTwoWindow::showProc
 * 展示分析过程
 */
void TaskTwoWindow::showProc(){
    if(CodeMap.size() == 0) {
        QMessageBox::warning(this,"警告","请先去词法分析生成编码映射表后使用！");
        return;
    }

    if(GraActionMap.size() == 0) {
        QMessageBox::warning(this,"注意","如果要生成语法树，请先导入语义动作表后再重新执行分析过程！");
    }

    std::vector<ParseStep> steps;
    std::stack<int> stateStack;    // 状态栈
    std::stack<QString> symbolStack; // 符号栈（用于展示）
    treeStack = std::stack<SyntaxTreeNode*>(); //清空旧语法栈

    // 创建 GramTable 弹窗
    auto *popup = new GramTable("语法分析过程:", this);

    // 初始化
    stateStack.push(0); // 初始状态为0
    symbolStack.push("$"); // 输入符号队列的末尾符号

    int index = 0;  // 输入指针
    QString inputQueue = buildInputQueue(tokens); // 构建输入队列

    bool isAccept = false; //用于规约最后一条完整式子
    while (true) {
        int state = stateStack.top();  // 当前状态

        // 确保 index 在有效范围内
        std::string currentSym = "$";  // 默认是 $
        if (index < tokens.size()) {

            int cd = tokens[index].code;
            currentSym = CodeMap[cd];
            if (lr.grammerTerminalList.count(tokens[index].value)) {
                currentSym = tokens[index].value;
            }
        }

        const auto &actionMap = lr.lr1Table[state];  // 获取当前状态的动作表
        auto it = actionMap.find(currentSym);  // 查找当前符号对应的动作

        ParseStep step;
        step.stackContent = getStackContent(stateStack, symbolStack);  // 展示栈
        step.inputContent = getInputTail(tokens, index);  // 展示剩余输入

        if (it == actionMap.end() || it->second.type == ERROR) {
            step.operation = "错误";  // 错误处理
            steps.push_back(step);
            break;
        }

        const Action &act = it->second;
        if (act.type == SHIFT) {
            step.operation = QString("移进%1").arg(act.target);
            symbolStack.push(QString::fromStdString(tokens[index].value));
            stateStack.push(act.target);

            ++index;  // 移进后更新输入指针
            /*
            // 创建终结符分析树节点并压入语法树栈
            SyntaxTreeNode* node = new SyntaxTreeNode;
            int cd = tokens[index].code;
            string type = CodeMap[cd];
            node->type = QString::fromStdString(type);  // 类型如 identifier、number
            node->value = QString::fromStdString(tokens[index].value); // 具体值如 "x", "3"
            node->terminal = true;
            node->childNum = 0;
            treeStack.push(node);
            */

            //语法树部分
            if(GraActionMap.isEmpty()) continue; //没有语法树就跳过

            SyntaxTreeNode* tmpTree = new SyntaxTreeNode();
            tmpTree->Name = QString::fromStdString(tokens[index - 1].value); //终结符节点
            treeStack.push(tmpTree); //入栈
            //结束

        } else if (act.type == REDUCE) {
            const auto &prod = lr.idToProduction[act.target];  // 获取规约的产生式
            bool isEmptyRule = (prod.right.size() == 1 && prod.right[0] == "#"); //如果是空规约式

            int popCount = isEmptyRule ? 0 : prod.right.size();

            // 规约操作：弹出栈顶的符号
            while (popCount--) {
                if (!symbolStack.empty()) symbolStack.pop();
                if (!stateStack.empty()) stateStack.pop();
            }

            /*
            // 构建语法树父节点
            SyntaxTreeNode* parent = new SyntaxTreeNode();
            parent->type = QString::fromStdString(prod.left); //非终结符
            parent->value = "";
            parent->terminal = false;

            QVector<SyntaxTreeNode*> children;
            for (int i = 0; i < prod.right.size(); ++i) {
               if (!treeStack.empty()) {
                   SyntaxTreeNode* child = treeStack.top();
                   treeStack.pop();
                   children.prepend(child); // 保证顺序与产生式右部一致
               }
            }
            parent->child = children;
            parent->childNum = children.size();

            treeStack.push(parent); // 推入语法树栈
            */

            symbolStack.push(QString::fromStdString(prod.left));  // 将规约的左部推入栈
            int newState = 0;
            // 根据栈顶状态找到新的状态
            if (!stateStack.empty()) {
                const auto &stateActionMap = lr.lr1Table[stateStack.top()];
                auto stateIt = stateActionMap.find(prod.left);
                if (stateIt != stateActionMap.end()) {
                    newState = stateIt->second.target;
                }
            }

            stateStack.push(newState);  // 推入新的状态

            step.operation = QString("用第%1条规约：%2 -> %3")
                .arg(act.target)
                .arg(QString::fromStdString(prod.left))
                .arg(QString::fromStdString(join(prod.right, ' ')));


            //语法树部分
            if(GraActionMap.empty()) continue;
            //如果规约的是空#
            if(isEmptyRule) {
                SyntaxTreeNode* tmpTree = new SyntaxTreeNode();
                tmpTree->Name = "#";
                treeStack.push(tmpTree);
            }

            //根据规约规则先找到语义动作
            QString GraActionNum = GraActionMap[prod];
            QVector<SyntaxTreeNode*> tmpTreeVec; //反转栈
            for(int i = 0; i < GraActionNum.size(); i++)
            {
                tmpTreeVec.push_back(treeStack.top());
                treeStack.pop();
            }
            reverse(tmpTreeVec.begin(),tmpTreeVec.end());
            //先找到根节点，第一个1就是
            int rootIdx = GraActionNum.indexOf('1');
            if (rootIdx == -1) {
                QMessageBox::warning(this, "语义动作错误", "当前规约没有指定根节点 '1'！");
                continue;
            }
            SyntaxTreeNode* root = tmpTreeVec[rootIdx];
            //链接兄弟链条
            SyntaxTreeNode* broChains = root;
            while(broChains->bro != nullptr)
                broChains = broChains->bro;

            for(int i = 0; i < GraActionNum.size(); i++) {
                switch (GraActionNum[i].toLatin1()) {
                    case IGNORE:
                    case ROOT:
                        break;
                    case CHILD:
                        root->son.append(tmpTreeVec[i]);
                        break;
                    case BRO:
                        broChains->bro = tmpTreeVec[i];
                        broChains = broChains->bro;
                        break;
                }
            }
            treeStack.push(root);

        } else if (act.type == ACCEPT) {
            isAccept = true;
            step.operation = "接受";
            steps.push_back(step);
            break;
        }

        steps.push_back(step);

    }

    // 展示到表格中
    popup->setTable(steps.size(), 3, {"分析栈", "输入串", "操作"});
    QTableWidget *table = popup->getTableWidget();

    for (int i = 0; i < steps.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(steps[i].stackContent));
        table->setItem(i, 1, new QTableWidgetItem(steps[i].inputContent));
        table->setItem(i, 2, new QTableWidgetItem(steps[i].operation));
    }

    table->verticalHeader()->setVisible(true); // 开启行号显示
    popup->exec(); // 弹出展示
    popup->setAttribute(Qt::WA_DeleteOnClose);
}

/**
 * @brief TaskTwoWindow::getAction 用户导入语义动作表
 */
void TaskTwoWindow::getAction()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择语义动作表文件", "", "Text Files (*.txt);;All Files (*)");
    if (fileName.isEmpty()) return;

    //处理输入语义动作
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QMessageBox::warning(this, "文件错误", "无法打开所选文件！");
       return;
    }

    QMessageBox::information(this,"提示","导入成功!");
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
       QString line = in.readLine().trimmed();
       if (!line.isEmpty()) {
           lines.append(line);
       }
    }
    file.close();

    if (lines.size() % 2 != 0) {
       QMessageBox::warning(this, "格式错误", "语义动作表必须是偶数行，一行文法一行动作！");
       return;
    }


    //将语义动作表的value与文法规则进行映射
    //GraAction<ItemLR0, QString> GraActionMap
    for (int i = 0; i < lines.size(); i += 2) {
        QString grammarLine = lines[i];         // A -> B | C
        QString actionLine = lines[i + 1];      // 1 2 | 3

        QStringList parts = grammarLine.split("->", QString::SkipEmptyParts);

        if (parts.size() != 2) continue; //文法有问题！

        QString left = parts[0].trimmed();                          // 左部 A
        QStringList rightParts = parts[1].split('|');               // 拆右部 B、C
        QStringList actionParts = actionLine.split('|');            // 拆动作 1、2、3
        for (QString& part : actionParts) {
            part.remove(QRegExp("\\s")); // 移除所有空白字符（包括空格、换行、制表符等）
        }

        if (rightParts.size() != actionParts.size()) {
            QMessageBox::warning(this, "语义动作数错误",
                                 QString("产生式 [%1] 的右部数量与语义动作数不一致！").arg(grammarLine));
            continue;
        }

        for (int j = 0; j < rightParts.size(); ++j) {
            ItemLR0 item;
            item.left = left.toStdString();
            item.dotPos = 0;

            QString right = rightParts[j].trimmed();
            QStringList symbols = right.split(" ", QString::SkipEmptyParts);
            for (const QString& sym : symbols) {
                item.right.push_back(sym.toStdString());
            }

            QString action = actionParts[j].trimmed();
            GraActionMap[item] = action;
        }
    }
}

/**
 * @brief TaskTwoWindow::getNodeText 获取节点的值
 * @param node
 * @return
 */
QString TaskTwoWindow::getNodeText(SyntaxTreeNode* node) {
    return node->Name;
}


/**
 * @brief TaskTwoWindow::addSubtree  添加以某个 node 为根的整个兄弟链（本节点 + bro + bro->bro + ...）
 * @param parentItem
 * @param node
 */
void TaskTwoWindow::addSubtree(QTreeWidgetItem* parentItem, SyntaxTreeNode* node) {
    while (node != nullptr) {
        QTreeWidgetItem* item = new QTreeWidgetItem(parentItem);
        item->setText(0, getNodeText(node));

        // 递归添加所有子节点
        for (SyntaxTreeNode* child : node->son) {
            addSubtree(item, child);
        }

        node = node->bro; // 移动到下一个兄弟节点
    }
}


/**
 * @brief TaskTwoWindow::showTree 绘制语法树
 */
void TaskTwoWindow::showTree() {
    if (treeStack.empty()) {
            QMessageBox::information(this, "注意", "没有语法树，请先完成语法分析！");
            return;
        }

        treeWidget->clear();
        treeWidget->setHeaderLabel("语法树");

        SyntaxTreeNode* root = new SyntaxTreeNode();
        root->Name = "root";

        SyntaxTreeNode* sonTop = treeStack.top();
        root->son.push_back(sonTop);

        QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWidget);
        rootItem->setText(0, getNodeText(root));

        // 用新的方式添加整棵树（含兄弟）
        for(const auto & son : root->son) {
            addSubtree(rootItem, son);
        }


        treeWidget->addTopLevelItem(rootItem);
        treeWidget->expandAll();
}

/**
 * @brief TaskTwoWindow::addUsageTip 左上角用户使用说明书
 */
void TaskTwoWindow::addUsageTip()
{
    QPushButton *helpBtn = new QPushButton("?", this);
    helpBtn->setFixedSize(20, 20);
    helpBtn->move(5, 5); // 左上角

    connect(helpBtn, &QPushButton::clicked, this, [=]() {
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle("使用说明");

        QTextEdit *textEdit = new QTextEdit(dialog);
        textEdit->setText(tr("【TaskTwo 使用说明】\n\n"
                             "1. 点击“选择文法文件”读取文法\n"
                             "2. 点击“分析”处理文法，自动生成扩展文法、first/follow集\n"
                             "3. 可分别查看 LR0/SLR1/LR1 DFA 图及分析表\n"
                             "4. 点击“选择源程序文件”并“展示分析过程”\n"
                             "5. 可展示分析树\n\n"
                             "注意：\n"
                             "1. 文法符号之间需使用空格分隔\n"
                             "2. 文法不能存在语义冲突"
                             "3. 每次导入新编码文件前，请先再次点击开始分析,清除分析过程。"));
        textEdit->setReadOnly(true);

        QVBoxLayout *layout = new QVBoxLayout(dialog);
        layout->addWidget(textEdit);
        dialog->setLayout(layout);
        dialog->resize(500, 300);
        dialog->exec();
    });
}
