#pragma once

#include <iostream>
#include "Token.h"
#include "ENUMS.h"
#include <map>


enum ITEM_TYPE {
    OPERATOR,
    VARIABLE,
    CONST,
    ARRAY_EL,
    EMPTY,
    FINAL
};

enum OPERATION_T {
    BEGIN_T,
    END_T,
    MARK_T,
    DECLARE_ARR,
    READ_T,
    WRITE_T,
    ASSIGN_T,
    PLUS_T,
    MINUS_T,
    DIV_T,
    MUL_T,
    LESS_T,
    GREATER_T,
    EQUAL_T,
    LESS_OR_EQUAL_T,
    GREATER_OR_EQUAL_T,
    NOT_EQUAL_T,
    J_T,
    JF_T,
    I_T,
    ERROR_T
};


struct OPSItem {
    int value = -1;
    std::string word = "";
    int mark_pos;
    int index = -1;
    ITEM_TYPE type;
    TOKEN_T token_type;
    OPERATION_T operation = OPERATION_T::ERROR_T;

    OPSItem(int value, ITEM_TYPE type, TOKEN_T token_type)
            : value(value), type(type), token_type(token_type) {};
    OPSItem(std::string word, ITEM_TYPE type, TOKEN_T token_type)
            : word(word), type(type), token_type(token_type) {
        switch (token_type) {
            case TOKEN_T::EQUAL_T:
                operation = OPERATION_T::EQUAL_T;
                this->word = "==";
                break;
            case TOKEN_T::ASSIGN_T:
                operation = OPERATION_T::ASSIGN_T;
                this->word = "=";
                break;
            case TOKEN_T::DIV_T:
                operation = OPERATION_T::DIV_T;
                this->word = "/";
                break;
            case TOKEN_T::MINUS_T:
                operation = OPERATION_T::MINUS_T;
                this->word = "-";
                break;
            case TOKEN_T::MUL_T:
                operation = OPERATION_T::MUL_T;
                this->word = "*";
                break;
            case TOKEN_T::PLUS_T:
                operation = OPERATION_T::PLUS_T;
                this->word = "+";
                break;
            case TOKEN_T::GOREQUAL_T:
                operation = OPERATION_T::GREATER_OR_EQUAL_T;
                this->word = ">=";
                break;
            case TOKEN_T::LOREQUAL_T:
                operation = OPERATION_T::LESS_OR_EQUAL_T;
                this->word = "<=";
                break;
            case TOKEN_T::GREATER_T:
                this->word = ">";
                operation = OPERATION_T::GREATER_T;
                break;
            case TOKEN_T::LESS_T:
                operation = OPERATION_T::LESS_T;
                this->word = "<";
                break;
            case TOKEN_T::NOTEQUAL_T:
                operation = OPERATION_T::NOT_EQUAL_T;
                this->word = "!=";
                break;
        }
    };
    OPSItem(std::string word, OPERATION_T operation)
            : operation(operation), type(ITEM_TYPE::OPERATOR), word(word) {};
    OPSItem(std::string word = "", int mark_pos = -1)
            : type(ITEM_TYPE::EMPTY), word(word), mark_pos(mark_pos),operation(OPERATION_T::MARK_T) {};
    OPSItem(std::string word, ITEM_TYPE type, int index)
        : type(type), word(word), index(index) {};


    OPSItem& operator= (const OPSItem& other) {
        this->value = other.value;
        this->word = other.word;
        this->mark_pos = other.mark_pos;
        this->token_type = other.token_type;
        this->operation = other.operation;
        return *this;
    }
};



struct OPS {
    std::vector<OPSItem> items;
    std::map<std::string, int> vars;
    std::map<std::string, std::vector<int>> arr;
};
