/*
* 完成日期：2024-9-17
* 作者：vajackye/黄泽基
* 学校：SCNU-CS-2022级
* 版本：0.1--version
*/
#include "initCode.h"
#include <fstream>

/**
* 未写宏专题，只特判了一个println!宏在标识符部分，而且是简单的特判。一行中开头的（可含空格）部分，不能有其余字符(连着写的，与println不分开的）
* 未判断部分没用过的字符如 "...",只判断了一个for的".."
* 不支持注释嵌套，如要增加，可以在注释部分增加一个计数器，统计/ *和* /出现次数是否相同
*
*/


//需要转换类型的字符串，转换成QT输出格式：QString
string store = "";
//注释是否分行
int expFlag = 0;
//判断原生字符串还是原生标识符
int rcFlag = 0;
//判断是否进行了修改操作
bool exChange = false;


void check(string rust);	//执行函数
void clear(string &rust);	//清除前导空格
void isSymbolKind(string lineJudge);	//判断并解决标点符号类型
int zhushi(int index, const string& rust);	//注释处理
int Identify(int index, const string& rust);	//标识符处理
int keyWords(int index, const string& rust);	//关键字处理
int Symbol(int index, const string& rust);		//标点符号处理
int interFace(int index, const string& rust, int rcaFlag);	//字面量处理



//待修改
string doAnalysis(const string& filePath)
{
    //清理先前的存储结果
    store.clear();

    //打开文件（传入文件）
    ifstream file(filePath);
    if(!file.is_open()) {
        return "Error: Could not open file " + filePath;
    }


    //初始化
    iterKeyword();
    iterString();
    iterSymbol();

    string rust;
    //getline(file, rust)
    while (getline(file, rust))
    {
        if (expFlag != 1)
            clear(rust);

        store += rust; //得清理前导空格！void clear()函数
        store += '\n';
        check(rust);
        if(expFlag != 1)
            store += '\n';
    }
    //结束
    file.close();
    //返回分析结果
    return store;
}



//---------------------------------------------------------------------------------------
void check(string rust)
{

    //保证在一次for循环下来是能够读取完一个单词的。

    //判断字面量，关键字，标识符，标点符号，注释
    for (int i = 0; i < rust.length(); i++)
    {
        exChange = false; //每次重置

        //判断是选用哪一个函数处理
        if (expFlag == 1)
        {
            i = zhushi(i, rust);
            continue;
        }
        //不妨加一个空格特判，提高效率
        while (isspace(rust[i]) && i < rust.length())
            i++;


        i = zhushi(i, rust);
        if (!exChange) //相等说明上面执行失败
        {
            i = keyWords(i, rust);
        }
        if (!exChange) //相等说明上面执行失败
        {
            i = Identify(i, rust);
        }
        if (!exChange) //相等说明上面执行失败
        {
            i = Symbol(i, rust);
        }
        if (!exChange) //相等说明上面执行失败
        {
            i = interFace(i, rust, rcFlag);
        }
    }
}

//注释处理
int zhushi(int index, const string& rust) {
    int befIdx = index;
    string deal;

    //单行注释
    if (rust.length() >= 2 && rust.substr(index, 2) == "//" && !expFlag)
    {
        while (index < rust.length())
        {
            deal += rust[index++];
        }
        store += deal + ": 单行注释\n";
        exChange = true; //修改成功
        return index - 1; //return final
    }
    //多行注释
    else if (rust.length() >= 2 && rust.substr(index, 2) == "/*" && !expFlag)
    {
        expFlag = 1; //多行注释开始了
        deal += "/*";
        index += 2;
        // 多行注释开始，持续读取直到遇到 "*/"
        while (index < rust.length())
        {
            deal += rust[index++];
            // 检查是否遇到块注释结束符 "*/"
            if (deal.size() >= 2 && deal.substr(deal.length() - 2) == "*/")
            {
                store += deal + ": 多行注释\n";
                expFlag = 0; //结束多行注释
                exChange = true; //修改成功
                return index - 1; // final
            }
        }
        store += deal + ": 多行注释（未结束）\n";
        exChange = true; //修改成功
        return index - 1; //return final
    }
    //多行注释中属于注释的一行，继续解决
    else if (expFlag) {
        while (index < rust.length())
        {
            deal += rust[index++];
            // 检查是否遇到块注释结束符 "*/"
            if (deal.size() >= 2 && deal.substr(deal.length() - 2) == "*/")
            {
                store += deal + ": 多行注释\n";
                expFlag = 0; //结束多行注释
                exChange = true; //修改成功
                return index - 1; // final
            }
        }
        store += deal + ": 多行注释（未结束）\n";
        exChange = true; //修改成功
        return index - 1; //return final
    }
    return befIdx; //no deal，return before
}


