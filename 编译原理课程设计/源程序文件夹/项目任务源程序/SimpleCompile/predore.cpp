/***************************************************************
 * 版权所有 (C) 20222121007 计算机科学与技术师范 黄泽基
 * 保留所有权利
 *
 * 模块名称：pretore.cpp
 * 模块功能：本模块用于实现正则表达式转后缀表达式
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
#include <iostream>
#include "preDoRe.h"

using namespace std;

// 预处理输入
void preDoRe::predoName(string regexLine)
{
    TokenRule rule;

    auto eqPos = regexLine.find('=');

    string left = regexLine.substr(0, eqPos);
    string right = regexLine.substr(eqPos + 1);

    //鲁棒：移除两侧空格
    left.erase(0, left.find_first_not_of(" \t"));
    left.erase(left.find_last_not_of(" \t") + 1);
    right.erase(0, right.find_first_not_of(" \t"));
    right.erase(right.find_last_not_of(" \t") + 1);

    // 移除正则内部所有空格和制表符
    right.erase(remove_if(right.begin(), right.end(), [](unsigned char c) { return isspace(c); }), right.end());

    //判定是否：需要转为DFA
    rule.generateDFA = left[0] == '_';

    //匹配规则是否为：多个单词/有编码
    regex nameRegex(R"(([A-Za-z_][A-Za-z_-]*)(\d+)?(S)?)");
    smatch match;
    if (regex_match(left, match, nameRegex))
    {
        rule.name = match[1];
        if (match[2].matched)
        {
            rule.code = stoi(match[2]);
        }
        rule.multiSymbols = match[3].matched;
    }

    //先展开 []
    string processed = iterReg(right);

    //替换命名规则
    processed = replaceNamedRule(processed);

    //将正闭包a+替换为闭包aa*
    processed = replacePositiveClosure(processed);

    //存入pattern
    rule.pattern = processed;
    rule.constantP = processed;
    this->ruleMap[rule.name] = rule;
    return;
}

// 处理中括号[]
string preDoRe::preMidbrack(string regex)
{
    string finalStr;

    for (int i = 0; i < regex.size(); i++)
    {
        if (regex[i] == ']') break;
        if (regex[i] == '-')
        {
            char startChar = regex[i - 1];
            char endChar = regex[i + 1];
            for (char ch = startChar + 1; ch <= endChar; ch++)
            {
                finalStr += '|';
                finalStr += ch;
            }
            i++;
            continue;
        }
        if (regex[i] == '\\')
        { //处理转义
            finalStr += '|';
            finalStr += regex[i];
            finalStr += regex[i + 1];
            i++;
            continue;
        }
        finalStr += '|';
        finalStr += regex[i];
    }

    finalStr.erase(0, 1); //移除前导|
    finalStr = '(' + finalStr + ')'; //优先级高

    return finalStr;
}

// 迭代正则查找中括号
string preDoRe::iterReg(string regex)
{
    string befStr;

    for (int i = 0; i < regex.size(); i++)
    {
        //新补丁，处理mini-c的[]
        if(regex[i] == '\\' && i + 1 < regex.size()) {
            befStr += "\\";
            i++;
            befStr += regex[i];
            continue;
        }
        if (regex[i] == '[')
        {
            string cg = preMidbrack(regex.substr(i + 1));

            while (regex[i] != ']') i++; //移动到对应的 ]处。
            befStr += cg;
        }
        else
        {
            befStr += regex[i];
        }
    }

    return befStr;
}

// 替换命名规则(展开)
string preDoRe::replaceNamedRule(string regex)
{
    string result;

    for (int i = 0; i < regex.size(); i++)
    {
        if (isalpha(regex[i]) || regex[i] == '_')
        {
            string tmp;
            int startIdx = i;

            while (i < regex.size() && (isalpha(regex[i]) || regex[i] == '_'))
            {
                tmp += regex[i++];
            }
            i--;
            auto it = this->ruleMap.find(tmp); //返回迭代器

            if (it != this->ruleMap.end())
            { //命名规则
                //检查该命名规则是否有缓存，有则不必再递归解决命名
                if (this->cache.find(tmp) != this->cache.end())
                {
                    result += cache[tmp];
                }
                else
                {
                    string pattern = replaceNamedRule(it->second.pattern);
                    cache[tmp] = pattern; //缓存处理的命名规则
                    result += pattern;
                }
            }
            else
            { //非命名规则
                result += tmp;
            }
        }
        else
        { //非字母
            result += regex[i];
        }
    }

    return result;
}

// 替换正闭包符 + 为 aa*
string preDoRe::replacePositiveClosure(string regex)
{
    string result;
    int n = regex.length();

    for (int i = 0; i < n; i++)
    {
        //处理转义字符
        if (regex[i] == '\\')
        {
            result += regex[i++];
            result += regex[i];
            //如果存在正闭包
            if (i + 1 < n && regex[i + 1] == '+')
            {
                result += regex[i - 1] + regex[i] + '*';
            }
            continue;
        }
        //正闭包
        if (regex[i] == '+')
        {
            string preFix; //存储“+”前扫描的部分
            int j = i - 1; //回退指针，扫描“+”前的内容

            //情况1：前面是括号整体内容（）
            if (j >= 0 && regex[j] == ')')
            {
                stack<char>stk;
                stk.push(')');

                //向前回退，直到匹配到：‘（’
                --j;
                while (j >= 0 && !stk.empty())
                {
                    if (regex[j] == ')') stk.push(')');
                    else if (regex[j] == '(') stk.pop();
                    --j;
                }
                //截取括号内的内容
                preFix = regex.substr(j + 2, i - j - 3);

                //整体处理，前半部分(a+ --> aa*的a)以在else部分增加。
                result += "(" + preFix + ")*";
            }
            //剩余情况:普通字符，转义已处理。
            else
            {
                preFix += regex[j];
                result += preFix + '*';
            }
        }
        else
        {
            result += regex[i];//直接添加非 '+' 的字符
        }
    }

    return result;
}

// 对规则统一调用连接符号
void preDoRe::dealAllPoint()
{
    map<string, TokenRule> copyRule = this->ruleMap; //保存旧规则

    for (pair<string, TokenRule> it : copyRule) {
        this->ruleMap[it.first].pattern = minAddMultiple(it.second.pattern);
    }
}

/*
digit=[0-9]
letter=[A-Za-z]
test=digit(abc|def|!=|<<|\(|\)|g)?letter
_num100=(\+|-)?digit+
_ID101=letter(letter|digit)*
_specail200S= \+ | - | \* | / | = | < | <= | <<
*/
/**
 * @brief preDoRe::minAddMultiple 添加连接符号. --》已修正多字符问题
 * @param regex
 * @return
 */
