/*****************************************************************************
*  Copyright (C), 2025, 黄泽基 20222121007
*
*  @file    ReToNfa.h
*  @brief   NFA转DFA
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
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <string>
#include <map>
#include <stack>
#include <unordered_map>
#include "ReToNfa.h"

// DFA 边转移结构体（存储该节点可到达哪些边）
struct DFAEdge {
    int to = -1;   // 目标节点
    std::string c = "#";   // 转移符号
    DFAEdge(){}
    DFAEdge(int t, std::string ch) :to(t), c(ch) {}
};

// DFA 节点结构体
struct DFANode {
    int id = -1;   // 节点编号
    std::vector<DFAEdge> edges;  // 该节点通过不同边抵达的其他节点
    std::set<int> closure;   // DFA 存储的 NFA 的 ε 闭包（所有等价 NFA 节点）
    bool isEnd = false;  // 是否为终态节点
};

struct DFA {
    int start = 0;  // DFA 初态
    std::set<int> end;  // NFA 原先终态集合编号
    std::unordered_set<std::string> symbol;  // 存储所有可以转移的符号
    std::map<int, std::vector<DFAEdge>> to;  // 记录所有节点的转移，用于构建 DFA 转移表
};

class NfaToDfa {
public:
    std::unordered_map<std::string, DFA> finalDFA;  // 存储所有规则的 DFA
    std::unordered_map<std::string, std::vector<DFANode>> miniNodeMap; //用于最小化dfa时处理
    std::set<std::set<int>> stat;  // 当前 DFA 状态集合

    void NTDFA(const std::string& ruleName, const NFA& nfa, const std::unordered_set<std::string>& symbols);

    void printDFA(const DFA& dfa);

    void clear();//清空所有数据

private:
    bool isEndState(const std::set<int>& closure, const std::set<int>& end);
    std::set<int> epClosure(const std::set<int>& s, const NFA& nfa);
    std::set<int> move(const std::set<int>& s, const std::string& sym, const NFA& nfa);
};
