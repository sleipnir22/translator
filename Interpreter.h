#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "OPS.h"
#include "ENUMS.h"
#include <map>

class Interpreter {
    int sum = 0;
    size_t pos = 0;
    std::map<std::string, int> vars;
    std::map<std::string, std::vector<int>> arrs;
    std::vector<OPSItem> items;
    std::stack<OPSItem> st;

    void SUB(OPSItem), MUL(OPSItem), DIV(OPSItem), LOAD(OPSItem), ST(OPSItem &), ADD(OPSItem);
    void OP(OPSItem, OPERATION_T operation);
    void push_item(OPSItem&, std::stack<OPSItem>&);
    void execute_command(OPSItem&, OPSItem&, std::stack<OPSItem>&, OPSItem& item);
    void step(std::stack<OPSItem>&, OPSItem&);
    bool k_zero = true, a_zero = true, b_zero = true;
    OPSItem* k = nullptr;
    void next();
    void do_arithm(OPSItem& a, OPSItem&b, OPERATION_T operation, std::stack<OPSItem>& stack);
    void do_assign(OPSItem& a, OPSItem&b, OPERATION_T operation, std::stack<OPSItem>& stack);

public:
    void generate_commands();                      //заполняет стек до оператора
    Interpreter(OPS ops)
        : items(ops.items), vars(ops.vars), arrs(ops.arr){};

    void show_variables();
    //void generate_commands();
};

