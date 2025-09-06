#ifndef TASKTWOWINDOW_H
#define TASKTWOWINDOW_H

#include <QWidget>
#include <QStringList>
#include <QString>
#include <stack>
#include <QTreeWidget>
#include "mainwindow.h"
#include "grammerdo.h"
#include "gramtable.h"
#include "common.h"

class TaskTwoWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TaskTwoWindow(QWidget *parent = nullptr);
    std::string join(const std::vector<std::string> &vec, char delimiter);


private:
    LR1 lr;                             //LR表
    std::vector<Token> tokens;          //分析表存储内容
    QTextEdit *grammarDisplay;          // 文法读取
    QTextEdit *externGrDis;             // 扩充文法展示
    QTextEdit *slr1Result;              // SLR1判别
    QTableWidget *sourceDisplay;        // 编码展示
    QTreeWidget *treeWidget;            // 语法树层级展示
    std::stack<SyntaxTreeNode*> treeStack; // 语法树栈，用于构建语法树
    QMap<ItemLR0, QString> GraActionMap;//语法树分析时用的语义动作映射表
    QString buildInputQueue(const std::vector<Token> &tokens);
    QString getStackContent(const std::stack<int> &states, const std::stack<QString> &symbols);
    QString getInputTail(const std::vector<Token> &tokens, int startIdx);

private slots:
    void backToMain();                  // 返回主页面
    void inputFile();                   // 选择并读取文法文件
    void analysisGram();                // 预处理文法
    void showExternGram();              // 展示扩充文法集
    void showFirst();                   // 展示first集合
    void showFollow();                  // 展示follow集合
    void showLR0Dfa();                  // 展示LR0 的 DFa
    void judgeSLR1();                   // 判断文法是否为 SLR1
    void showLR1Dfa();                  // 展示LR1 的 DFa
    void showLR1Tab();                  // 展示LR1 的 分析表
    void inputSrc();                    // 读入源程序文件
    void showProc();                    // 展示源程序 的 分析过程
    void getAction();                   // 用户导入语义动作
    void showTree();                    // 展示LR1 下的 具体语法树
    void addUsageTip();                 // 使用说明书
    QString getNodeText(SyntaxTreeNode* node); //语法树生成辅助函数
    void addSubtree(QTreeWidgetItem* parentItem, SyntaxTreeNode* node); //语法树生成辅助函数

signals:

};

#endif // TASKTWOWINDOW_H
