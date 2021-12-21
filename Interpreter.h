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
    size_t pos = 0;
    std::map<std::string, float> vars;
    std::map<std::string, std::vector<float>> arrs;
    std::map<std::string, VAL_T> valts;
    std::vector<OPSItem> items;
    std::stack<OPSItem> st;
    bool from_jump = false;
    OPSItem sum = OPSItem(0, ITEM_TYPE::CONST, TOKEN_T::INT_T);

    void mem_alloc(int, std::string);

    void push_item(OPSItem&, std::stack<OPSItem>&);
    void execute_bin_command(OPSItem, OPSItem, OPERATION_T operation);
    void execute_un_command(OPSItem, OPERATION_T operation);
    void step(std::stack<OPSItem>&, OPSItem);

    void do_arithm(OPSItem, OPSItem, OPERATION_T);
    void do_assign(OPSItem, OPSItem);
    void do_compare(OPSItem, OPSItem, OPERATION_T);
    std::tuple<float, float> get_values(OPSItem lvalue, OPSItem rvalue);
    float get_value(OPSItem value, VAL_T valt);
    float get_value(float value, VAL_T valt);

public:
    void generate_commands();                      //заполняет стек до оператора
    Interpreter(OPS ops)
        : items(ops.items), vars(ops.vars), arrs(ops.arr), valts(ops.valts) {};

    void show_variables();
    //void generate_commands();
};