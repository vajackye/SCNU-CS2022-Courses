#pragma once
#include <QDialog>
#include <QComboBox>
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <QHeaderView>
#include "retonfa.h"
#include "nfatodfa.h"
#include "minidfa.h"


class NodeTable : public QDialog {
    Q_OBJECT
public:
    NodeTable(int Type):nodeType(Type){}
    NodeTable(
        const std::unordered_map<std::string, NFA> finalNFA,  // 存储所有规则的 NFA
        const std::unordered_map<std::string, DFA> finalDFA,  // 存储所有规则的 DFA
        const std::unordered_map<std::string, std::vector<DFANode>> DFANode, //存储所有规则的DFA的NFA节点
        const std::unordered_map<std::string, MinDFA> finalMiniDFA,  // 每条规则最小化后的 DFA节点
        const std::unordered_map<std::string, std::unordered_set<std::string>> symbols, //存储每个规则的所有可遍历字符。
        const int Type,
        QWidget *parent = nullptr
    );

private slots:
    void onShowClicked(); // 展示表格

private:
    QComboBox *regexSelector; //正则表达式选择
    QPushButton *showButton;  //点击展示填充
    QTableWidget *table;      //表格

    std::unordered_map<std::string, NFA> NfaData;  // 存储所有规则的 NFA
    std::unordered_map<std::string, DFA> DfaData;  // 存储所有规则的 DFA
    std::unordered_map<std::string, std::vector<DFANode>> DFANodeMap; //存储所有规则的DFA的NFA节点
    std::unordered_map<std::string, MinDFA> MiniDfa;  // 每条规则最小化后的 DFA节点
    std::unordered_map<std::string, std::unordered_set<std::string>> symbolData; //存储每个规则的所有可遍历字符。
    int nodeType; //标识当前是要求转NFA、DFA还是MiniDFA (1:NFA; 2:DFA; 3:MinDFA)

    void fillTable(const QString &regexName); //填充表格

};

