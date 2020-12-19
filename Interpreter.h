#pragma once
#include <stack>
#include "Token.h"
#include "OPS.h"
#include <map>
using namespace std;

class Interpreter
{
	typedef void (Interpreter::* gf)(string);
	static gf funcArr[6];
	static const char opArr[5];
	map<string, int> varMap;
	double sum;
	string a, b,t;
	int k = 0;
	bool k_zero = true;
	bool a_zero = true;
	bool b_zero = true;

	int i;
	OPS ops;
	stack<Token> com_stack;
	stack<Token> inter_stack;
	void push_token();
	void fill_com_stack();
	void set_mem_var();
	int  get_op_index(int);
	void ADD(string), SUB(string), MUL(string), DIV(string), Load(string), St(string);
	int fill_until_op();
	void com(int);
	void op_exe(int,string);
	void load_two_top();
public:
	void get_commands(OPS);
};

