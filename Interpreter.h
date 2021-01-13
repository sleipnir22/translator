#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "OPS.h"
#include "ENUMS.h"
#include <map>
#include "Errors.h"

class Interpreter {
    struct two_values { int lvalue, rvalue;};
    size_t pos = 0;
    std::map<std::string, int> vars;
    std::map<std::string, std::vector<int>> arrs;
    std::vector<OPSItem> items;
    std::stack<OPSItem> st;
    bool from_jump = false;
    OPSItem sum = OPSItem(0, ITEM_TYPE::CONST, TOKEN_T::INT_T);

    void mem_alloc(int, std::string);

    void push_item(OPSItem&, std::stack<OPSItem>&);
    void execute_bin_command(OPSItem,OPSItem, OPERATION_T operation);
    void execute_un_command(OPSItem, OPERATION_T operation);
    void step(std::stack<OPSItem>&, OPSItem);

    void do_arithm(OPSItem, OPSItem,OPERATION_T);
    void do_assign(OPSItem, OPSItem);
    void do_compare(OPSItem, OPSItem, OPERATION_T);
    std::tuple<int,int> get_values(OPSItem lvalue, OPSItem rvalue);

public:
    void generate_commands();                      //заполняет стек до оператора
    Interpreter(OPS ops)
        : items(ops.items), vars(ops.vars), arrs(ops.arr){};

    void show_variables();
    //void generate_commands();
};