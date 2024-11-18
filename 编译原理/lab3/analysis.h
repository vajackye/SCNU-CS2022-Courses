#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include<unordered_set>
#include<utility>
#include<vector>
#include<QString>
#include<QFile>
#include<QTextStream>

using namespace std;
// 定义 TokenType 枚举类型
enum TokenType {
    // 关键字（KW）
    IF, THEN, ELSE, ENDIF,
    REPEAT, UNTIL, READ, WRITE,
    TRUE, FALSE, // 布尔值
    FOR, ENDFOR, WHILE, ENDWHILE,

    //标识符常量
    CONST, //常量
    ID, //标识符

    // 运算符（OP）
    ASSIGN,      // :=
    LT,   // <
    GT, // >
    LE,   // <=
    GE, // >=
    EQ,        // =
    NEQ,    // <>
    PLUS,         // +
    MINUS,        // -
    MUL,     // *
    DIV,       // /
    MOD,      // %
    POW,        // ^
    INCREMENT,    // ++
    DECREMENT,    // --

    // 正则符号（REG）
    REG_ASSIGN,   // ::=
    REG_OR,       // |
    REG_AND,      // &
    REG_HASH,     // #
    REG_OPT, // ?

    //通用左右括号
    LP,   // (
    RP,   // )

    // 分隔符（SEP）
    SEP,    // ;

    // 特殊符号
    ERROR,        // 错误标记
    ENDFILE       // 文件结束
};

//枚举类映射
extern unordered_map<string, TokenType> mp;

//节点类
struct Node {
    string ch;
    int SIZE; // MAX is 4
    Node* child[4]; //最多4个孩子，这里开8个，其实是预防用户输入不合法。我树建了..
    Node* sibling; //兄弟节点
    //默认构造函数
    Node() : SIZE(0),ch(""), sibling(nullptr), child { nullptr, nullptr, nullptr, nullptr } {}
    Node(string fir) : SIZE(0), ch(fir), sibling(nullptr), child{ nullptr, nullptr, nullptr, nullptr } {}
    Node(string fir,string sec) : SIZE(0), ch(fir),sibling(nullptr), child{ nullptr, nullptr, nullptr, nullptr } {}
};

//操作类
class Analysis {
    public:
        bool explain = false; //注释词法分析
        bool isReg = false; //regex的行为特判
        string InputCode; //输入的代码，保存结果
        string word; //词法分析结果存储
        int lineNum; //代码总行数
        int tkNow; //目前遍历到的Tokens下的idx的下一位。
        pair<string, TokenType>token; //当前token
        vector<pair<string, TokenType>>Tokens; //存入所有的记录的单词顺序，进行语法分析getToken使用
        vector<pair<string, int>>ErrorLine; //存储行号，以便获取报错时行号
        Node* root = nullptr; //树根

        //QT特色操作
        QString fileName;
        vector<tuple<QString, QString, int>> errorList;  // 错误信息列表


        void init(); //初始化,同时先建一棵树
        void analysis(const QString &fileContent); //分析函数
        string wordKind(string ss); //词法分析
        int zhushi(string st, int index, bool &flag); //词法注释处理
        int digit(string st, int index, bool &flag); //词法数字处理
        int keyW(string st, int index, bool &flag); //词法关键字处理
        int opera(string st, int index, bool &flag); //词法运算符处理
        int regex(string st, int index, bool &flag); //词法正则处理
        void printWord(); //打印词法


        Node* LangAnaly(); // 语法分析入口函数
        TokenType getToken(); // 获取下一个token
        Node* stmt_sequence();
        Node* statement();
        Node* if_stmt();
        Node* repeat_stmt();
        Node* assign_stmt();
        Node* read_stmt();
        Node* write_stmt();
        Node* exp();
        Node* simple_exp();
        Node* term();
        Node* pow();
        Node* factor();
        Node* regex_stmt();
        Node* andreg();
        Node* topreg();
        Node* reg_factor();
        Node* while_stmt();
        Node* for_stmt();
        void match(const TokenType& expectedToken); // 用于判别当前符号是否为预想的类型，否则报错
        void Error(int errorKind, const int& idx, const TokenType& expectedToken, const TokenType&token); //出错函数

        //清除树
        void clear(Node* root); //开始删除整条树

        //打印树
        void printSyntaxTree(Node* root, int depth = 0);
};


