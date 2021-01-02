// translator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
int main() {
    setlocale(LC_ALL, "Russian");
    ifstream f;
    string path = "D:\\Clionprojects\\text.txt";
    f.open(path);
    string text;
    cout << text;
    if (!f.is_open()) {
        cout << "Vive la France!" << endl;
    } else {
        char ch;
        while (f.get(ch)) {
            text.push_back(ch);
        }
    }

    Lexer lexer(text);
    Parser *parser = new Parser(lexer);
    auto ops = parser->make_ops();

    cout << endl;

    for (int i = 0; i < ops.ops_tokens.size(); i++) {
        ops.ops_tokens[i].get_info();;
    }
    cout << endl;

    for (int i = 0; i < ops.ops_varArr.size(); i++) {
        ops.ops_varArr[i].get_info();
    }

    Interpreter* interpreter = new Interpreter(ops);
    interpreter->generate_commands();
    interpreter->show_variables();
    return 0;
}