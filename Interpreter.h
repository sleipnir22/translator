#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "OPS.h"
#include <map>
#include <algorithm>

using namespace std;

class Interpreter {
    int sum;
    Token a, b, t;                     
    Token* k;
    size_t i;
    OPS ops;
    stack<Token> st;
    map<Token, int> variables;

    void SUB(Token), MUL(Token), DIV(Token), LOAD(Token), ST(Token&), ADD(Token);
    void OP(Token);

    void push_token(Token);

    void fill_stack();                      
    void get_two_operands();                
    void execute_command();
    bool k_zero = true, a_zero = true, b_zero = true;
public:
    Interpreter(OPS);
    void show_variables();
    void generate_commands();
};