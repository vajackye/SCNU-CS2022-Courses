/***************************************************************
 * 版权所有 (C) 20222121007 计算机科学与技术师范 黄泽基
 * 保留所有权利
 *
 * 模块名称：nfatodfa.cpp
 * 模块功能：本模块用于实现NFA转DFA
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
#include "NfaToDfa.h"

using namespace std;

void NfaToDfa::NTDFA(const std::string& ruleName, const NFA& nfa, const std::unordered_set<string>& symbols) {
    stat.clear();

    DFA dfa;
    dfa.start = 0;
    dfa.end = nfa.acceptStates;
    dfa.symbol = symbols;

    std::vector<DFANode> tempDfaNodes;
    std::stack<int> s;
    int cnt = 0;

    // 初始闭包
    DFANode startNode;
    startNode.closure = epClosure({ nfa.startState }, nfa);
    startNode.id = cnt++;
    startNode.isEnd = isEndState(startNode.closure, nfa.acceptStates);
    tempDfaNodes.push_back(startNode);
    stat.insert(startNode.closure);
    s.push(0);

    while (!s.empty()) {
        int now = s.top(); s.pop();
        for (const auto& sym : symbols) {
            std::set<int> moved = move(tempDfaNodes[now].closure, sym, nfa);
            if (moved.empty()) continue;

            if (stat.find(moved) == stat.end()) {
                DFANode newNode;
                newNode.closure = moved;
                newNode.id = cnt++;
                newNode.isEnd = isEndState(moved, nfa.acceptStates);
                tempDfaNodes.push_back(newNode);
                stat.insert(moved);
                s.push(newNode.id);
                tempDfaNodes[now].edges.emplace_back(newNode.id, sym);
            }
            else {
                // 查找已有的闭包编号
                for (const auto& node : tempDfaNodes) {
                    if (node.closure == moved) {
                        tempDfaNodes[now].edges.emplace_back(node.id, sym);
                        break;
                    }
                }
            }
        }
    }

    // 构建转移表
    for (const auto& node : tempDfaNodes) {
        dfa.to[node.id] = node.edges;
    }

    //存储节点数据。用于最小化dfa
    miniNodeMap[ruleName] = tempDfaNodes;

    finalDFA[ruleName] = dfa;
}

bool NfaToDfa::isEndState(const std::set<int>& closure, const std::set<int>& end) {
    for (int state : closure) {
        if (end.count(state)) return true;
    }
    return false;
}

std::set<int> NfaToDfa::epClosure(const std::set<int>& s, const NFA& nfa) {
    std::stack<int> stk;
    std::set<int> res = s;

    for (int state : s) stk.push(state);

    while (!stk.empty()) {
        int curr = stk.top(); stk.pop();
        auto it = nfa.states[curr].transitions.find("#");
        if (it != nfa.states[curr].transitions.end()) {
            for (int next : it->second) {
                if (!res.count(next)) {
                    res.insert(next);
                    stk.push(next);
                }
            }
        }
    }
    return res;
}

std::set<int> NfaToDfa::move(const std::set<int>& s, const std::string& sym, const NFA& nfa) {
    std::set<int> res;
    for (int state : s) {
        auto it = nfa.states[state].transitions.find(sym);
        if (it != nfa.states[state].transitions.end()) {
            res.insert(it->second.begin(), it->second.end());
        }
    }
    return epClosure(res, nfa);
}

//遍历dfa结果
void NfaToDfa::printDFA(const DFA& dfa)
{
    std::cout << "=== DFA 状态信息 ===" << std::endl;
    std::cout << "起始状态: " << dfa.start << std::endl;
    std::cout << "终止状态集: ";
    for (int e : dfa.end) std::cout << e << " ";
    std::cout << "\n-----------------------" << std::endl;

    for (const auto& pr : dfa.to) {
        const auto stateId = pr.first;
        const auto edges = pr.second;
        cout << "状态 " << stateId;
        if (dfa.end.count(stateId)) std::cout << " [终态]";
        std::cout << " 有转移：" << std::endl;
        for (const auto& edge : edges) {
            std::cout << "  --[" << edge.c << "]--> " << edge.to << std::endl;
        }
        std::cout << "-----------------------" << std::endl;
    }
}

//清空所有数据
void NfaToDfa::clear()
{
    finalDFA.clear();
    miniNodeMap.clear();
    stat.clear();
}
