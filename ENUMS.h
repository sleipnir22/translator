
#pragma once

enum TOKEN_T {
    EMPTY_T = -2,
    ERROR_T = -1,
    END_T = 0,      //";"
    NAME_T = 1,     //variable
    INT_T = 2,      //const integer
    STR_T = 3,      //string
    EQUALS_T = 61,  //"="
    L_PR_T = 40,    //"("
    R_PR_T = 41,    //")"
    MUL_T = 42,     //"*"
    PLUS_T = 43,    //"+"
    MINUS_T = 45,   //"-"
    DIV_T = 47,     //"/"
};

enum class TOKEN_T_M {
    EMPTY_T = -2,
    ERROR_T = -1,
    PLUS_T = 0,    //"+"
    MINUS_T = 1,   //"-"
    MUL_T = 2,     //"*"
    DIV_T = 3,     //"/"
    L_PR_T = 4,    //"("
    R_PR_T = 5,    //")"
    NAME_T = 6,     //variable
    INT_T = 7,      //const integer
    EQUALS_T = 8,  //"="
    END_T = 9,      //";"
    //STR_T = 10,      //string
};
