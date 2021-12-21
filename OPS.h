#pragma once

#include <iostream>
#include "Token.h"
#include "ENUMS.h"
#include <map>



struct OPSItem {
    float value = -1.;
    VAL_T val_t = FLOAT;
    std::string word = "";
    int mark_pos;
    int index = -1;
    ITEM_TYPE type;
    TOKEN_T token_type;
    OPERATION_T operation = OPERATION_T::ERROR_T;
    OPSItem(float value, ITEM_TYPE type, TOKEN_T token_type)
        : value(value), type(type), token_type(token_type) {};
    OPSItem(float value, ITEM_TYPE type, TOKEN_T token_type, VAL_T val_t)
        : value(value), type(type), token_type(token_type), val_t(val_t) {};
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
        : type(ITEM_TYPE::EMPTY), word(word), mark_pos(mark_pos), operation(OPERATION_T::MARK_T) {};
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


    void set_value(float _value)
    {
        if (val_t == INT)
            value = (int)_value;
        else
            value = _value;
    }
    float get_value()
    {
        return value;
    }
};



struct OPS {
    std::vector<OPSItem> items;
    std::map<std::string, float> vars;
    std::map<std::string, std::vector<float>> arr;
    std::map<std::string, VAL_T> valts;
};
