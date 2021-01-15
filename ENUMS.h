
#pragma once


enum class TOKEN_T {        //27
    EMPTY_T = -2,
    ERROR_T = -1,
    NAME_T = 0,             // name
    INT_T = 1,              // int
    NEWINT_T = 2,           // new int
    NEWARRAY_T = 3,         // new array
    READ_T = 4,            //"read"
    WRITE_T = 5,           //"write"
    L_BRACE_T = 6,          //"{"
    R_BRACE_T = 7,         //"}"
    L_SQUARE_T = 8,        //"["
    R_SQUARE_T = 9,        //"]"
    COMMA_T = 10,            //","
    ASSIGN_T = 11,          //"="
    LESS_T = 12,            //"<"
    GREATER_T = 13,         //">"
    LOREQUAL_T = 14,        //"<="
    GOREQUAL_T = 15,        //">="
    EQUAL_T = 16,           //"=="
    NOTEQUAL_T = 17,        //"!="
    IF_T = 18,              //"if"
    ELSE_T = 19,            //"else"
    WHILE_T = 20,           //"while"
    PLUS_T = 21,             //"+"
    MINUS_T = 22,            //"-"
    MUL_T = 23,              //"*"
    DIV_T = 24,              //"/"
    L_PR_T = 25,             //"("
    R_PR_T = 26,             //")"
    END_T = 27,              //";"
    FLOAT_T = 28,           //double
    NEWFLOAT_T = 29         //new double
};
