#pragma once
#include <iostream>
#include <string>
#include <numeric>
#include "minidfa.h"
#include "predore.h"

class lexSource
{
public:
    lexSource();
    std::string generateLexerCode(std::unordered_map<std::string, MinDFA> finalMiniDFA,std::map<std::string, TokenRule> ruleMap);

    void generateHeaderAndStructs(std::ostringstream& code);
    void generateCheckFunctions(std::ostringstream& code, const std::unordered_map<std::string, MinDFA>& finalMiniDFA, const std::map<std::string, TokenRule>& ruleMap);
    void generateMainLexer(std::ostringstream& code, const std::unordered_map<std::string, MinDFA>& finalMiniDFA, const std::map<std::string, TokenRule>& ruleMap);
};

