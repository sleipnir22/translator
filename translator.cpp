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
    ifstream f;
    std::string path = "text.txt";
    f.open(path);
    std::string text;
    cout << text;
    if (!f.is_open()) {
        cout << "Vive la France!" << endl;
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

    cout << endl;

    //Interpreter* interpreter = new Interpreter(ops);
    //interpreter->generate_commands();
    //interpreter->show_variables();
    return 0;
}