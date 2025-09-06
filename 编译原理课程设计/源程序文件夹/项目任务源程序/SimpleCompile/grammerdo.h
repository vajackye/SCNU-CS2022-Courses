/*****************************************************************************
*  Copyright (C), 2025, 黄泽基 20222121007
*
*  @file    preGrammer.h
*  @brief   语法分析类，囊括：BNF文法改造；first，follow生成；LR0生成；SLR1生成；LR1生成；语法树生成。
*
*  @author  黄泽基
*  @date    2025-4-05
*  @version V1.0.0
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改内容
*  @note V1.0.0   黄泽基     创建文件
*****************************************************************************
*/
#pragma once
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<stack>
#include<sstream>
#include"common.h"
#include<QString>
#include<QPlainTextEdit>
#include<QStringList>

using namespace std;

//分析表结构
enum ActionType {SHIFT, REDUCE, GOTO, ACCEPT, ERROR};

struct Action {
    ActionType type;
    int target; // 对于 SHIFT 或 GOTO，为状态编号；对于 REDUCE，为产生式编号
    Action(): type(ERROR), target(-1){}
    Action(ActionType t, int trg): type(t),target(trg){}
};

//LR0中每一个规则存储结构
struct ItemLR0 {
    string left; //规则左部
    vector<string> right; //规则右部
    int dotPos = 0; //点的位置

    //比较两个Item是否相同
    bool operator==(const ItemLR0& other) const {
        return left == other.left && right == other.right && dotPos == other.dotPos;
    }

    bool operator<(const ItemLR0& other) const {
      if (left != other.left) return left < other.left;
      if (right != other.right) return right < other.right;
      return dotPos < other.dotPos;
    }

    // 输出函数：将 ItemLR1 转换为字符串
   string toString() const {
       std::string ss;
       ss += left + " → ";

       for (int i = 0; i < right.size(); ++i) {
           ss += right[i];
       }

       return ss;
   }

    ItemLR0() {}
    ItemLR0(string l, vector<string> r, int d) :left(l), right(r), dotPos(d) {}
};

struct ItemLR1 {
    string left; //规则左部
    vector<string> right; //规则右部
    int dotPos = 0; //点的位置
    string lookahead; //LR1的超前查看一个字符，可能存在多种情况。(|)

    //比较两个ItemLR1是否相同
    bool operator==(const ItemLR1& other) const {
        return left == other.left && right == other.right && dotPos == other.dotPos && lookahead == other.lookahead;
    }

    ItemLR1() {}
    ItemLR1(string l, vector<string> r, int d) :ItemLR1(l, r, d, {}) {}
    ItemLR1(string l, vector<string> r, int d, string look) :left(l), right(r), dotPos(d), lookahead(move(look)) {} //移动构造，避免多余拷贝
};

//个性化hash，保证能够处理ItemLR0操作
namespace std {
    // 定义 Item 类型的哈希函数
    template <>
    struct hash<ItemLR0> {
        size_t operator()(const ItemLR0& item) const {
            size_t h1 = hash<string>()(item.left); // 对 left 字段哈希
            size_t h2 = hash<size_t>()(item.dotPos); // 对 dotPos 字段哈希
            size_t h3 = 0;
            for (const auto& s : item.right) {
                h3 ^= hash<string>()(s) + 0x9e3779b9 + (h3 << 6) + (h3 >> 2); // 合并哈希作为right字段哈希值
            }
            return h1 ^ h2 ^ h3; // 返回组合哈希值
        }
    };

    // 定义 unordered_set<Item> 的哈希函数
    template <>
    struct hash<unordered_set<ItemLR0>> {
        size_t operator()(const unordered_set<ItemLR0>& set) const {
            size_t hashValue = 0;
            for (const auto& item : set) {
                hashValue ^= hash<ItemLR0>()(item); // 对每个元素的哈希值进行异或操作
            }
            return hashValue; // 返回集合的组合哈希值
        }
    };

    // 定义 unordered_set<Item> 的比较函数
    template <>
    struct equal_to<unordered_set<ItemLR0>> {
        bool operator()(const unordered_set<ItemLR0>& lhs, const unordered_set<ItemLR0>& rhs) const {
            return lhs == rhs; // 使用集合自带的相等运算符进行比较
        }
    };
}

//个性化hash，保证能够处理ItemLR1操作
namespace std {
    // 为 ItemLR1 类型定义哈希函数
    template <>
    struct hash<ItemLR1> {
        size_t operator()(const ItemLR1& item) const {
            size_t h1 = hash<string>()(item.left);  // 对 left 字段哈希
            size_t h2 = hash<size_t>()(item.dotPos);  // 对 dotPos 字段哈希
            size_t h3 = 0;

            // 对 right 字段的每个元素进行哈希
            for (const auto& s : item.right) {
                h3 ^= hash<string>()(s) + 0x9e3779b9 + (h3 << 6) + (h3 >> 2);  // 合并哈希值
            }

            // 对 lookahead 进行哈希
            size_t h4 = hash<string>()(item.lookahead);  // 对 left 字段哈希

            return h1 ^ h2 ^ h3 ^ h4;  // 合并所有字段的哈希值
        }
    };