string preDoRe::minAddMultiple(string regex)
{
    string befStr;
    int len = regex.size();

    for (int i = 0; i < len; i++)
    {
        // 1️ 处理转义字符整体
        if (regex[i] == '\\' && i + 1 < len)
        {
            befStr += regex[i];
            befStr += regex[i + 1];
            i++;
            // 判断下一个
            if (i + 1 < len && (isalnum(regex[i + 1]) || regex[i + 1] == '(' || regex[i + 1] == '\\'))
            {
                befStr += '.';
            }
            continue;
        }
        // 2️ 正常字符
        befStr += regex[i];
        // 3️ 当前字符属于不需要连接符情况
        if (regex[i] == '(' || regex[i] == '|') continue;
        //if (regex[i] == '*' || regex[i] == '?' || regex[i] == '|' || regex[i] == '(' || regex[i] == ')') continue;
        if (opPrecedence(regex[i]) > 2 || regex[i] == ')') {
            if (regex[i] == ')' && i + 1 < regex.size() && (isOperator(regex[i + 1]) || regex[i + 1] == ')')) continue;
            if (opPrecedence(regex[i]) > 2 && i + 1 < regex.size() && (isOperator(regex[i + 1]) || regex[i + 1] == ')')) continue;
            befStr += ".";
            continue;
        }
        // 4️ 特殊情况，不在末尾
        if (i + 1 < len)
        {
            // 如果下一个是这些，不加 .
            if (regex[i + 1] == '*' || regex[i + 1] == '?' || regex[i + 1] == '|' || regex[i + 1] == ')') continue;

            befStr += '.';
        }
    }

    // 最后一位是.，去掉
    while (!befStr.empty() && befStr.back() == '.') {
        befStr.pop_back();
    }

    return befStr;
}

// 对规则统一调用转后缀操作
void preDoRe::dealAllPostfix()
{
    for (pair<string, TokenRule> it : this->ruleMap)
    {
        this->postfixMap[it.first] = regexToPostfix(it.second.pattern);
    }
}

// 正则表达式转换为后缀表达式:运算符压入，字符直接跳过
std::string preDoRe::regexToPostfix(const std::string& regex)
{
    stack<char> opStack; //运算符栈
    string postFix;

    for (size_t i = 0; i < regex.length(); i++) {
        char c = regex[i];
        //处理转义字符
        if (c == '\\' && i + 1 < regex.length()) {
            postFix += c; //添加'\'
            postFix += regex[i + 1]; //添加符号
            i++; //跳过下一个
            continue;
        }
        //如果是普通字符
        if (isalnum(c)) {
            postFix += c;
        }
        //左括号
        else if (c == '(') {
            opStack.push(c);
        }
        //右括号
        else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postFix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty())opStack.pop(); //弹出左括号
        }
        //操作符（双目）：栈顶比入栈高，则一直移出(直到栈顶优先级低于入栈）并加到后缀表达式后，最后入栈的入栈
        else if (opPrecedence(c) > 0 && opPrecedence(c) < 3 ) {
            while (!opStack.empty() && opPrecedence(opStack.top()) >= opPrecedence(c)) {
                postFix += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
        //剩余其他标点符号
        else {
            postFix += c;
        }
    }
    //最后清空栈
    while (!opStack.empty()) {
        postFix += opStack.top();
        opStack.pop();
    }
    return postFix;
}

//判断是否存在命名
bool preDoRe::getPattern(std::string ruleName)
{
    return this->ruleMap.find(ruleName) != this->ruleMap.end();
}

//打印规则
void preDoRe::printRule()
{
    for (std::pair<std::string, TokenRule> name : ruleMap)
    {
        cout << name.first << " " << name.second << endl;
    }
}

//打印后缀规则
void preDoRe::printPostfix()
{
    for (pair<string, string> name : this->postfixMap) {
        cout << name.first << " " << name.second << endl;
    }
}

//清空数据
void preDoRe::clear()
{
    ruleMap.clear();
    cache.clear();
    postfixMap.clear();
}


