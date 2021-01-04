
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "ENUMS.h"


class Token {
    TOKEN_T type;
    TOKEN_T_M token_M_ind;
    std::string word;
    int col = -1, row = -1;
public:
    Token();
    Token(std::string word, TOKEN_T type);
    Token(std::string word, TOKEN_T type, TOKEN_T_M M_type);
    Token(std::string word, TOKEN_T type, TOKEN_T_M M_type, int col, int row);
    Token& operator=(const Token&);
    void get_info() const;
    std::string get_word() const;
    TOKEN_T get_type() const;
    int get_M_ind() const;
};



