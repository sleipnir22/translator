#include "Token.h"
Token::Token(string word, int type)
{
	this->word = word;
	this->type = type;
}



void Token::get_info()
{
<<<<<<< Updated upstream
	cout << "(��� �������: " << type << "; �������: " << word <<")\n";
=======
	cout << word << " ";
>>>>>>> Stashed changes
}

string Token::get_word()
{
    return this->word;
}

int Token::get_type()
{
    return this->type;
}
