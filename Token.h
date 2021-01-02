#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Token {
    int type;
    string word;
    bool is_operator = false;
public:
    Token(string word, int type);
    Token();
    void get_info() const;
    string get_word() const;
    int get_type() const;
    bool is_op();
    friend bool operator <(const Token& left, const Token& right);
    Token& operator = (const Token& other);
};

//template <typename T>
//struct variable {
//    bool is_init;
//    T value;
//    string name;
//};

//template <typename T>
//struct constant {
//    const T value;
//    string name;
//};