#pragma once

#include <stack>
#include "Lexer.h"
#include "OPS.h"
#include "Token.h"
#include "ENUMS.h"


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


class stack_item : public Token {

    STATE state = STATE::TERM;
    STACK_ITEM_T stack_item_type;
public:
    stack_item(std::string word, TOKEN_T token_type)
            : Token(word, token_type), stack_item_type(STACK_ITEM_T::TERM_T) {}

    stack_item(std::string word)
            : Token(word, TOKEN_T::EMPTY_T), stack_item_type(STACK_ITEM_T::TERM_T) {}

    stack_item(TOKEN_T token_type)
            : Token("\0", token_type), stack_item_type(STACK_ITEM_T::TERM_T) {}

    stack_item()
            : Token("\0", TOKEN_T::EMPTY_T), stack_item_type(STACK_ITEM_T::EMPTY_T) {}

    stack_item(TOKEN_T token_type, STACK_ITEM_T stack_item_type)
            : Token("\0", token_type), stack_item_type(stack_item_type) {}

    stack_item(STATE state)
            : state(state), stack_item_type(STACK_ITEM_T::STATE_T) {}

    STACK_ITEM_T get_stack_item_type() const { return stack_item_type; }

    STATE get_state() const { return state; }
};


class Parser {

    typedef void (Parser::* functionalArray)();

    static const functionalArray funcArr[46];
    static const int M[17][28];

    bool is_filling_vars;
    bool is_filling_arr;
    Token token;
    std::string token_word;
    TOKEN_T token_type;
    int k = 0;
    std::stack<stack_item *> stack1, stack2;
    std::stack<int> marks;
    Lexer lex;
    OPS cur_ops;

    Token get_token();

    void step(STACK_ITEM_T, STACK_ITEM_T);

    void reset_parser();

    bool is_semantic(std::stack<stack_item *> &stack2);

    void execute_semantic(std::vector<OPSItem> &ops_items, std::stack<stack_item *> &stack2);

    void count();

    void f1(), f2(), f3(), f4(), f5(), f6(), f7(), f8(), f9(), f10(), f11(), f12(), f13(), f14(), f15(),
            f16(), f17(), f18(), f19(), f20(), f21(), f22(), f23(), f24(), f25(), f26(), f27(), f28(), f29(), f30(),
            f31(), f32(), f33(), f34(), f35(), f36(), f37(), f38(), f39(), f40(), f41(), f42(), f43(), f44(), f45(), f46();

public:
    Parser(Lexer l);

    OPS make_ops();
};