//标识符处理
/*未处理r#的r#crate等超标词报错词*/
int Identify(int index, const string& rust) {
    int befIdx = index; //假设后面出问题了，溯源。
    string deal;

    //特判一个println!宏。若写了宏专题，此处应该删去
    if (rust.substr(index, 7) == "println" && index + 7 < rust.length() && rust[index + 7] == '!') {
        deal = "println!";
        index += 8; // 跳过 println! 宏
        store += deal + ": 宏\n";
        exChange = true; // 修改成功
        return index - 1; // final
    }

    //判断标识符,注意如:main()等问题。
    //_开头
    if (rust[index] == '_')
    {
        deal += rust[index++];
        while (index < rust.length() && (isalpha(rust[index]) || isdigit(rust[index]) || rust[index] == '_'))
        {
            deal += rust[index++];
        }
        if (deal.length() == 1) return index - 1; //is no Identify

        store += deal + ": 标识符\n";
        exChange = true; //修改成功
        return index - 1; //final
    }
    //原生标识符 r#
    else if (index + 1 < rust.length() && rust[index] == 'r' && rust[index + 1] == '#')
    {
        deal += "r#";
        index += 2;
        while (index < rust.length() && (isalpha(rust[index]) || isdigit(rust[index]) || rust[index] == '_'))
        {
            deal += rust[index++];
        }
        if (deal.length() == 2)
        {
            rcFlag = 1; //修正，表明是原生字符串
            return index - 2; //是原生字符串"", return final
        }

        store += deal + ": 标识符(原生)\n";
        exChange = true; //修改成功
        return index - 1; //final
    }
    //字母开头
    else if (isalpha(rust[index]))
    {
        deal += rust[index++];
        while (index < rust.length() && (isalpha(rust[index]) || isdigit(rust[index]) || rust[index] == '_'))
        {
            deal += rust[index++];
        }
        store += deal + ": 标识符\n";
        exChange = true; //修改成功
        return index - 1; //final
    }
    //都匹配失败，溯源
    return befIdx;
}


//关键字处理
int keyWords(int index, const string& rust) {
    int befIdx = index; //如果不是关键字，溯源
    string deal;
    //关键字全部都是字母
    if (isalpha(rust[index])) {
        while (index < rust.length() && isalpha(rust[index]))
            deal += rust[index++];
    }

    if (!checkKeys(deal)) return befIdx; //说明不是关键字
    store += deal + ": 关键字\n";
    exChange = true;
    return index - 1; // final
}


//标点符号处理
int Symbol(int index, const string& rust) {
    int befIdx = index;
    string deal;

    deal += rust[index++];

    //如果当前是标点符号
    if (checkSymbol(deal))
    {
        string befDeal = deal; //记录回溯遇到非标点符号
        //看看是否有多字符连接
        while (index < rust.length())
        {
            befDeal = deal;
            deal += rust[index++];

            //执行到非标点符号了
            if (!checkSymbol(deal)) {
                deal = befDeal;
                store += deal;
                isSymbolKind(deal); //判断符号种类
                exChange = true;
                return index - 2; //final
            }
        }
        store += deal; //标点符号刚好结尾。
        isSymbolKind(deal); //判断符号种类
        exChange = true;
        return index - 1; //final
    }
    return befIdx; //不是标点符号,溯源
}


