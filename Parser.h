#pragma once
#include <stack>
#include "Lexer.h"
#include "OPS.h"
using namespace std;

class Parser
{

    typedef void (Parser::* functionalArray)();
    static const functionalArray funcArr[12];
    static const int M[6][10];
    static const char nterm[6];
    static const int term[10];
    Token token;
    stack<char> stack1, stack2; // string!!!
    string token_word;
    int token_type;
    Lexer lex;

    int i;
    vector<Token> p_ops_tokens;
    char sch;


    int get_t_index(int);                   //функция, которая находит номер терминала в массиве терминалов
    int get_nt_index(char);                 //та же функция, но для нетерминалов
    void reset_parser();
    bool push_ops();
    bool compare_stacks();
    template <class T> void clear_stack(stack<T>);
    void show_error(string error);
    void f1(), f2(), f3(), f4(), f5(), f6(), f7(), f8(), f9(), f10(), f11(), f12();
public:
    Parser(Lexer l);
    OPS make_ops();

};
