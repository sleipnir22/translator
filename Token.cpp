#include "Token.h"
#include "ENUMS.h"

Token::Token() {
    this->type = TOKEN_T::EMPTY_T;
    this->token_M_ind = TOKEN_T_M::EMPTY_T;
    this->word = "\0";
}

Token::Token(std::string word, TOKEN_T type) {
    this->word = word;
    this->type = type;
    this->token_M_ind = (TOKEN_T_M) type;
}

Token::Token(std::string word, TOKEN_T type, TOKEN_T_M M_type) {
    this->word = word;
    this->type = type;
    this->token_M_ind = M_type;
}

Token::Token(std::string word, TOKEN_T type, TOKEN_T_M M_type, int col, int row) : word(word) , type(type) , token_M_ind(M_type) ,col(col), row(row) {}

void Token::get_info() const {
    std::cout << word << " ";
}

std::string Token::get_word() const {
    return this->word;
}

TOKEN_T Token::get_type() const {
    return this->type;
}
int Token::get_M_ind() const
{
    return (int) this->token_M_ind;
}

bool operator<(const Token& left, const Token& right)
{
    return left.get_type() < right.get_type();
}

Token& Token::operator=(const Token& other)
{
    this->type = other.type;
    this->word = other.word;
    this->token_M_ind = other.token_M_ind;
    this->row = other.row;
    this->col = other.col;
    return *this;
}