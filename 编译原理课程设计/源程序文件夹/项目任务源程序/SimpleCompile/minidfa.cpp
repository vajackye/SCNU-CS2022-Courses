/***************************************************************
 * 版权所有 (C) 20222121007 计算机科学与技术师范 黄泽基
 * 保留所有权利
 *
 * 模块名称：minidfa.cpp
 * 模块功能：本模块用于最小化DFA操作
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
#include "MiniDfa.h"
#include <iostream>

using namespace std;

/*
* 输入：ruleName--命名规则，dfaNodes--DFA的所有节点以及转移边，symbols--DFA所有边的转移符号
*/
void MiniDfa::minimize(const std::string& ruleName, const std::vector<DFANode>& dfaNodes, const std::unordered_set<std::string>& symbols) {

    this->dfaNode = dfaNodes;
    this->kind.clear();
    this->eq.clear();
    this->stateCnt = 2;

    //初始所有dfaNode划分为两个状态：0（终态）和1（非终态）
    set<int>end, nonEnd;
    for (DFANode node : dfaNode) {
        if (node.id >= this->kind.size()) this->kind.resize(node.id + 1);
        if (node.isEnd) {
            end.insert(node.id);
            this->kind[node.id] = 0;
        }
        else {
            nonEnd.insert(node.id);
            this->kind[node.id] = 1;
        }
    }
    //开始存储等价类到类集合
    if (!end.empty())
        eq.push_back(end);
    if (!nonEnd.empty())
        eq.push_back(nonEnd);

    //开始逐步分裂集合，划分更多状态
    while (true) {
        int preNum = this->stateCnt;

        //遍历符号表，通过每一个符号逐步分裂
        for (string sym : symbols) {
            for (int i = 0; i < preNum; i++) {
                split(i, sym, dfaNode);
            }
        }
        //如果没有变化
        if (preNum == this->stateCnt) break;
    }

    //构建状态转移表
    buildMinimizedDFA(ruleName);
}

/*
* 输入：等价类节点编号;划分字符;原dfaNode
*/
void MiniDfa::split(int spId, const std::string& sym, const std::vector<DFANode>& dfaNodes) {
    set<int> curSet = this->eq[spId];

    if (curSet.size() == 1) return; //==1 无需分割

    map<int, set<int>> eqKind; //记录状态转移分组结果，key：目标编号，set<int>对应dfa编号集合

    //遍历当前等价类中所有状态
    for (int state : curSet) {
        bool found = false; //标记位，记录当前状态是否找到匹配的转移

        vector<DFAEdge> edges = dfaNodes[state].edges;
        //遍历当前状态所有出边，检查是否有通过sym抵达
        for (DFAEdge edge : edges) {
            if (edge.c == sym) {
                //对边状态插入到相应id，用于切割
                eqKind[this->kind[edge.to]].insert(state);
                found = true;
            }
        }
        if (!found) {
            eqKind[-1].insert(state);
        }
    }

    //遍历eqKind每一个分组，检查是否需要分裂原先集合
    for (auto pir : eqKind) {
        int groupId = pir.first;
        set<int> newSet = pir.second;
        if (newSet.size() < curSet.size()) {
            eq.push_back(newSet); //新分组
            for (int stId : newSet) {
                kind[stId] = this->stateCnt; //将这些节点分配到新的状态内

                curSet.erase(stId); //移除原先的。
            }
            this->stateCnt++;
        }
    }
    this->eq[spId] = curSet;
}

void MiniDfa::buildMinimizedDFA(const std::string& ruleName) {
    std::vector<MinDFANode> miniDfa;
    std::unordered_map<int, int> oldToNew;

    // 构建旧id -> 新id 映射
    for (int newId = 0; newId < eq.size(); newId++) {
        for (int oldId : eq[newId]) {
            oldToNew[oldId] = newId;
        }
    }

    // 创建 MinDFANode 节点
    for (int i = 0; i < eq.size(); i++) {
        MinDFANode node;
        node.id = i;
        node.isEnd = false;

        for (int id : eq[i]) {
            if (dfaNode[id].isEnd) {
                node.isEnd = true;
                break;
            }
        }

        miniDfa.push_back(node);
    }

    // 构建边（从代表状态即可）
    for (int i = 0; i < eq.size(); ++i) {
        int repId = *eq[i].begin();
        for (const DFAEdge& edge : dfaNode[repId].edges) {
            int from = i;
            int to = oldToNew[edge.to];
            std::string sym = edge.c;

            MinDFAEdge tmp;
            tmp.c = sym;
            tmp.to = to;
            miniDfa[from].edges.push_back(tmp);
        }
    }

    // 构建 MinDFA 结构
    MinDFA result;
    result.states = miniDfa;

    // 查找原DFA的初态编号，并映射到最小化后的编号
    int oldStartId = 0;  // 假设原DFA的初始状态是0（你也可以从传入参数中记录）
    if (oldToNew.find(oldStartId) != oldToNew.end()) {
        result.start = oldToNew[oldStartId];
    }

    // 存入 finalMiniDFA
    finalMiniDFA[ruleName] = result;
}

/*
* 输入：当前需要打印的命名规则
*/
void MiniDfa::printMinimizedDFA(const std::string& ruleName) {
    auto it = finalMiniDFA.find(ruleName);
       if (it == finalMiniDFA.end()) {
           std::cout << "No minimized DFA found for rule: " << ruleName << std::endl;
           return;
       }

       const MinDFA& dfa = it->second;
       const std::vector<MinDFANode>& nodes = dfa.states;
       int startId = dfa.start;

       std::cout << "=== Minimized DFA for rule: " << ruleName << " ===\n";

       for (const auto& node : nodes) {
           std::cout << "State " << node.id;
           if (node.id == startId) std::cout << " (Start)";
           if (node.isEnd) std::cout << " (Accept)";
           std::cout << ":\n";

           for (const auto& edge : node.edges) {
               std::cout << "  --[" << edge.c << "]--> State " << edge.to << "\n";
           }
       }

       std::cout << "=============================================\n";
}

//清空所有数据
void MiniDfa::clear()
{
    finalMiniDFA.clear();
}
