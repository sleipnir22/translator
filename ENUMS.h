
#pragma once


enum class TOKEN_T {        //27
    EMPTY_T = -2,
    ERROR_T = -1,          
    PLUS_T = 0,             //"+"
    MINUS_T = 1,            //"-"
    MUL_T = 2,              //"*"
    DIV_T = 3,              //"/"
    L_PR_T = 4,             //"("
    R_PR_T = 5,             //")"
    NAME_T = 6,             // name
    INT_T = 7,              // int
    NEWINT_T = 8,           // new int
    NEWARRAY_T = 9,         // new array
    ASSIGN_T = 10,          //"="
    END_T = 11,             //";"
    L_BRACE_T= 12,          //"{"
    R_BRACE_T = 13,         //"}"
    L_SQUARE_T = 14,        //"["
    R_SQUARE_T = 15,        //"]"
    WHILE_T = 16,           //"while"
    IF_T = 17,              //"if"
    ELSE_T = 18,            //"else"
    READ_T = 19,            //"read"
    WRITE_T = 20,           //"write"
    GREATER_T = 21,         //">"
    LESS_T = 22,            //"<"
    LOREQUAL_T = 23,        //"<="
    GOREQUAL_T = 24,        //">="
    EQUAL_T = 25,           //"=="
    NOTEQUAL_T = 26,        //"!="
    COMMA_T = 27            //","
};
