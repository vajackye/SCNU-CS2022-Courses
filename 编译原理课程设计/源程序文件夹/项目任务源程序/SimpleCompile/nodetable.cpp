/***************************************************************
 * 版权所有 (C) 20222121007 计算机科学与技术师范 黄泽基
 * 保留所有权利
 *
 * 模块名称：nodetable.cpp
 * 模块功能：本模块用于可视化NFA、DFA、DFA最小化图表
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
#include "nodetable.h"

NodeTable::NodeTable(
        const std::unordered_map<std::string, NFA> finalNFA,  // 存储所有规则的 NFA
        const std::unordered_map<std::string, DFA> finalDFA,  // 存储所有规则的 DFA
        const std::unordered_map<std::string, std::vector<DFANode>> DFANode, //存储所有规则的DFA的NFA节点
        const std::unordered_map<std::string, MinDFA> finalMiniDFA,  // 每条规则最小化后的 DFA节点
        const std::unordered_map<std::string, std::unordered_set<std::string>> symbols, //存储每个规则的所有可遍历字符。
        const int type,
        QWidget *parent
):QDialog(parent),NfaData(finalNFA),DfaData(finalDFA),DFANodeMap(DFANode),MiniDfa(finalMiniDFA),symbolData(symbols),nodeType(type)
{
    setWindowTitle("自动机状态转移表");
    resize(800,600);

    regexSelector = new QComboBox(this);
    for(const auto &pair : symbolData) {
        regexSelector->addItem(QString::fromStdString(pair.first)); //将对应正则的名字填充上去
    }

    showButton = new QPushButton("展示", this);
    connect(showButton, &QPushButton::clicked, this, &NodeTable::onShowClicked);

    table = new QTableWidget(this);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(regexSelector);
    topLayout->addWidget(showButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(table);
    setLayout(mainLayout);
}


void NodeTable::onShowClicked() {
    QString ruleName = regexSelector->currentText();
    fillTable(ruleName);
}

void NodeTable::fillTable(const QString &regexName) {
    std::string key = regexName.toStdString();
    std::unordered_set<std::string> tmpSym(symbolData[key].begin(),symbolData[key].end());

    //将set值改为vector，排序增加逻辑
    std::vector<std::string> symbolVec;
    for(auto ch : tmpSym) {
        symbolVec.push_back(ch);
    }
    //如果是NFA，有空边
    if(nodeType == 1) symbolVec.push_back("#");

    std::sort(symbolVec.begin(),symbolVec.end());

    int rowCount = 0;
    int colCount = static_cast<int>(symbolVec.size()) + 2;//第一列标识是否为终点、起点；第二列为编号;其余列为转移符号

    table->clear();
    table->setColumnCount(colCount);

    QStringList headers;//设置表头
    headers << "标志" << "状态编号";
    for(const auto & sym: symbolVec) {
        headers << QString::fromStdString(sym);
    }

    table->setHorizontalHeaderLabels(headers);


    //判断是NFA、DFA还是MinDFA
    if(nodeType == 1) {
        if(NfaData.count(key)) {
            const auto &nfa = NfaData.at(key);
            const auto &states = nfa.states;

            table->setRowCount(static_cast<int>(states.size()));

            for(const auto &state : states) {
                int row = state.id;
                QString flag;
                if(state.id == nfa.startState) flag += "-";
                if(nfa.acceptStates.count(state.id)) flag += "+";

                table->setItem(row, 0, new QTableWidgetItem(flag));
                table->setItem(row, 1, new QTableWidgetItem(QString::number(state.id)));

                for(int i = 0; i < symbolVec.size(); i++) {
                    const std::string &sym = symbolVec[i];
                    if(state.transitions.count(sym)) {
                        QStringList targets;
                        for(int t : state.transitions.at(sym)) {
                            targets << QString::number(t);
                        }
                        table->setItem(row, static_cast<int>(i) + 2, new QTableWidgetItem(targets.join(",")));
                    }
                }
            }
        }
    }
    else if(nodeType == 2) {
        const auto& dfa = DfaData.at(key);
        const auto& nodeList = DFANodeMap.at(key); // 包含 DFANode（有 closure 集合）

        table->setRowCount(nodeList.size());

        for(const auto& node : nodeList) {
            int row = node.id;
            // 构造状态集合字符串，例如 "{1,2,3}"
            QString stateStr = "{";
            bool first = true;
            for (int n : node.closure) {
                if (!first) stateStr += ",";
                stateStr += QString::number(n);
                first = false;
            }
            stateStr += "}";

            // 第一列：是否为终态（+）或起点（-）
            QString mark;
            if (row == dfa.start) mark += "-";
            bool isEnd = false;
            for (int n : node.closure) {
                if (dfa.end.count(n)) {
                    isEnd = true;
                    break;
                }
            }
            if (isEnd) mark += "+";
            table->setItem(row, 0, new QTableWidgetItem(mark));

            // 第二列：状态集合字符串
            table->setItem(row, 1, new QTableWidgetItem(stateStr));

            // 后续列：每个符号的转移目标（也显示为集合）
            for (int col = 0; col < symbolVec.size(); ++col) {
                QString sym = QString::fromStdString(symbolVec[col]);

                QString destStr = "";
                for (const auto& edge : node.edges) {
                    if (QString::fromStdString(edge.c) == sym) {
                        const auto& destNode = nodeList[edge.to];
                        destStr = "{";
                        bool first2 = true;
                        for (int n : destNode.closure) {
                            if (!first2) destStr += ",";
                            destStr += QString::number(n);
                            first2 = false;
                        }
                        destStr += "}";
                        break;
                    }
                }
                table->setItem(row, col + 2, new QTableWidgetItem(destStr));
            }
        }
    }
    else if(nodeType == 3) {
        const MinDFA& minDfa = MiniDfa.at(key);
        const auto& nodes = minDfa.states;
        int startState = minDfa.start;

        table->setRowCount(static_cast<int>(nodes.size()));

        for (const auto& node : nodes) {
            int row = node.id;

            QString flag;
            if (row == startState) flag += "-";  // 正确地标记初态
            if (node.isEnd) flag += "+";

            table->setItem(row, 0, new QTableWidgetItem(flag));
            table->setItem(row, 1, new QTableWidgetItem(QString::number(node.id)));

            for (const auto& edge : node.edges) {
                auto it = std::find(symbolVec.begin(), symbolVec.end(), edge.c);
                if (it != symbolVec.end()) {
                    int col = static_cast<int>(std::distance(symbolVec.begin(), it)) + 2;
                    table->setItem(row, col, new QTableWidgetItem(QString::number(edge.to)));
                }
            }
        }
    }

    table->resizeColumnsToContents();
    table->horizontalHeader()->setStretchLastSection(true);
}
