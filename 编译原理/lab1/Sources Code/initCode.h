/*
* 完成日期：2024-9-17
* 作者：vajackye/黄泽基
* 学校：SCNU-CS-2022级
* 版本：0.1--version
*/
#pragma once
#include <iostream>
#include <unordered_map>
#include <cctype>
#include<string>

using namespace std;

extern unordered_map<string, int> strToKey;
extern unordered_map<string, int> symbol;


enum keyWord
{
    AS = 1, BREAK, CONST, CONTINUE, CRATE, ELSE, ENUM, EXTERN, FALSE,
    FN, FOR, IF, IMPL, IN, LET, LOOP, MATCH, MOD, MOVE, MUT, PUB,
    REF, RETURN, SELFVALUE, SELFTYPE, STATIC, STRUCT, SUPER, TRAIT,
    TRUE, TYPE, UNSAFE, USE, WHERE, WHILE, ASYNC, AWAIT, DYN, ABSTRACT,
    BECOME, BOX, DO, FINAL, MACRO, OVERRIDE, PRIV, TYPEOF, UNSIZED,
    VIRTUAL, YIELD, TRY, UNION
}; //传统枚举，不考虑安全性和作用域

/*
说明：以下为调用该封装包时需要初始化*1次的函数
*/

//函数：内联函数降低复杂度，关键字枚举 ，内联函数定义要放到头文件中
inline string kwToString(keyWord kw) {
    switch (kw) {
    case AS: return "as";
    case BREAK: return "break";
    case CONST: return "const";
    case CONTINUE: return "continue";
    case CRATE: return "crate";
    case ELSE: return "else";
    case ENUM: return "enum";
    case EXTERN: return "extern";
    case FALSE: return "false";
    case FN: return "fn";
    case FOR: return "for";
    case IF: return "if";
    case IMPL: return "impl";
    case IN: return "in";
    case LET: return "let";
    case LOOP: return "loop";
    case MATCH: return "match";
    case MOD: return "mod";
    case MOVE: return "move";
    case MUT: return "mut";
    case PUB: return "pub";
    case REF: return "ref";
    case RETURN: return "return";
    case SELFVALUE: return "self";
    case SELFTYPE: return "selftype";
    case STATIC: return "static";
    case STRUCT: return "struct";
    case SUPER: return "super";
    case TRAIT: return "trait";
    case TRUE: return "true";
    case TYPE: return "type";
    case UNSAFE: return "unsafe";
    case USE: return "use";
    case WHERE: return "where";
    case WHILE: return "while";
    case ASYNC: return "async";
    case AWAIT: return "await";
    case DYN: return "dyn";
    case ABSTRACT: return "abstract";
    case BECOME: return "become";
    case BOX: return "box";
    case DO: return "do";
    case FINAL: return "final";
    case MACRO: return "macro";
    case OVERRIDE: return "override";
    case PRIV: return "priv";
    case TYPEOF: return "typeof";
    case UNSIZED: return "unsized";
    case VIRTUAL: return "virtual";
    case YIELD: return "yield";
    case TRY: return "try";
    case UNION: return "union";
    default: return "";
    }
}

//函数：内联函数降低复杂度，关键字检索，内联函数定义要放到头文件中
inline keyWord stringToKw(string value) {
    if (value == "as") return AS;
    if (value == "break") return BREAK;
    if (value == "const") return CONST;
    if (value == "continue") return CONTINUE;
    if (value == "crate") return CRATE;
    if (value == "else") return ELSE;
    if (value == "enum") return ENUM;
    if (value == "extern") return EXTERN;
    if (value == "false") return FALSE;
    if (value == "fn") return FN;
    if (value == "for") return FOR;
    if (value == "if") return IF;
    if (value == "impl") return IMPL;
    if (value == "in") return IN;
    if (value == "let") return LET;
    if (value == "loop") return LOOP;
    if (value == "match") return MATCH;
    if (value == "mod") return MOD;
    if (value == "move") return MOVE;
    if (value == "mut") return MUT;
    if (value == "pub") return PUB;
    if (value == "ref") return REF;
    if (value == "return") return RETURN;
    if (value == "self") return SELFVALUE;
    if (value == "selftype") return SELFTYPE;
    if (value == "static") return STATIC;
    if (value == "struct") return STRUCT;
    if (value == "super") return SUPER;
    if (value == "trait") return TRAIT;
    if (value == "true") return TRUE;
    if (value == "type") return TYPE;
    if (value == "unsafe") return UNSAFE;
    if (value == "use") return USE;
    if (value == "where") return WHERE;
    if (value == "while") return WHILE;
    if (value == "async") return ASYNC;
    if (value == "await") return AWAIT;
    if (value == "dyn") return DYN;
    if (value == "abstract") return ABSTRACT;
    if (value == "become") return BECOME;
    if (value == "box") return BOX;
    if (value == "do") return DO;
    if (value == "final") return FINAL;
    if (value == "macro") return MACRO;
    if (value == "override") return OVERRIDE;
    if (value == "priv") return PRIV;
    if (value == "typeof") return TYPEOF;
    if (value == "unsized") return UNSIZED;
    if (value == "virtual") return VIRTUAL;
    if (value == "yield") return YIELD;
    if (value == "try") return TRY;
    if (value == "union") return UNION;
}

void iterString();	//函数1：关键字映射，初始化
void iterSymbol();	//函数2：标点符号映射，初始化，为1表示存在该东西

/*
说明：以下为封装的检查函数，用于判断类型
提示：通常遇到空格分隔符号，作为分割一个字符串的行为。可减少测试次数（针对关键字和标识符）
*/


bool checkKeys(const string& value);	//函数：检查是否为关键字，字符串->关键字。strToKey。只进行简单的完成串的检查（对关键字空格外部处理）
bool checkIdentifiers(const string& value);	//函数：检查是否为标识符,非字母的**其余字符**在外部手动判断（空格分割字符串）。内部只做基本判断。
bool checkSymbol(const string& value);		//函数：检查是否为标点符号
bool checkExplanation(const string& value);	//函数：检查是否为注释

