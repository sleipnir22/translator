#include "Token.h"
Token::Token(string word, int type)
{
	this->word = word;
	this->type = type;
}

void Token::get_info()
{
	cout << "��� �������: " << type << " �������: " << word << endl;
}