    // 为 unordered_set<ItemLR1> 类型定义哈希函数
    template <>
    struct hash<unordered_set<ItemLR1>> {
        size_t operator()(const unordered_set<ItemLR1>& set) const {
            size_t hashValue = 0;
            for (const auto& item : set) {
                hashValue ^= hash<ItemLR1>()(item);  // 对每个 ItemLR1 的哈希值进行异或操作
            }
            return hashValue;  // 返回集合的组合哈希值
        }
    };

    // 为 unordered_set<ItemLR1> 类型定义相等比较函数
    template <>
    struct equal_to<unordered_set<ItemLR1>> {
        bool operator()(const unordered_set<ItemLR1>& lhs, const unordered_set<ItemLR1>& rhs) const {
            return lhs == rhs;  // 使用 unordered_set 自带的相等比较运算符
        }
    };
}

class LR1
{
public:
    // === 文法与first、follow存储 ===
    unordered_map<string, vector<vector<string>>> langMp;//存储文法。格式如下：<规则左部,规则右部或的每一条规则<每一条或的规则的具体细化>
    vector<string> lgName; //所有非终结符的文法记载
    unordered_map<string, unordered_set<string>> firstSet; //每个非终结符的first集合
    unordered_map<string, unordered_set<string>> followSet;//每个非终结符的follow集合

    // === LR0的存储结构 ===
    //对于LR0TransTable，仅仅是为了在QT上展示关系罢了。否则都不需要开这个存储结构
    unordered_map<int, unordered_set<ItemLR0>> LR0DfaStates;//LR0每个状态对应的项目集
    unordered_map<int, unordered_map<string, int>>LR0TransTable; //LR0状态转移表，每个状态通过不同操作符跳到对应下一个状态

    // === LR1的存储结构 ===
    unordered_map<int, unordered_set<ItemLR1>> LR1DfaStates; //LR1每个状态对应的项目集
    unordered_map<int, unordered_map<string, int>>LR1TransTable; //LR1状态转移表，每个状态通过不同操作符跳到对应下一个状态
    unordered_map<ItemLR0, int> GramId; //记录产生式（文法）的规则编号，用于生成DFA分析表
    unordered_map<int, ItemLR0> idToProduction; // GramId 反查编号对应的 ItemLR0

    // === 分析表构建存储结构 ===
    unordered_map<int, unordered_map<string, Action>> lr1Table;// 分析表：状态 -> 符号 -> 动作
    unordered_set<string> grammerTerminalList; //所有终结符记录

    //读入语义动作


    string startLang;//文法开始符号,LR0与LR1共用
    bool isRightGram; //是否为正确文法，是否存在死递归
    bool isSlr; //判断是否为SLR1文法
    int LR0StateID; //LR0的最大编号
    int LR1StateId; //LR1的最大编号
    int hasEmpty; //标志这个文法存在空

    void init(); //初始化处理
    string splitLang(string lang); //切割文法
    void collectGrammarTerminals(); //收集所有终结符
    void getFirstSet(); //求first集合
    bool judgeDieFirst(); //判断是否合理，存在死递归否
    void getFollowSet(); //求follow集合
    void newStart(); //判定是否需要更改文法开始符号

    //LR0部分
    void getClosureLR0(unordered_set<ItemLR0>& items); //对于LR的DFA图内项目集，递归地将所有可能的扩展（包含空规则和符号）添加到项目集中。
    unordered_set<ItemLR0> GotoLR0(const unordered_set<ItemLR0>& state, const string& symbol); //对LR0每个状态进行符号移进的操作，生成新状态，并进行状态合并。
    void DfaLR0(); //获取LR0的DFA图表

    //SLR1部分
    string IsSLR1(); //判断是否为SLR1，并展示判断结果，非SLR1展现原因

    //LR1部分
    void getClosureLR1(unordered_set<ItemLR1>& items); //LR1的DFA状态内项目集，递归扩展
    unordered_set<ItemLR1> GotoLR1(const unordered_set<ItemLR1>& state, const string& symbol); //对LR1每个状态进行符号移进的操作，生成新状态，并进行状态合并。
    void DfaLR1(); //获取LR1的DFA图表

    //构建分析表部分
    void buildGramId(); //构建产生式规则的编号
    void buildLR1Table();//构建分析表

    //构建语法树部分


};
