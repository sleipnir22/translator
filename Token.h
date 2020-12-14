#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Token
{
	int type;
	string word;
public:
	Token(string word, int type);
	void get_info();
    string get_word();
    int get_type();
};

