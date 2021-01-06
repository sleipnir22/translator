#pragma once

#include <stack>
#include "Lexer.h"
#include "OPS.h"
#include "Token.h"
#include "ENUMS.h"


enum STATE
{
    TERM = -1,
    A = 0,
    S = 1,
    U = 2,
    T = 3,
    V = 4,
    F = 5,
};

enum TOKEN_IND
{

};

enum STACK_ITEM_T 
{
    TERM_T,
    STATE_T
};


class stack_item : public Token
{
    STATE state = TERM;
    STACK_ITEM_T stack_item_type;
public:
    stack_item(std::string word, TOKEN_T token_type)
        : Token(word,token_type), stack_item_type(TERM_T) {}

    stack_item(TOKEN_T token_type)
        : Token("\0", token_type), stack_item_type(STACK_ITEM_T::TERM_T) {}

    stack_item(STATE state) 
        : state(state), stack_item_type(STACK_ITEM_T::STATE_T) {}

    STACK_ITEM_T get_stack_item_type() const { return stack_item_type; }
    STATE get_state() const { return state; }
};


class Parser {

    typedef void (Parser::* functionalArray)();
    static const functionalArray funcArr[15];
    static const int M[6][10];

    Token token;
    std::string token_word;
    TOKEN_T token_type;

    std::stack<stack_item*> stack1, stack2;

    Lexer lex;
    OPS cur_ops;

    int i;
    stack_item* st_item;
    Token get_token();
    void step(STACK_ITEM_T, TOKEN_T);
    void show_error(std::string);
    void reset_parser();
    void f1(), f2(), f3(), f4(), f5(), f6(), f7(), f8(), f9(), f10(), f11(), f12(), f13(), f14(), f15();
public:
    STATE cur_state;                                                    // Текущее состояние
    Parser(Lexer l);
    OPS make_ops();
};