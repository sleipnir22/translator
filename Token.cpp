#include "Token.h"
#include "ENUMS.h"
Token::Token() {
    this->type = -1;
    this->word = "\0";
}

Token::Token(string word, int type) {
    this->word = word;
    this->type = type;
    if ((this->type == MUL_T)  || (this->type == DIV_T) || (this->type == PLUS_T) || (this->type == MINUS_T) || (this->type == EQUALS_T))
        {is_operator = true;}
}

void Token::get_info() const {
    cout << word << " ";
}

string Token::get_word() const {
    return this->word;
}

int Token::get_type() const {
    return this->type;
}

bool Token::is_op() {
    return is_operator;
}

bool operator<(const Token& left, const Token& right)
{
    return left.get_type() < right.get_type();
}

Token& Token::operator=(const Token& other)
{
    this->type = other.type;
    this->word = other.word;
    return *this;
}