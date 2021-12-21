
#pragma once

enum class MAIN_TYPE {
    DEFAULT,
    COMPARE,
    VARIABLE,
    CONST,
    DECLARE,
    DECLAREARR
};

enum class ITEM_TYPE {
    OPERATOR,
    VARIABLE,
    CONST,
    ARRAY_EL,
    EMPTY,
    FINAL
};

enum class TOKEN_T {        //27
    DEFAULT_T = -3,
    EMPTY_T = -2,
    ERROR_T = -1,
    NAME_T = 0,             // name
    INT_T = 1,              // int
    NEWINT_T = 2,           // new int
    NEWINTARR_T = 3,         // new int array
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
    FLOAT_T = 28,           //float
    NEWFLOAT_T = 29,         //new float
    NEWFLOATARR_T = 30      //new float array
};




enum STATE {
    TERM = -1,
    P = 0,
    I = 1,
    M = 2,
    A = 3,
    N = 4,
    Q = 5,
    S = 6,
    H = 7,
    C = 8,
    D = 9,
    K = 10,
    E = 11,
    U = 12,
    T = 13,
    V = 14,
    F = 15,
    Z = 16,
};

enum STACK_ITEM_T {
    EMPTY_T,
    TERM_T,
    STATE_T
};


enum OPERATION_T
{
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


enum VAL_T
{
    INT,
    FLOAT
};