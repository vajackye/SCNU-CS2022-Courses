/***************************************************************
 * 版权所有 (C) 20222121007 计算机科学与技术师范 黄泽基
 * 保留所有权利
 *
 * 模块名称：lexsource.cpp
 * 模块功能：本模块用于实现词法分析源程序打印
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
#include "lexsource.h"

using namespace std;

lexSource::lexSource() {}

string lexSource::generateLexerCode(std::unordered_map<std::string, MinDFA> finalMiniDFA, std::map<std::string, TokenRule> ruleMap)
{
    std::ostringstream code;

    generateHeaderAndStructs(code);
    generateCheckFunctions(code, finalMiniDFA, ruleMap);
    generateMainLexer(code, finalMiniDFA, ruleMap);

    return code.str();
}

void lexSource::generateHeaderAndStructs(std::ostringstream &code)
{
    code << "#include <iostream>\n"
            "#include <string>\n"
            "#include <vector>\n"
            "#include <cctype>\n"
            "#include <map>\n"
            "#include <set>\n"
            "#include <fstream>\n";
    code << "using namespace std;\n\n";

    code << "struct Token {\n";
    code << "    int code;\n";
    code << "    string value;\n";
    code << "};\n\n";

    code << "vector<Token> tokens;\n\n";
}

void lexSource::generateCheckFunctions(std::ostringstream& code, const std::unordered_map<std::string, MinDFA>& finalMiniDFA, const std::map<std::string, TokenRule>& ruleMap)
{
    for (const auto& [ruleName, minDfa] : finalMiniDFA) {
        if (ruleName == "_annotation") continue;
        ostringstream outerCode; //解决外部终态判断
        code << "// DFA 识别函数: " << ruleName << "\n";
        auto tmp = ruleName;
        std::replace(tmp.begin(), tmp.end(), '-', '_');
        code << "int check_" << tmp << "(const string& input, int start) {\n";
        code << "    int state = " << minDfa.start << ";\n";
        code << "    int pos = start;\n";
        code << "    bool isErr = false;\n";
        code << "    while (pos < input.size() && !isErr) {\n";
        code << "        bool Match = false;\n";
        code << "        char ch = input[pos];\n";
        code << "        switch(state) {\n";

        for (const auto& node : minDfa.states) {
            code << "            case " << node.id << ":\n";

            //如果没有边且为终态，直接返回
            if (node.isEnd) {
                outerCode << "if ( state == " << node.id << "){\n";
                outerCode << "   return pos - 1;\n";
                outerCode << "}\n";
            }

            code << "                switch(ch) {\n";
            for (const auto& edge : node.edges) {
                if (edge.c.length() == 1) {
                    code << "                       case '" << edge.c << "': state = " << edge.to << "; Match = true; break;\n";
                }
                else {
                    code << "                       case '" << edge.c[0] << "': state = " << edge.to << "; Match = true; break;\n";
                }
            }
            code << "                }\n";
            code << "                if(!Match) {\n";
            code << "                   isErr=true;\n";
            code << "                   break;";
            code << "                }\n";
            code << "                pos++;\n";
            code << "                break;\n";
        }

        code << "            default: \n";
        code << "                    isErr = true;\n";
        code << "                    \nbreak;\n";
        code << "        }\n";
        code << "    }\n";

        //终态判断，外部代码块
        code << outerCode.str();
        code << "    return -1;\n";
        code << "}\n\n";
    }

    if(finalMiniDFA.find("_NUM") != finalMiniDFA.end()) {
        code << "int check__annotation(const string& input, int start) {\n";
        code << "    int pos = start;\n";
        code << "    if (pos >= input.size()) return -1;\n";
        code << "    // Minic-style: //...\n";
        code << "    if (input[pos] == '/' && pos + 1 < input.size() && input[pos + 1] == '/') {\n";
        code << "        pos += 2;\n";
        code << "        while (pos < input.size() && input[pos] != '\\n') {\n";
        code << "            pos++;\n";
        code << "        }\n";
        code << "        return pos - 1; // 返回最后一个字符位置（不包括换行）\n";
        code << "    }\n";
        code << "    return -1;\n";
        code << "}\n\n";
    }
    else if(finalMiniDFA.find("_number") != finalMiniDFA.end()) {
        code << "int check__annotation(const string& input, int start) {\n";
        code << "    int pos = start;\n";
        code << "    if (pos >= input.size()) return -1;\n";
        code << "    // Tiny-style: { ... }\n";
        code << "    if (input[pos] == '{') {\n";
        code << "        pos++;\n";
        code << "        while (pos < input.size() && input[pos] != '}') {\n";
        code << "            pos++;\n";
        code << "        }\n";
        code << "        if (pos < input.size() && input[pos] == '}') {\n";
        code << "            return pos; // 返回匹配终止位置\n";
        code << "        } else {\n";
        code << "            return -1; // 没有匹配到闭合 }\n";
        code << "        }\n";
        code << "    }\n";
        code << "    return -1;\n";
        code << "}\n\n";
    }
}

void lexSource::generateMainLexer(std::ostringstream &code, const std::unordered_map<std::string, MinDFA> &finalMiniDFA, const std::map<std::string, TokenRule> &ruleMap)
{
    code << "void lexer(const string& input) {\n";
    code << "    int pos = 0;\n";
    code << "    while (pos < input.size()) {\n";
    code << "        int maxLen = -1;\n";
    code << "        string tokenName = \"\";\n";

    //先解决注释问题，注释统一定义为：_annotation命名，先在文件内查询是否存在这个定义
    if (finalMiniDFA.count("_annotation")) {
        code << "        {\n";
        code << "            int len = check__annotation(input, pos);\n";
        code << "            if (len > maxLen) {\n";
        code << "                maxLen = len;\n";
        code << "                tokenName = \"annotation\";\n";
        code << "            }\n";
        code << "        }\n";
    }
    //再解决空格问题，统一把空格给处理掉
    //再解决关键字keyword问题。优先匹配keyword
    if (finalMiniDFA.count("_keyword")) {
        code << "        {\n";
        code << "            int len = check__keyword(input, pos);\n";
        code << "            if (len > maxLen) {\n";
        code << "                maxLen = len;\n";
        code << "                tokenName = \"keyword\";\n";
        code << "            }\n";
        code << "        }\n";
    }

    for (const auto& [ruleName, _] : finalMiniDFA) {
        if (ruleName == "_annotation" || ruleName == "_keyword") continue;

        auto tmp = ruleName;
        std::replace(tmp.begin(), tmp.end(), '-', '_');
        std::string funcName = "check_" + tmp;
        code << "        {\n";
        code << "            int len = " << funcName << "(input, pos);\n";
        code << "            if (len > maxLen) {\n";
        code << "                maxLen = len;\n";
        code << "                tokenName = \"" << ruleName.substr(1,ruleName.length()) << "\";\n";
        code << "            }\n";
        code << "        }\n";
    }

    code << "        if (maxLen == -1) {\n";
    code << "            pos++;\n";
    code << "            continue;\n";
    code << "        }\n";

    code << "        string matched = input.substr(pos, maxLen - pos + 1);\n";
    code << "        int code = -1;\n";
    code << "        if (tokenName != \"annotation\") {\n";

    for (const auto& [ruleName, rule] : ruleMap) {
        if (rule.code != -1) {
            if (rule.multiSymbols) {
                int baseCode = rule.code;

                std::stringstream ss(rule.constantP);
                std::string symbol;
                int offset = 0;

                code << "        if (tokenName == \"" << ruleName.substr(1) << "\") {\n";

                while (std::getline(ss, symbol, '|')) {
                    // 清理空格
                    symbol.erase(std::remove_if(symbol.begin(), symbol.end(), ::isspace), symbol.end());

                    // 处理转义符
                    std::string rawSymbol = symbol;
                    if (rawSymbol[0] == '\\' && rawSymbol.size() == 2) {
                        rawSymbol = rawSymbol[1];
                    }

                    // 转义字符打印时加转义处理
                    std::string printableSymbol = rawSymbol;
                    if (printableSymbol == "\"" || printableSymbol == "\\" || printableSymbol == "\'") {
                        printableSymbol = "\\" + printableSymbol;
                    }

                    code << "            if (matched == \"" << printableSymbol << "\") {\n";
                    code << "                code = " << (baseCode + offset) << ";\n";
                    code << "            }\n";

                    offset++;
                }

                code << "        }\n";
            }
            else
                code << "            if (tokenName == \"" << ruleName.substr(1) << "\") code = " << rule.code << ";\n";
        }
    }

    code << "            tokens.push_back({code, matched});\n";
    code << "        }\n";
    code << "        pos = maxLen + 1;\n";
    code << "    }\n";
    code << "}\n\n";

    code << "int main() {\n";
    code << "    string filepath;\n";
    code << "    cout << \"请输入源文件路径: \";\n";
    code << "    cin >> filepath;\n";
    code << "    ifstream file(filepath);\n";
    code << "    if (!file) {\n";
    code << "        cerr << \"无法打开源文件！\" << endl;\n";
    code << "        return 1;\n";
    code << "    }\n";
    code << "    string suffix;\n";
    code << "    cout << \"请输入输出文件后缀（如 .lex）: \";\n";
    code << "    cin >> suffix;\n";
    code << "    string line, input;\n";
    code << "    while (getline(file, line)) input += line + '\\n';\n";
    code << "    file.close();\n";
    code << "    lexer(input);\n";

    code << "    size_t dotPos = filepath.find_last_of('.');\n";
    code << "    string baseName = (dotPos == string::npos) ? filepath : filepath.substr(0, dotPos);\n";
    code << "    string outpath = baseName + suffix;\n";

    code << "    ofstream outfile(outpath);\n";
    code << "    if (!outfile) {\n";
    code << "        cerr << \"无法创建输出文件！\" << endl;\n";
    code << "        return 1;\n";
    code << "    }\n";
    code << "    for (const auto& token : tokens) {\n";
//    code << "        outfile << \"(\" << token.code << \", '\" << token.value << \"')\\n\";\n";
    code << "        outfile << token.code << \" \" << token.value <<\" \"; ";
    code << "    }\n";
    code << "    outfile.close();\n";
    code << "    cout << \"词法分析完成，结果保存在：\" << outpath << endl;\n";
    code << "    return 0;\n";
    code << "}\n";

}
