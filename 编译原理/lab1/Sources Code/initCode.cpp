/*
* 完成日期：2024-9-17
* 作者：vajackye/黄泽基
* 学校：SCNU-CS-2022级
* 版本：0.1--version
*/
#include "initCode.h"

unordered_map<string, int> strToKey;
unordered_map<string, int> symbol;

/*
说明：
    以下为调用该封装包时需要初始化*1次的函数
*/


//函数：
//函数1：关键字映射，初始化
void iterString() {

    for (int i = AS; i <= UNION; i++) {
        keyWord kw = static_cast<keyWord>(i);
        string value = kwToString(kw);
        strToKey[value] = i;
    }
}

//函数2：标点符号映射，初始化，为1表示存在该东西
void iterSymbol() {
    int counter = 1;
    //操作符：1--36
    // 算术运算符
    symbol["+"] = counter++;
    symbol["-"] = counter++;
    symbol["*"] = counter++;
    symbol["/"] = counter++;
    symbol["%"] = counter++;

    // 位运算符
    symbol["^"] = counter++;
    symbol["!"] = counter++;
    symbol["&"] = counter++;
    symbol["|"] = counter++;

    // 短路逻辑运算符
    symbol["&&"] = counter++;
    symbol["||"] = counter++;

    // 移位运算符
    symbol["<<"] = counter++;
    symbol[">>"] = counter++;

    // 复合赋值运算符
    symbol["+="] = counter++;
    symbol["-="] = counter++;
    symbol["*="] = counter++;
    symbol["/="] = counter++;
    symbol["%="] = counter++;
    symbol["^="] = counter++;
    symbol["&="] = counter++;
    symbol["|="] = counter++;
    symbol["<<="] = counter++;
    symbol[">>="] = counter++;

    // 比较运算符
    symbol["="] = counter++;
    symbol["=="] = counter++;
    symbol["!="] = counter++;
    symbol[">"] = counter++;
    symbol["<"] = counter++;
    symbol[">="] = counter++;
    symbol["<="] = counter++;

    // 其他符号
    symbol["@"] = counter++;
    symbol["_"] = counter++;
    symbol["."] = counter++;
    symbol[".."] = counter++;
    symbol["..."] = counter++;
    symbol["..="] = counter++;

    // 分隔符  : 37----45
    symbol[","] = counter++;
    symbol[";"] = counter++;
    symbol[":"] = counter++;
    symbol["::"] = counter++;

    // 箭头
    symbol["->"] = counter++;
    symbol["=>"] = counter++;

    // 宏和属性符号
    symbol["#"] = counter++;
    symbol["$"] = counter++;
    symbol["?"] = counter++;

    // 定界符 46--51
    symbol["{"] = counter++;
    symbol["}"] = counter++;
    symbol["["] = counter++;
    symbol["]"] = counter++;
    symbol["("] = counter++;
    symbol[")"] = counter++;
}



/*
说明：以下为封装的检查函数，用于判断类型
提示：通常遇到空格分隔符号，作为分割一个字符串的行为。可减少测试次数（针对关键字和标识符）
*/


//函数：检查是否为关键字，字符串->关键字。strToKey
//只进行简单的完成串的检查（对关键字空格外部处理）
bool checkKeys(const string& value) {
    if (strToKey.find(value) == strToKey.end()) return false;
    return true;
}

//函数：检查是否为标识符
//非字母的**其余字符**在外部手动判断（空格分割字符串）。内部只做基本判断。
bool checkIdentifiers(const string& value) {
    //先判断是不是关键字
    if (strToKey.find(value) == strToKey.end()) {
        //单个_不行
        if (value == "_") return false;
        //原生标识符不能为以下几个：
        if (value == "r#crate" || value == "r#self" || value == "r#super" || value == "r#self")
            return false;
        //非法原生
        if (value == "r#")
            return false;
        //正常字符，以字符开头或者_开头
        if (isalpha(value[0]) || value[0] == '_')
            return true;
    }
    return false;
}

//函数：检查是否为标点符号
bool checkSymbol(const string& value) {
    //一般要进行字符串的连续判断：now+next or next empty(两个，或者最后一个)，
    // 对于乘号或者除号，不存在同时使用，故不需要担心与注释等冲突
    return symbol.find(value) != symbol.end();
}

//函数：检查是否为注释

bool checkExplanation(const string& value) {
    //注释字符串需要进行3重判断(/**等3个字符),
    //同时跳跃性的审查后面元素直到遇到*/ 或 //整行注释
    if (value == "//") return true;
    else if (value == "///") return true;
    else if (value == "/*") return true;
    else if (value == "/**") return true;
    else if (value == "//!") return true;
    else if (value == "/*!") return true;
    else if (value == "*/") return true;
    else return false;
}
