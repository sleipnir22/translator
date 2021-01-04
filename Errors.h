#pragma once
#include <exception>

class SyntaxError : public std::exception
{
    std::string error;
    int col, row;
    SyntaxError(int col, int row, Token expectedToken)
        : col(col), row(row), error("Syntax error! Expected ") {}


    std::string what() const override {
        return error;
    }
};


class IllegalCharacter : public std::exception
{

};

class RuntimeError : public std::exception
{

};