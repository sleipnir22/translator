
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "ENUMS.h"


class Token {
    MAIN_TYPE main_type;
    TOKEN_T type;
    std::string word;

public:
    int col = -1, row = -1;

    Token();

    Token(std::string word, TOKEN_T type, MAIN_TYPE main_type);

    Token(std::string word, TOKEN_T type, MAIN_TYPE main_type, int col, int row);

    Token& operator=(const Token&);

    void get_info() const;

    std::string get_word() const;

    TOKEN_T get_type() const;
    MAIN_TYPE get_main_type() const;
};



