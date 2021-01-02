#pragma once
#include <iostream>
#include "Token.h"

struct OPS {
    vector<Token> ops_tokens;
    vector<Token> ops_varArr;
};

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
};



