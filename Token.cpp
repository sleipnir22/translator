#include "Token.h"

Token::Token()
{
	
}

Token::Token(string word, int type)
{
	this->word = word;
	this->type = type;
}



void Token::get_info()
{
	cout << "(Type: " << type << "; Value: " << word << ")\n";
}

string Token::get_word()
{
	return this->word;
}

int Token::get_type()
{
	return this->type;
}
