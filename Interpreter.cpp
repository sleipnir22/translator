#include "Interpreter.h"

#define g Interpreter

void g::next() {
    pos++;
}

void g::show_variables() {
    std::cout << std::endl;
    for (auto& var : vars )
    {
        std::cout << var.first << " : " << var.second << std::endl;
    }
}

void g::push_item(OPSItem& item, std::stack<OPSItem>& stack) {
    stack.push(item);
}


//стек заполняем до тех пор, пока не встретится оператор
void g::generate_commands() {
    for(auto& item : items) {
        step(st, item);
    }
}

void g::step(std::stack<OPSItem>& stack, OPSItem& item)
{
    if (item.type != ITEM_TYPE::OPERATOR) {
        push_item(item, stack);
    } else if (!stack.empty()) {
        auto& b = stack.top();
        stack.pop();
        auto& a = stack.top();
        a_zero = a.value == 0;
        b_zero = b.value == 0;

        execute_command(a,b, stack, item);
    }
}


void g::execute_command(OPSItem& a, OPSItem& b, std::stack<OPSItem>& stack, OPSItem& item) {
    auto operation = item.operation;
    switch (operation) {
        case OPERATION_T::DIV_T:
        case OPERATION_T::PLUS_T:
        case OPERATION_T::MINUS_T:
        case OPERATION_T::MUL_T:
            do_arithm(a,b,operation,stack);
            break;
        case OPERATION_T::ASSIGN_T:
            do_assign(a,b,stack);
            break;
    }
}

void g::do_arithm(OPSItem& a, OPSItem&b, OPERATION_T operation, std::stack<OPSItem>& stack){
    if (k_zero) {
        LOAD(a);
        OP(b, operation);
        stack.top().value = 0;
        k = &stack.top();
        k_zero = false;
    } else if (!k_zero && a_zero) {
        OP(b, operation);
        stack.top().value = 0;
        k = &stack.top();
        k_zero = false;
    } else if (!k_zero && b_zero) {
        if (operation == OPERATION_T::PLUS_T || operation == OPERATION_T::MUL_T) {
            LOAD(a);
            stack.top().value = 0;
            k = &stack.top();
            k_zero = false;
        } else if (operation == OPERATION_T::MINUS_T || operation == OPERATION_T::DIV_T) {
            OPSItem t(0, ITEM_TYPE::VARIABLE, TOKEN_T::NAME_T);
            ST(t);
            LOAD(a);
            OP(t, operation);
            stack.top().value = 0;
            k = &stack.top();
            k_zero = false;
        }
    } else if (!k_zero && !a_zero && !b_zero) {
        OPSItem t(0, ITEM_TYPE::VARIABLE, TOKEN_T::NAME_T);
        ST(t);
        LOAD(a);
        OP(b, operation);
        stack.top().value = 0;
        *k = t;
        k = &stack.top();
    }
}

void g::do_assign(OPSItem &a, OPSItem &b, std::stack<OPSItem> &stack) {
    if (k_zero) {
        LOAD(b);
        ST(a);
        a_zero = false;
    } else if (!k_zero && !b_zero) {
        OPSItem t(0, ITEM_TYPE::VARIABLE, TOKEN_T::NAME_T);
        ST(t);
        LOAD(b);
        ST(a);
        *k = t;
    } else if (!k_zero && b_zero) {
        ST(a);
        k = nullptr;
        k_zero = true;
    }
}

void g::OP(OPSItem operand, OPERATION_T operation) {
    switch(operation){
        case OPERATION_T::PLUS_T:
            ADD(operand);
            break;
        case OPERATION_T::MINUS_T:
            SUB(operand);
            break;
        case OPERATION_T::DIV_T:
            DIV(operand);
            break;
        case OPERATION_T::MUL_T:
            MUL(operand);
            break;
    }
}

void g::ADD(OPSItem item) {
    if (item.type == ITEM_TYPE::CONST)
        sum += item.value;
    else sum += vars[item.word];
}

void g::SUB(OPSItem item) {
    if (item.type == ITEM_TYPE::CONST)
        sum -= item.value;
    else sum -= vars[item.word];
}

void g::DIV(OPSItem item) {
    try {
        if (item.value == 0)
            throw "Error! Division to 0"; //переписать обработчик ошибок
        if (item.type == ITEM_TYPE::CONST)
            sum /= item.value;
        else sum /= vars[item.word];
    }
    catch (std:: string& error) {
        std::cout << error << " ";
    }
}

void g::MUL(OPSItem item) {
    if (item.type == ITEM_TYPE::CONST)
        sum *= item.value;
    else sum *= vars[item.word];
}

void g::ST(OPSItem& item) {
    item.value = sum;
    //обработка ошибки
    vars[item.word] = sum;
}

void g::LOAD(OPSItem item) {
    if (item.type == ITEM_TYPE::CONST)
        sum = item.value;
    else sum = vars[item.word];
}