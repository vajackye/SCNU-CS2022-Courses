/*****************************************************************************
*  Copyright (C), 2025, 黄泽基 20222121007
*
*  @file    ReToNfa.h
*  @brief   DFA最小化
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
#include <vector>
#include <set>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "NfaToDfa.h"

// 最小化后的 DFA 边
struct MinDFAEdge {
    std::string c = "#";
    int to = -1;
};

// 最小化后的 DFA 节点
struct MinDFANode {
    int id = -1;
    bool isEnd = false;

    std::vector<MinDFAEdge> edges;
};

//封装
struct MinDFA {
    int start = -1;  // 最小化DFA的初态编号
    std::vector<MinDFANode> states;
};

class MiniDfa {
public:
    std::unordered_map<std::string, MinDFA> finalMiniDFA;  // 每条规则最小化后的 DFA节点

    // 接口函数：对某条规则的 DFA 进行最小化
    void minimize(const std::string& ruleName, const std::vector<DFANode>& dfaNodes, const std::unordered_set<std::string>& symbols);

    void buildMinimizedDFA(const std::string& ruleName); // 构建并存入 finalMiniDFA

    // 打印某条规则的最小化 DFA
    void printMinimizedDFA(const std::string& ruleName);

    //清空所有数据
    void clear();

private:
    std::vector<DFANode> dfaNode;
    std::unordered_set<std::string> symbolSet;
    std::vector<std::set<int>> eq;       // 等价类集合
    std::vector<int> kind;               // 每个 DFA 节点对应的等价类编号
    int stateCnt = 2;

    void split(int spId, const std::string& sym, const std::vector<DFANode>& dfaNodes);  // 分割等价类

};
