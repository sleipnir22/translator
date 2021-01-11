#pragma once

#include <exception>
#include <string>
#include <iostream>
#include "Token.h"

class Error {
protected:
    int col = -1, row = -1;
    Token t;
public:
    Error(int col, int row, Token t)
            : col(t.col), row(t.row), t(t) {}

    virtual std::string what() const = 0;
};

class SyntaxError : public Error {
    const char *error;
public:
    SyntaxError(int col, int row, Token t) : Error(col, row, t), error("Syntax Error! (") {};

    std::string what() const override {
        return std::string(error) + std::to_string(row) + (",") + std::to_string(col) + (")");
    }
};

class IllegalCharacter : public Error {
    const char *error;
public:
    IllegalCharacter(int col, int row, Token t) : Error(col, row, t), error("Illegal character! (") {};

    std::string what() const override {
        return std::string(error) + std::to_string(row) + (",") + std::to_string(col) + (")");
    }
};

class RuntimeError : public Error {
    std::string error;
public:
    RuntimeError(int col, int row, Token t) : Error(col, row, t), error("Runtime Error (") {}

    std::string what() const override {
        return std::string(error) + std::to_string(row) + (",") + std::to_string(col) + (")");
    }
};

class DeclarationError : public Error {
    std::string error;
public:
    DeclarationError(int col, int row, Token t) : Error(col, row, t), error("Declaration Error! ") {};

    std::string what() const override {
        return std::string(error) + std::string(t.get_word()) + std::string(" was already declared!") + (" (") +std::to_string(row) + (",") + std::to_string(col) + (")");
    }
};