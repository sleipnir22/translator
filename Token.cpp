#include "Token.h"
#include "ENUMS.h"

Token::Token() {
    this->type = TOKEN_T::EMPTY_T;
    this->word = "\0";
}

Token::Token(std::string word, TOKEN_T type, MAIN_TYPE main_type) {
    this->word = word;
    this->type = type;
    this->main_type = main_type;
}

Token::Token(std::string word, TOKEN_T type, MAIN_TYPE main_type, int col, int row) :
    word(word), type(type), main_type(main_type), col(col), row(row) {}

void Token::get_info() const {
    std::cout << word << " ";
}

std::string Token::get_word() const {
    return this->word;
}

TOKEN_T Token::get_type() const {
    return this->type;
}

MAIN_TYPE Token::get_main_type() const {
    return this->main_type;
}

bool operator<(const Token& left, const Token& right) {
    return left.get_type() < right.get_type();
}

Token& Token::operator=(const Token& other) {
    this->main_type = other.main_type;
    this->type = other.type;
    this->word = other.word;
    this->row = other.row;
    this->col = other.col;
    return *this;
}