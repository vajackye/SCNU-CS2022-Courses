/*****************************************************************************
*  Copyright (C), 2025, 黄泽基 20222121007
*
*  @file    ReToNfa.h
*  @brief   预处理后正则转NFA
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
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "common.h"

//NFA节点结构
struct NFAState
{
    int id = -1; //起点编号
    std::unordered_map<std::string, std::set<int>> transitions;// 转换表，字符到目标状态集合的映射
};

struct NFA
{
    std::vector<NFAState> states; //节点集合
    int startState; //起始状态编号
    std::set<int> acceptStates; //接受节点编号集合
};

class ReToNfa
{
    public:
        std::unordered_map<std::string, NFA> finalNFA; //最终NFA
        std::stack<std::pair<int, int>> nfaStack; // 存储中间NFA子图 (start, end)
        std::unordered_map<std::string, std::unordered_set<std::string>> symbols; //存储每个规则的所有可遍历字符。

        int createState(NFA& nfa); //新建节点状态
        void addTransition(NFA& nfa, int fromState, std::string symbol, int toState); //连接节点
        NFA buildNFA(const std::string& postfixRegex, const std::string& ruleName); //后缀转NFA主函数
        void checkAllNode(); //迭代所有NFA节点
        void clear(); //清除所有数据
};


