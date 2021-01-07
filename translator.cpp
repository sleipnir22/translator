// translator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Token.h"
#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "OPS.h"
int main() {
    setlocale(LC_ALL, "Russian");
    std::ifstream f;
    std::string path = "text.txt";
    f.open(path);
    std::string text;
    std::cout << text;
    if (!f.is_open()) {
        std::cout << "Vive la France!" << std::endl;
    }
    else {
        char ch;
        while (f.get(ch)) {
            text.push_back(ch); // not optimal!
        }
    }

    Lexer lexer(text);
    Parser* parser = new Parser(lexer);
    auto ops = parser->make_ops();

    ops;
    std::cout << std::endl;
    return 0;
}