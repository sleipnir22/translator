﻿#include "Token.h"
#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <chrono>
int main() {
    setlocale(LC_ALL, "Russian");
    std::ifstream f;
    std::string path = "D:\\Clionprojects\\";

    std::string pth;
    std::cin >> pth;
    path += pth;

    f.open(path);
    std::string text;
    std::cout << text;
    if (!f.is_open()) {
        std::cout << "Cannot open the file!" << std::endl;
    } else {
        char ch;
        while (f.get(ch)) {
            text.push_back(ch);
        }
    }

    auto t1 = std::chrono::high_resolution_clock::now();

    Lexer lexer(text);
    auto parser = new Parser(lexer);
    auto ops = parser->make_ops();
    auto interpreter = new Interpreter(ops);

    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "\nProgram has been successfully compiled into OPS! \nOPS:\n";
    for (const auto &item : ops.items) {
        if (item.type == ITEM_TYPE::CONST) {
            std::cout << item.value << " ";
        } else std::cout << item.word << " ";
    }

    std::cout << "\n" << "================================================================================";
    auto t3 = std::chrono::high_resolution_clock::now();

    interpreter->generate_commands();

    auto t4 = std::chrono::high_resolution_clock::now();

    auto execution_duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
    auto compile_duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout <<"\n================================================================================\n";

//    std::cout << "variables: ";
//    interpreter->show_variables();
    std::cout << "Compile time: " << compile_duration /1000. << " milliseconds\n";
    std::cout << "Execution time: " << execution_duration /1000. << " milliseconds\n";


    std::cin.get();
    system("pause");
    return 0;
}
