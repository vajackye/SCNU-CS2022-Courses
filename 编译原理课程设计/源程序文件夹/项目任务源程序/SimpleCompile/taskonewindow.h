#ifndef TASKONEWINDOW_H
#define TASKONEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QStringList>
#include <QMessageBox>
#include "mainwindow.h"
#include "predore.h"
#include "retonfa.h"
#include "nfatodfa.h"
#include "minidfa.h"
#include "nodetable.h"
#include "lexsource.h"
#include "common.h"

class TaskOneWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TaskOneWindow(QWidget *parent = nullptr);
    preDoRe p; //预处理对象
    ReToNfa nf; //转Nfa对象
    NfaToDfa df; //转Dfa对象
    MiniDfa mindf; //最小化Dfa对象
    lexSource lex; //输出词法分析源程序

private slots:
    void backToMain(); //返回主页面
    void inputFile();             // 选择并读取正则文件
    void saveFile();              // 保存正则文件
    void analysisRegex();         // 分析正则，生成NFA、DFA、minDFA
    void selectNFA();             // 根据下拉框选择展示对应NFA
    void selectDFA();             // 根据下拉框选择展示对应DFA
    void selectMinDFA();          // 根据下拉框选择展示对应minDFA
    void generateSourceCode();    // 根据minDFA生成词法分析器C++源代码
    void showWordCode();          // 展示词法分析器的识别结果编码

private:
    QTextEdit *regexDisplay;    //正则表达式文本框
    QTextEdit *sourceDisplay;   //源程序输出文本框
    QTableWidget *codeDisplay;     //编码输出文本框
    bool donePre = false;       //已经预处理完毕
    bool doneNfa = false;       //已经转好Nfa了
    bool doneDfa = false;       //已经转好Dfa了
    bool doneMinDfa = false;    //已经转好最小Dfa了

signals:

};
#endif // TASKONEWINDOW_H
