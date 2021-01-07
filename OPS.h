#pragma once
#include <iostream>
#include "Token.h"
#include "ENUMS.h"
#include <map>


enum  ITEM_TYPE
{
    OPERATOR,
    VARIABLE,
    CONST
};


class OPSItem
{
    int value = -1;
    std::string word ="0";
    ITEM_TYPE type;
    TOKEN_T token_type;
public:
    OPSItem(int value, ITEM_TYPE type, TOKEN_T token_type)
        : value(value), type(type), token_type(token_type){};
    OPSItem(std::string word, ITEM_TYPE type, TOKEN_T token_type)
        : word(word), type(type), token_type(token_type){};
    OPSItem(ITEM_TYPE type, TOKEN_T token_type)
        : type(type), token_type(token_type) {};
};

struct OPS {
    std::vector<OPSItem> items;
    std::map<std::string,int> vars;
    std::map<std::string, std::vector<int>> arr;
};
