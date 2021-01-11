// translator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Token.h"
#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "OPS.h"
#include <chrono>
int func(int a);
int main() {
    setlocale(LC_ALL, "Russian");
    std::ifstream f;
    std::string path = "D:\\Clionprojects\\text.txt";
    f.open(path);
    std::string text;
    std::cout << text;
    if (!f.is_open()) {
        std::cout << "Vive la France!" << std::endl;
    } else {
        char ch;
        while (f.get(ch)) {
            text.push_back(ch); // not optimal!
        }
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    Lexer lexer(text);
    auto parser = new Parser(lexer);
    auto ops = parser->make_ops();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Program has been successfully compiled into OPS!. \nOPS:\n";
    for (const auto &item : ops.items) {
        if (item.type == ITEM_TYPE::CONST) {
            std::cout << item.value << " ";
        } else std::cout << item.word << " ";
    }

    std::cout << "\n" << "================================================================================";
    auto t3 = std::chrono::high_resolution_clock::now();

    auto interpreter = new Interpreter(ops);
    interpreter->generate_commands();

    auto t4 = std::chrono::high_resolution_clock::now();

    interpreter->show_variables();

    auto execution_duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
    auto compile_duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout <<"================================================================================\n";
    std::cout << "Compile time: " << compile_duration /1000. << " milliseconds\n";
    std::cout << "Execution time: " << execution_duration /1000. << " milliseconds\n";

//    auto t5 = std::chrono::high_resolution_clock::now();
//
//
//    auto t6 = std::chrono::high_resolution_clock::now();
//
//    auto cpp_duration = std::chrono::duration_cast<std::chrono::microseconds>(t6 - t5).count();
//    std::cout << "Actual CPP time: " << cpp_duration << " microseconds\n";
    return 0;
}
