#pragma once
#include <iostream>
#include "Token.h"
#include <map>


enum ITEM_TYPE
{
    OPERATOR,
    VARIABLE,
    CONST
};

class OPSItem
{
    int value;
    string word;
    ITEM_TYPE type;
public:
    OPSItem(string word, ITEM_TYPE type)
        : word (word), type(type) {};
    OPSItem(int value, ITEM_TYPE type)
        : value (value), type(type) {};
};

struct OPS {
    vector<vector<OPSItem>> array;
    vector<OPSItem> variables;
    vector<OPSItem> items;
};

