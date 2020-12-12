#pragma once
#include <stack>
#include <iostream>
#include "Token.h"
#include <vector>
#include <queue>
#include "lexer.h"
#include "OPS.h"
using namespace std;
class Parser
{

    typedef void (Parser::* functionalArray)();
    static const functionalArray funcArr[11];
    static const int M[5][9];
    static const char nterm[5];
    static const int term[9];
    Token token;
    stack<char> stack1, stack2;
    string token_word;
    int token_type;
    Lexer lex;

    int pos, i, cnt , x;
    vector<Token> p_ops_tokens;
    char sch;


    int get_t_index(int);                   //функция, которая находит номер терминала в массиве терминалов
    int get_nt_index(char);                 //та же функция, но для нетерминалов
    void reset_parser();
    bool push_ops();
    bool compare_stacks();
    template <class T> void clear_stack(stack<T>);
    void show_error(string error);
    void f1(), f2(), f3(), f4(), f5(), f6(), f7(), f8(), f9(), f10(), f11();
public:
    Parser(Lexer);
    OPS make_ops();               //делает ОПС

};
