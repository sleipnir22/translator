#include "Token.h"
Token::Token(string word, int type)
{
	this->word = word;
	this->type = type;
}

void Token::get_info()
{
	cout << "тип лексемы: " << type << " лексема: " << word << endl;
}