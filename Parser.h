#pragma once
#include <stack>
#include <iostream>
#include "Token.h"
#include <vector>
#include <queue>
using namespace std;
class Parser
{

    typedef void (Parser::*functionalArray)();
    static const functionalArray funcArr[9];
    static const int M[5][6];
    static const char nterm[5];
    static const int term[6];
    vector<Token> tokens;
    stack<char> stack1,stack2;
    //stack<Token> st1;
    int pos = 0;


    int get_t_index(int);                   //функция, которая находит номер терминала в массиве терминалов
    int get_nt_index(char);                 //та же функция, но для нетерминалов
public:
    void f1(),f2(), f3(), f4(), f5(), f6(), f7(), f8(), f9();
    Parser(const vector<Token>&);
    vector<Token> make_ops();               //делает ОПС
    Token findFirstName();

};

