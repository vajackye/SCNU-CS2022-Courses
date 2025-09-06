#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <set>
#include <fstream>
using namespace std;

struct Token {
    int code;
    string value;
};

vector<Token> tokens;

// DFA 识别函数: _ID
int check__ID(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                       case '8': state = 0; Match = true; break;
                       case '7': state = 0; Match = true; break;
                       case '6': state = 0; Match = true; break;
                       case '3': state = 0; Match = true; break;
                       case '4': state = 0; Match = true; break;
                       case '2': state = 0; Match = true; break;
                       case '1': state = 0; Match = true; break;
                       case 'Y': state = 0; Match = true; break;
                       case 'W': state = 0; Match = true; break;
                       case 'S': state = 0; Match = true; break;
                       case 'R': state = 0; Match = true; break;
                       case 'Q': state = 0; Match = true; break;
                       case 'P': state = 0; Match = true; break;
                       case 'O': state = 0; Match = true; break;
                       case '9': state = 0; Match = true; break;
                       case 'N': state = 0; Match = true; break;
                       case 'Z': state = 0; Match = true; break;
                       case 'M': state = 0; Match = true; break;
                       case '5': state = 0; Match = true; break;
                       case 'o': state = 0; Match = true; break;
                       case 'm': state = 0; Match = true; break;
                       case 'l': state = 0; Match = true; break;
                       case 'g': state = 0; Match = true; break;
                       case 'p': state = 0; Match = true; break;
                       case 'f': state = 0; Match = true; break;
                       case 'y': state = 0; Match = true; break;
                       case 'n': state = 0; Match = true; break;
                       case 'X': state = 0; Match = true; break;
                       case 'V': state = 0; Match = true; break;
                       case 'E': state = 0; Match = true; break;
                       case '_': state = 0; Match = true; break;
                       case 'w': state = 0; Match = true; break;
                       case 'q': state = 0; Match = true; break;
                       case 'h': state = 0; Match = true; break;
                       case 'D': state = 0; Match = true; break;
                       case 'b': state = 0; Match = true; break;
                       case 'a': state = 0; Match = true; break;
                       case 'U': state = 0; Match = true; break;
                       case 'e': state = 0; Match = true; break;
                       case 's': state = 0; Match = true; break;
                       case 't': state = 0; Match = true; break;
                       case '0': state = 0; Match = true; break;
                       case 'C': state = 0; Match = true; break;
                       case 'T': state = 0; Match = true; break;
                       case 'k': state = 0; Match = true; break;
                       case 'd': state = 0; Match = true; break;
                       case 'H': state = 0; Match = true; break;
                       case 'c': state = 0; Match = true; break;
                       case 'i': state = 0; Match = true; break;
                       case 'r': state = 0; Match = true; break;
                       case 'K': state = 0; Match = true; break;
                       case 'x': state = 0; Match = true; break;
                       case 'z': state = 0; Match = true; break;
                       case 'J': state = 0; Match = true; break;
                       case 'j': state = 0; Match = true; break;
                       case 'u': state = 0; Match = true; break;
                       case 'v': state = 0; Match = true; break;
                       case 'A': state = 0; Match = true; break;
                       case 'B': state = 0; Match = true; break;
                       case 'F': state = 0; Match = true; break;
                       case 'G': state = 0; Match = true; break;
                       case 'L': state = 0; Match = true; break;
                       case 'I': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case 'Y': state = 0; Match = true; break;
                       case 'W': state = 0; Match = true; break;
                       case 'S': state = 0; Match = true; break;
                       case 'R': state = 0; Match = true; break;
                       case 'Q': state = 0; Match = true; break;
                       case 'P': state = 0; Match = true; break;
                       case 'O': state = 0; Match = true; break;
                       case 'N': state = 0; Match = true; break;
                       case 'Z': state = 0; Match = true; break;
                       case 'M': state = 0; Match = true; break;
                       case 'o': state = 0; Match = true; break;
                       case 'm': state = 0; Match = true; break;
                       case 'l': state = 0; Match = true; break;
                       case 'g': state = 0; Match = true; break;
                       case 'p': state = 0; Match = true; break;
                       case 'f': state = 0; Match = true; break;
                       case 'y': state = 0; Match = true; break;
                       case 'n': state = 0; Match = true; break;
                       case 'X': state = 0; Match = true; break;
                       case 'V': state = 0; Match = true; break;
                       case 'E': state = 0; Match = true; break;
                       case '_': state = 0; Match = true; break;
                       case 'w': state = 0; Match = true; break;
                       case 'q': state = 0; Match = true; break;
                       case 'h': state = 0; Match = true; break;
                       case 'D': state = 0; Match = true; break;
                       case 'b': state = 0; Match = true; break;
                       case 'a': state = 0; Match = true; break;
                       case 'U': state = 0; Match = true; break;
                       case 'e': state = 0; Match = true; break;
                       case 's': state = 0; Match = true; break;
                       case 't': state = 0; Match = true; break;
                       case 'C': state = 0; Match = true; break;
                       case 'T': state = 0; Match = true; break;
                       case 'k': state = 0; Match = true; break;
                       case 'd': state = 0; Match = true; break;
                       case 'H': state = 0; Match = true; break;
                       case 'c': state = 0; Match = true; break;
                       case 'i': state = 0; Match = true; break;
                       case 'r': state = 0; Match = true; break;
                       case 'K': state = 0; Match = true; break;
                       case 'x': state = 0; Match = true; break;
                       case 'z': state = 0; Match = true; break;
                       case 'J': state = 0; Match = true; break;
                       case 'j': state = 0; Match = true; break;
                       case 'u': state = 0; Match = true; break;
                       case 'v': state = 0; Match = true; break;
                       case 'A': state = 0; Match = true; break;
                       case 'B': state = 0; Match = true; break;
                       case 'F': state = 0; Match = true; break;
                       case 'G': state = 0; Match = true; break;
                       case 'L': state = 0; Match = true; break;
                       case 'I': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _comma-op
int check__comma_op(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case ',': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _relop
int check__relop(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                       case '=': state = 3; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case '>': state = 0; Match = true; break;
                       case '<': state = 0; Match = true; break;
                       case '!': state = 2; Match = true; break;
                       case '=': state = 2; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 2:
                switch(ch) {
                       case '=': state = 3; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 3:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
if ( state == 3){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _assign-op
int check__assign_op(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case '=': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _addop
int check__addop(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case '-': state = 0; Match = true; break;
                       case '+': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _left-squarebracket
int check__left_squarebracket(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case '[': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _NUM
int check__NUM(const string& input, int start) {
    int state = 3;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                       case '7': state = 0; Match = true; break;
                       case '6': state = 0; Match = true; break;
                       case '8': state = 0; Match = true; break;
                       case '5': state = 0; Match = true; break;
                       case '0': state = 0; Match = true; break;
                       case '9': state = 0; Match = true; break;
                       case '4': state = 0; Match = true; break;
                       case '.': state = 1; Match = true; break;
                       case '1': state = 0; Match = true; break;
                       case '2': state = 0; Match = true; break;
                       case '3': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case '7': state = 2; Match = true; break;
                       case '6': state = 2; Match = true; break;
                       case '8': state = 2; Match = true; break;
                       case '5': state = 2; Match = true; break;
                       case '0': state = 2; Match = true; break;
                       case '9': state = 2; Match = true; break;
                       case '4': state = 2; Match = true; break;
                       case '1': state = 2; Match = true; break;
                       case '2': state = 2; Match = true; break;
                       case '3': state = 2; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 2:
                switch(ch) {
                       case '7': state = 2; Match = true; break;
                       case '6': state = 2; Match = true; break;
                       case '8': state = 2; Match = true; break;
                       case '5': state = 2; Match = true; break;
                       case '0': state = 2; Match = true; break;
                       case '9': state = 2; Match = true; break;
                       case '4': state = 2; Match = true; break;
                       case '1': state = 2; Match = true; break;
                       case '2': state = 2; Match = true; break;
                       case '3': state = 2; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 3:
                switch(ch) {
                       case '7': state = 0; Match = true; break;
                       case '6': state = 0; Match = true; break;
                       case '8': state = 0; Match = true; break;
                       case '5': state = 0; Match = true; break;
                       case '0': state = 0; Match = true; break;
                       case '9': state = 0; Match = true; break;
                       case '4': state = 0; Match = true; break;
                       case '1': state = 0; Match = true; break;
                       case '2': state = 0; Match = true; break;
                       case '3': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
if ( state == 2){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _left-roundbracket
int check__left_roundbracket(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case '(': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _divide-op
int check__divide_op(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case ';': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _right-curlybrace
int check__right_curlybrace(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case '}': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _right-roundbracket
int check__right_roundbracket(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case ')': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _mulop
int check__mulop(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case '^': state = 0; Match = true; break;
                       case '%': state = 0; Match = true; break;
                       case '*': state = 0; Match = true; break;
                       case '/': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _right-squarebracket
int check__right_squarebracket(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case ']': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _left-curlybrace
int check__left_curlybrace(const string& input, int start) {
    int state = 1;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case '{': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

// DFA 识别函数: _keyword
int check__keyword(const string& input, int start) {
    int state = 2;
    int pos = start;
    bool isErr = false;
    while (pos < input.size() && !isErr) {
        bool Match = false;
        char ch = input[pos];
        switch(state) {
            case 0:
                switch(ch) {
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 1:
                switch(ch) {
                       case 'h': state = 19; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 2:
                switch(ch) {
                       case 'w': state = 1; Match = true; break;
                       case 'd': state = 9; Match = true; break;
                       case 'v': state = 10; Match = true; break;
                       case 'r': state = 15; Match = true; break;
                       case 'e': state = 18; Match = true; break;
                       case 'i': state = 20; Match = true; break;
                       case 'f': state = 14; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 3:
                switch(ch) {
                       case 'd': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 4:
                switch(ch) {
                       case 'r': state = 22; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 5:
                switch(ch) {
                       case 'a': state = 13; Match = true; break;
                       case 't': state = 12; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 6:
                switch(ch) {
                       case 'o': state = 7; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 7:
                switch(ch) {
                       case 'a': state = 8; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 8:
                switch(ch) {
                       case 't': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 9:
                switch(ch) {
                       case 'o': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 10:
                switch(ch) {
                       case 'o': state = 21; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 11:
                switch(ch) {
                       case 'l': state = 17; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 12:
                switch(ch) {
                       case 'u': state = 4; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 13:
                switch(ch) {
                       case 'l': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 14:
                switch(ch) {
                       case 'l': state = 6; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 15:
                switch(ch) {
                       case 'e': state = 5; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 16:
                switch(ch) {
                       case 's': state = 17; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 17:
                switch(ch) {
                       case 'e': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 18:
                switch(ch) {
                       case 'l': state = 16; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 19:
                switch(ch) {
                       case 'i': state = 11; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 20:
                switch(ch) {
                       case 'f': state = 0; Match = true; break;
                       case 'n': state = 8; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 21:
                switch(ch) {
                       case 'i': state = 3; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            case 22:
                switch(ch) {
                       case 'n': state = 0; Match = true; break;
                }
                if(!Match) {
                   isErr=true;
                   break;                }
                pos++;
                break;
            default: 
                    isErr = true;
                    
break;
        }
    }
if ( state == 0){
   return pos - 1;
}
    return -1;
}

int check__annotation(const string& input, int start) {
    int pos = start;
    if (pos >= input.size()) return -1;
    // Minic-style: //...
    if (input[pos] == '/' && pos + 1 < input.size() && input[pos + 1] == '/') {
        pos += 2;
        while (pos < input.size() && input[pos] != '\n') {
            pos++;
        }
        return pos - 1; // 返回最后一个字符位置（不包括换行）
    }
    return -1;
}

void lexer(const string& input) {
    int pos = 0;
    while (pos < input.size()) {
        int maxLen = -1;
        string tokenName = "";
        {
            int len = check__annotation(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "annotation";
            }
        }
        {
            int len = check__keyword(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "keyword";
            }
        }
        {
            int len = check__ID(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "ID";
            }
        }
        {
            int len = check__comma_op(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "comma-op";
            }
        }
        {
            int len = check__relop(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "relop";
            }
        }
        {
            int len = check__assign_op(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "assign-op";
            }
        }
        {
            int len = check__addop(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "addop";
            }
        }
        {
            int len = check__left_squarebracket(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "left-squarebracket";
            }
        }
        {
            int len = check__NUM(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "NUM";
            }
        }
        {
            int len = check__left_roundbracket(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "left-roundbracket";
            }
        }
        {
            int len = check__divide_op(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "divide-op";
            }
        }
        {
            int len = check__right_curlybrace(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "right-curlybrace";
            }
        }
        {
            int len = check__right_roundbracket(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "right-roundbracket";
            }
        }
        {
            int len = check__mulop(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "mulop";
            }
        }
        {
            int len = check__right_squarebracket(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "right-squarebracket";
            }
        }
        {
            int len = check__left_curlybrace(input, pos);
            if (len > maxLen) {
                maxLen = len;
                tokenName = "left-curlybrace";
            }
        }
        if (maxLen == -1) {
            pos++;
            continue;
        }
        string matched = input.substr(pos, maxLen - pos + 1);
        int code = -1;
        if (tokenName != "annotation") {
            if (tokenName == "ID") code = 200;
            if (tokenName == "NUM") code = 100;
            if (tokenName == "addop") code = 700;
            if (tokenName == "annotation") code = 700;
            if (tokenName == "assign-op") code = 900;
            if (tokenName == "comma-op") code = 1100;
            if (tokenName == "divide-op") code = 1000;
            if (tokenName == "keyword") code = 300;
            if (tokenName == "left-curlybrace") code = 10;
            if (tokenName == "left-roundbracket") code = 50;
            if (tokenName == "left-squarebracket") code = 30;
            if (tokenName == "mulop") code = 800;
            if (tokenName == "relop") code = 600;
            if (tokenName == "right-curlybrace") code = 20;
            if (tokenName == "right-roundbracket") code = 60;
            if (tokenName == "right-squarebracket") code = 40;
            tokens.push_back({code, matched});
        }
        pos = maxLen + 1;
    }
}

int main() {
    string filepath;
    cout << "请输入源文件路径: ";
    cin >> filepath;
    ifstream file(filepath);
    if (!file) {
        cerr << "无法打开源文件！" << endl;
        return 1;
    }
    string suffix;
    cout << "请输入输出文件后缀（如 .lex）: ";
    cin >> suffix;
    string line, input;
    while (getline(file, line)) input += line + '\n';
    file.close();
    lexer(input);
    size_t dotPos = filepath.find_last_of('.');
    string baseName = (dotPos == string::npos) ? filepath : filepath.substr(0, dotPos);
    string outpath = baseName + suffix;
    ofstream outfile(outpath);
    if (!outfile) {
        cerr << "无法创建输出文件！" << endl;
        return 1;
    }
    for (const auto& token : tokens) {
        outfile << token.code << " " << token.value <<" ";     }
    outfile.close();
    cout << "词法分析完成，结果保存在：" << outpath << endl;
    return 0;
}
