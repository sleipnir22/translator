
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "ENUMS.h"


class Token {
    TOKEN_T type;
    std::string word;
public:
    int col = -1, row = -1;

    Token();

    Token(std::string word, TOKEN_T type);

    Token(std::string word, TOKEN_T type, int col, int row);

    Token &operator=(const Token &);

    void get_info() const;

    std::string get_word() const;

    TOKEN_T get_type() const;
};



