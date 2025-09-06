/**
*****************************************************************************
*  Copyright (C), 2025, 黄泽基 20222121007
*
*  @file    preDoRe.h
*  @brief   预处理输入正则符号文件
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
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <regex>
#include <stack>
#include "common.h"

//存储命名规则
struct TokenRule {
    std::string name;		//命名名字
    int code = -1;			//起始编码，默认-1则没有
    std::string pattern;	//正则表达式内容
    std::string constantP;  //持久化正则，内容不变
    bool generateDFA;		//是否需要生成DFA图
    bool multiSymbols;		//判断是否是多个单词

    // 定义排序规则
    bool operator<(const TokenRule& other) const {
        return name < other.name;
    }

    //输出重载
    friend std::ostream& operator<<(std::ostream& os, const TokenRule& rule){
        os << "Name: " << rule.name
            << ", Code: " << rule.code
            << ", DFA: " << (rule.generateDFA ? "Yes" : "No")
            << ", Multi: " << (rule.multiSymbols ? "Yes" : "No")
            << ", Pattern: " << rule.pattern;
        return os;
    }

};

class preDoRe {
public:
    std::map<std::string, TokenRule> ruleMap; //存储规则
    std::unordered_map<std::string, std::string> cache; //用于缓存已处理的命名规则的RE
    std::unordered_map<std::string, std::string> postfixMap; //存储规则映射的后缀表达式<命名, 后缀>
    //预处理输入
    void predoName(std::string regex);

    //预处理中括号[]
    std::string preMidbrack(std::string regex);

    //展开中括号
    std::string iterReg(std::string regex);

    //替换命名规则(展开)
    std::string replaceNamedRule(std::string regex);

    //替换正闭包符 + 为 aa*
    std::string replacePositiveClosure(std::string regex);

    //对所有规则统一操作连接符号
    void dealAllPoint();

    //添加连接符号.
    std::string minAddMultiple(std::string regex);

    //对所有规则统一转后缀表达操作
    void dealAllPostfix();

    //正则转后缀表达式
    std::string regexToPostfix(const std::string& regex);

    //判断是否存在命名
    bool getPattern(std::string ruleName);

    //打印规则
    void printRule();

    //打印后缀规则
    void printPostfix();

    //清空数据
    void clear();
};

