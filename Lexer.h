
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Token.h"
#include "ENUMS.h"

class Lexer {
    typedef void (Lexer::* semf)(char);

    static const semf funcArr[19];
    static const std::string SW[];
    static const int M[8][10];
    static const char T[];
    static const int S[8][10];
    int j, s, k;
    int row = 1, col = 1, lex_col = 1;
    Token token;
    int pos = 0;
    int num = 0;
    float d = 0, x = 0;
    std::string st;
    TOKEN_T type;
    MAIN_TYPE main_type;
    std::string text;

    int check_sw();

    void make_token();

    bool empty = true;
    bool token_ready = false;
    std::vector<std::string> varArr;
public:
    void f1(char), f2(char), f3(char), f4(char), f5(char), f6(char), f7(char), f8(char), f9(char), f10(char), f11(
        char), f12(char), f13(char), f14(char), f15(char), f16(char), f17(char), f18(char), f19(char);

    Lexer();

    Lexer(std::string text);

    Token get_token();

    std::vector<std::string> get_varArr() { return varArr; };

    bool is_empty() { return empty; }
};