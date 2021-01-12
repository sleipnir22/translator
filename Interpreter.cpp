#include "Interpreter.h"

#define g Interpreter

void g::show_variables() {
    std::cout << std::endl;
    for (auto& var : vars ) {
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
    if (item.type != ITEM_TYPE::FINAL) {
        if (item.type != ITEM_TYPE::OPERATOR) {
            push_item(item, stack);
        } else if ((item.operation == WRITE_T) || (item.operation == READ_T)) {
                auto &a = stack.top();
                stack.pop();
                execute_un_command(a, stack, item);
            } else {
                auto b = stack.top();
                stack.pop();
                auto &a = stack.top();
                //stack.pop();
                a_zero = (a.value == 0);
                b_zero = (b.value == 0);
                execute_bin_command(a, b, stack, item);
            }
        }
}

void Interpreter::execute_un_command(OPSItem &a, std::stack<OPSItem> & stack, OPSItem &item) {
    if (item.operation == OPERATION_T::WRITE_T) {
        auto item_val = a.value;
        if (a.type == ITEM_TYPE::CONST) {
            printf("\nOUTPUT: ");
            printf("%d", item_val);
        } else if (a.var != nullptr) {
            printf("\nOUTPUT: ");
            printf("%d",vars[a.word]);
        } else {
            printf("\nOUTPUT: ");
            printf("%d",sum);
        }
    } else if (item.operation == OPERATION_T::READ_T) {

    }
}

void g::execute_bin_command(OPSItem& a, OPSItem& b, std::stack<OPSItem>& stack, OPSItem& item) {
    auto operation = item.operation;
    if (operation == OPERATION_T::MUL_T || operation == OPERATION_T::PLUS_T
        || operation == OPERATION_T::DIV_T || operation == OPERATION_T::MINUS_T ) {
        do_arithm(a,b,operation,stack);
    } else if (operation == OPERATION_T::ASSIGN_T) {
        do_assign(a,b,stack);
    } else if (operation == OPERATION_T::BEGIN_T) {

    } else if (operation == OPERATION_T::DECLARE_ARR){
        auto size = items[pos - 1].value; //
        auto name = items[pos - 2].word;
        mem_alloc(arrs, size, name);
    } else if (operation == OPERATION_T::DECLARE_ARR) {

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
            OP(a, operation);
            stack.top().value = 0;
            k = &stack.top();
            k_zero = false;
        } else if (operation == OPERATION_T::MINUS_T || operation == OPERATION_T::DIV_T) {
            OPSItem t(0, ITEM_TYPE::CONST, TOKEN_T::INT_T);
            ST(t);
            LOAD(a);
            OP(t, operation);
            stack.top().value = 0;
            k = &stack.top();
            *k = t;
            k_zero = false;
        }
    } else if (!k_zero && !a_zero && !b_zero) {
        OPSItem t(0, ITEM_TYPE::CONST, TOKEN_T::INT_T);
        ST(t);
        LOAD(a);
        OP(b, operation);
        stack.top().value = 0;
        k = &stack.top();
        *k = t;
    }
}

void g::do_assign(OPSItem& a, OPSItem& b, std::stack<OPSItem>& stack) {
    if (k_zero) {
        LOAD(b);
        ST(a);
        a_zero = false;
    } else if (!k_zero && !b_zero) {
        OPSItem t(0, ITEM_TYPE::CONST, TOKEN_T::INT_T);
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
void g::mem_alloc(std::map<std::string, std::vector<int>> &arrs, int size, std::string name) {
    arrs.insert(std::make_pair(name, std::vector<int>(size)));
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
    item.var = &sum;
}

void g::LOAD(OPSItem item) {
    if (item.type == ITEM_TYPE::CONST)
        sum = item.value;
    else {
        sum = vars[item.word];
    }
}

