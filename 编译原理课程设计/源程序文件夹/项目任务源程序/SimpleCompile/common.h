/*****************************************************************************
*  Copyright (C), 2025, 黄泽基 20222121007
*
*  @file    common.h
*  @brief   项目一与二通用类
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
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <QString>
#include <QVector>
#include <map>

extern std::map<int, std::string> CodeMap; //映射表：code：value

/**
 * @brief opPrecedence 存储正则级别比较
 * @param ch
 * @return
 */
int opPrecedence(char ch);

/**
 * @brief isOperator 检查是否为运算符
 * @param ch
 * @return
 */
bool isOperator(char ch);

/**
 * @brief The Token struct 语法分析编码读入Token存储结构
 */
struct Token {
    int code;
    std::string value;
    Token(){}
    Token(int cd, std::string vl):code(cd),value(vl){}
};

/**
 * @brief The ParseStep struct 分析过程记录结构
 */
struct ParseStep {
    QString stackContent;  // 分析栈内容
    QString inputContent;  // 输入串内容
    QString operation;     // 操作说明（移进、规约、接收）
};

/**
 * @brief The SyntaxTreeNode struct 语法树节点结构
 */
//struct SyntaxTreeNode {
//    int childNum; //当前节点的子节点数目
//    QString type; //类型
//    QString value; //值
//    QVector<SyntaxTreeNode*> child; //孩子节点
//    bool terminal = false; //判断是否为终结符
//};


struct SyntaxTreeNode//语法树
{
    QString Name;
    QVector<SyntaxTreeNode*> son;
    SyntaxTreeNode* bro = nullptr;
};

//定义枚举值标识语法树生成类型
/**
 * 编码方式如下：
 * 0表示忽略当前单词，
 * 1表示当前单词作为根节点，
 * 2表示作为根节点的孩子结点，
 * 3表示作为根节点的兄弟结点
 */
enum TreeAction { IGNORE = '0', ROOT = '1', CHILD = '2', BRO = '3' };