//字面量处理
int interFace(int index, const string& rust, int rcaFlag = 0) {
    int befIdx = index;
    string deal;

    //判断是否为字符串字面量，关键标识:"或者r#也可，只支持单行字符串！
    if (rust[index] == '"')
    {
        deal += rust[index++];
        while (index < rust.length() && rust[index] != '"')
        {
            deal += rust[index++];
        }
        deal += '"';
        index++;
        store += deal + ": 字符串字面量\n";
        exChange = true; //修改成功
        return index - 1; //final
    }
    //r#必须是对称使用的~，并且rcaFlag检验了不是原生标识符！
    else if (index + 1 < rust.length() && rust[index] == 'r' && rust[index + 1] == '#' && rcaFlag)
    {
        index += 2;
        int counter = 1; //统计#数目

        //快进到没有#
        while (index < rust.length() && rust[index] == '#')
            counter++, index++;
        //if (index >= rust.length() || rust[index] != '"') {
        //	// 没有找到开始的双引号，错误的 r# 字符串（按假设这里可以忽略处理错误）
        //	return index;
        //}
        index++; // 跳过第一个 "，第一个"也作为开头

        //开始统计字符串
        while (index < rust.length())
        {
            //遇到结束引号，检查后面的#数目是否正确，如果正确说明到尾部了
            if (rust[index] == '"') {
                int hash_cnt = 0;
                index++; //跳过引号
                while (index < rust.length() && rust[index] == '#')
                    hash_cnt++, index++;
                if (hash_cnt == counter) {
                    store += deal + ": 原生字符串\n";
                    rcFlag = 0; //重置r#标识符
                    exChange = true; //修改成功
                    return index - 1; //final
                }
                //#数目不匹配，说明未到结尾
                else {
                    deal += '\"';
                    continue;
                }
            }
            deal += rust[index++]; //继续读取内容
        }
    }
    //判断字符字面量
    else if (rust[index] == '\'') {
        deal += rust[index++];
        if (index + 1 < rust.length())
        {
            deal += rust[index++];
            deal += rust[index++];
        }
        exChange = true; //修改成功
        store += deal + ": 字符字面量\n";
        return index - 1; //final
    }
    //判断数字字面量
    else if (isdigit(rust[index])) {
        int numKd = 0; //进制判断
        bool isFloat = false; //判断浮点与否
        deal += rust[index++];
        string befStr = deal; //存储之前的状态

        //遇到了循环符号for xx..xx
        if (index  < rust.length() && rust[index-1] == '.' && rust[index] == '.')
        {
            store += deal + ": 数字字面量(十进制整数)\n";
            exChange = true; //修改成功
            return index - 1; //final
        }

        // 先判断进制，同时判定是否第一个数字就完结了。
        if (index < rust.length()) {
            if (rust[index] == 'b') {
                numKd = 1;  // 二进制 0b
                deal += rust[index++];
            }
            else if (rust[index] == 'o') {
                numKd = 2;  // 八进制 0o
                deal += rust[index++];
            }
            else if (rust[index] == 'x') {
                numKd = 3;  // 十六进制 0x
                deal += rust[index++];
            }
            else if (rust[index] == '.' || rust[index] == 'e' || rust[index] == 'E' || rust[index] == 'f') {
                isFloat = true; //浮点数
                deal += rust[index++];
            }
            else if (isdigit(rust[index]) || rust[index] == '_' || rust[index] == 'i' || rust[index] == 'u') {
                deal += rust[index++];
            }
            else //都不满足，说明分割了
            {
                store += deal + ": 数字字面量(十进制整数)\n";
                exChange = true; //修改成功
                return index - 1; // final
            }
        }

        // 满足上面条件，则继续遍历所有数字
        while (index < rust.length()) {

            // 遇到标点符号或其他合法分隔符，终止
            if (checkSymbol(string(1, rust[index])) &&
                rust[index] != '.' &&
                rust[index] != '_' &&
                !((rust[index - 1] == 'e' || rust[index - 1] == 'E') && (rust[index] == '+' || rust[index] == '-')))
            {
                break;
            }
            //遇到了循环符号
            if (rust[index - 1] == '.' && rust[index] == '.')
            {
                store += befStr + ": 数字字面量(十进制整数)\n";
                exChange = true; //修改成功
                return index - 2; //final
            }
            if (rust[index] == '.' || rust[index] == 'e' || rust[index] == 'E' || rust[index] == 'f')
                isFloat = true;
            befStr = deal;
            deal += rust[index++];
        }

        // 判断数值类型：
        if (isFloat) {
            store += deal + ": 数字字面量(浮点数)\n";
        }
        else {
            switch (numKd) {
            case 1:
                store += deal + ": 数字字面量(二进制整数)\n";
                break;
            case 2:
                store += deal + ": 数字字面量(八进制整数)\n";
                break;
            case 3:
                store += deal + ": 数字字面量(十六进制整数)\n";
                break;
            default:
                store += deal + ": 数字字面量(十进制整数)\n";
            }
        }
        exChange = true; //修改成功
        return index - 1; // final
    }
    return befIdx; //失败了
}


//清理前导空格
void clear(string &rust)
{
    size_t start = rust.find_first_not_of(" \t\n\r\f\v");
    //如果该行非空
    if (start != string::npos)
    {
        rust = rust.substr(start); //去掉前导空格
    }
    else
    {
        rust.clear();
    }
}


//判断标点符号种类：操作符，分隔符，定界符
void isSymbolKind(string lineJudge)
{
    //操作符
    if (symbol[lineJudge] <= 36) store += ": 操作符\n";
    //分隔符
    else if (symbol[lineJudge] <= 45) store += ": 分隔符\n";
    //定界符
    else if (symbol[lineJudge] <= 51) store += ": 定界符\n";
}
