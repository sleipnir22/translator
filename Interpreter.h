#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "OPS.h"
#include <map>
using namespace std;

class Interpreter
{
	typedef void (Interpreter::* gf)(int);
	static const gf funcArr[4];
	static const string opArr[5];
	double sum;
	int a, b, k, t;
	int i;
	OPS ops;
	stack<Token> st;
	map<int, string> variables;
	void SUB(int), MUL(int), DIV(int), LOAD(int), ST(int&), ADD(int);
    void push_token(Token);
    void fill_stack();                      //заполняет стек до оператора
    bool is_operator(string);               //проверка на то, является ли входной токен из опс оператором
    int get_function_number();
public:
	Interpreter(OPS);
    void generate_commands();
};

