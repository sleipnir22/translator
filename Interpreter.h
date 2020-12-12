#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "Token.h"
#include "OPS.h"
using namespace std;

class Interpreter
{
	typedef void (Interpreter::* gf)();
	static const gf funcArr[6];
	static const char opArr[5];
	double sum;
	int a, b, k, t;
	int i;
	OPS ops;
	stack<Token> stack;
	vector<int> commands;
public:
	void f1(), f2(), f3(), f4(), f5(), f6();
	void get_commands(OPS);
	void push_token();
	void fill_iter_stack();
};

