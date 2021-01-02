#pragma once

enum TOKEN_T {
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

