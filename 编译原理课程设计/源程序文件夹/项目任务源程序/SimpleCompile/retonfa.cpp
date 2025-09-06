/***************************************************************
 * 版权所有 (C) 20222121007 计算机科学与技术师范 黄泽基
 * 保留所有权利
 *
 * 模块名称：retonfa.cpp
 * 模块功能：本模块用于实现后缀表达式转NFA
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
#include "ReToNfa.h"

using namespace std;

// 创建新状态，自动分配递增 id
int ReToNfa::createState(NFA& nfa)
{
    int newStateId = nfa.states.size();
    NFAState state;
    state.id = newStateId;
    nfa.states.push_back(state);
    return newStateId;
}

// 添加转换边 (fromState --symbol--> toState)，ε 转换默认用 "#" 表示
void ReToNfa::addTransition(NFA& nfa, int fromState, string symbol, int toState)
{
    nfa.states[fromState].transitions[symbol].insert(toState);
}

/**
 * @brief ReToNfa::buildNFA 后缀表达式转 NFA 核心函数 -->已修正多字符问题
 * @param postfixRegex
 * @param ruleName
 * @return
 */
NFA ReToNfa::buildNFA(const string& postfixRegex, const string& ruleName)
{
    NFA nfa;
    std::stack<std::pair<int, int>> nfaStack;
    // 存子 NFA 的起始和终止状态编号
    for (size_t i = 0; i < postfixRegex.size(); i++)
    {
        char c = postfixRegex[i];
        //处理数字字母（单字符）
        if (isalnum(c))
        {
            int start = createState(nfa);
            int end = createState(nfa);
            addTransition(nfa, start, string(1,c), end);
            nfaStack.push({ start,end });
            //添加到字母表中。
            this->symbols[ruleName].insert(string(1,c));
        }
        //处理转义字符 \x
        else if (c == '\\')
        {
            string tg = "";
            tg += string(1,postfixRegex[++i]); //整体：可拆分++i; 避免BUG
            //cout << tg << endl << endl;
            int start = createState(nfa);
            int end = createState(nfa);
            addTransition(nfa, start,tg, end);
            nfaStack.push({ start,end });
            //记录对应的转移表
            this->symbols[ruleName].insert(tg);
        }
        // 处理正则运算符
        else if(isOperator(c))
        {
            if (c == '*')
            {
                pair<int,int> frag = nfaStack.top(); nfaStack.pop();
                int start = createState(nfa);
                int end = createState(nfa);

                addTransition(nfa, start, "#", frag.first);
                addTransition(nfa, frag.second, "#", end);
                addTransition(nfa, frag.second, "#", frag.first);
                addTransition(nfa, start, "#", end);

                nfaStack.push({ start,end });
            }
            else if (c == '?')
            {
                pair<int, int> frag = nfaStack.top(); nfaStack.pop();
                int start = createState(nfa);
                int end = createState(nfa);

                addTransition(nfa, start, "#", frag.first);
                addTransition(nfa, frag.second, "#", end);
                addTransition(nfa, start, "#", end);

                nfaStack.push({ start,end });
            }
            else if (c == '|')
            {
                pair<int, int> frag2 = nfaStack.top(); nfaStack.pop();
                pair<int, int> frag1 = nfaStack.top(); nfaStack.pop();
                int start = createState(nfa);
                int end = createState(nfa);

                addTransition(nfa, start, "#", frag1.first);
                addTransition(nfa, start, "#", frag2.first);
                addTransition(nfa, frag1.second, "#", end);
                addTransition(nfa, frag2.second, "#", end);

                nfaStack.push({ start,end });
            }
            else if (c == '.')
            {
                pair<int, int> frag2 = nfaStack.top(); nfaStack.pop();
                pair<int, int> frag1 = nfaStack.top(); nfaStack.pop();

                addTransition(nfa, frag1.second, "#", frag2.first);
                nfaStack.push({ frag1.first,frag2.second });
            }
        }
        // 特殊字符
        else {
            int start = createState(nfa);
            int end = createState(nfa);
            addTransition(nfa, start, string(1,c),end);
            nfaStack.push({ start,end });
            //记录对应的转移表
            this->symbols[ruleName].insert( string(1,c));
        }
    }

    pair<int,int> final = nfaStack.top();
    nfa.startState = final.first;
    nfa.acceptStates.insert(final.second);

    return nfa;//以防万一再返回一次
}

//迭代所有NFA节点
void ReToNfa::checkAllNode() {
    cout << "===== NFA 状态节点信息 =====" << endl;
    for (const auto& rule : this->finalNFA) { // 遍历所有 NFA 规则
        const string& ruleName = rule.first; // 规则名称
        const NFA& nfa = rule.second; // NFA 结构

        cout << "规则: " << ruleName << endl;
        cout << "起始状态: " << nfa.startState << endl;
        cout << "终结状态: ";
        for (int acc : nfa.acceptStates) {
            cout << acc << " ";
        }
        cout << endl;

        // 遍历 NFA 的所有状态
        for (const auto& state : nfa.states) {
            cout << "状态 " << state.id << " :" << endl;
            for (const auto& trans : state.transitions) {
                const string& symbol = trans.first;
                const set<int>& targets = trans.second;
                cout << "  --[" << symbol << "]--> ";
                for (int target : targets) {
                    cout << target << " ";
                }
                cout << endl;
            }
        }
        cout << "---------------------------" << endl;
    }
    cout << "===========================" << endl;
}

//清除所有数据
void ReToNfa::clear()
{
    finalNFA.clear();
    std::stack<std::pair<int,int>>().swap(nfaStack);
    symbols.clear();
}

