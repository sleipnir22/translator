#include "Interpreter.h"
#include <utility>
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

    while (pos < items.size()){
        step(st, items[pos]);
        if (!from_jump)
            pos++;
        from_jump = false;
    }
}

void g::step(std::stack<OPSItem>& stack, OPSItem item)
{
    if (item.type != ITEM_TYPE::FINAL) {
        if (item.type != ITEM_TYPE::OPERATOR) {
            push_item(item, stack);
        } else if (item.operation == WRITE_T || item.operation == READ_T
        || item.operation == J_T) {
                auto a = stack.top();
                stack.pop();
                execute_un_command(a, item.operation);
        } else if (item.operation == OPERATION_T::MARK_T)
            return;
        else if (item.operation == OPERATION_T::BEGIN_T || item.operation == OPERATION_T::END_T){
            return;
            } else {
                auto rvalue = stack.top();
                stack.pop();
                auto lvalue = stack.top();
                stack.pop();
                execute_bin_command(lvalue, rvalue, item.operation);
            }
        }
}

void Interpreter::execute_un_command(OPSItem lvalue, OPERATION_T operation) {
    switch(operation) {
        case OPERATION_T::WRITE_T:
            if (lvalue.type == ITEM_TYPE::CONST) {
                printf("\nOUTPUT: ");
                printf("%d", lvalue.value);
            } else if (lvalue.type == ITEM_TYPE::VARIABLE) {
                printf("\nOUTPUT: ");
                printf("%d", vars.at(lvalue.word));
            } else if (lvalue.type == ITEM_TYPE::ARRAY_EL) {
                printf("\nOUTPUT: ");
                printf("%d", arrs.at(lvalue.word)[lvalue.index]);
            }
            break;
        case OPERATION_T::READ_T:
            break;
        case OPERATION_T::J_T:
            from_jump = true;
            pos = lvalue.mark_pos;
            break;
    }
}

void g::execute_bin_command(OPSItem lvalue, OPSItem rvalue, OPERATION_T operation) {
    int index, size;
    std::string name;
    switch(operation) {
        case OPERATION_T::MUL_T:
        case OPERATION_T::PLUS_T:
        case OPERATION_T::DIV_T:
        case OPERATION_T::MINUS_T:
            do_arithm(lvalue, rvalue, operation);
            break;

        case OPERATION_T::ASSIGN_T:
            do_assign(lvalue, rvalue);
            break;

        case OPERATION_T::DECLARE_ARR:
            size = rvalue.value;
            name = lvalue.word;
            mem_alloc(size, name);
            break;

        case OPERATION_T::I_T:
            index = rvalue.value;
            st.push(OPSItem(lvalue.word, ITEM_TYPE::ARRAY_EL, index));
            break;

        case OPERATION_T::GREATER_T:
        case OPERATION_T::LESS_T:
        case OPERATION_T::GREATER_OR_EQUAL_T:
        case OPERATION_T::EQUAL_T:
        case OPERATION_T::NOT_EQUAL_T:
        case OPERATION_T::LESS_OR_EQUAL_T:
            do_compare(lvalue, rvalue, operation);
            break;
        case OPERATION_T::JF_T:
            if (lvalue.value == 0) {
                pos = rvalue.mark_pos;
                from_jump = true;
            }
        default:
            break;
    }
}

std::tuple<int,int> g::get_values(OPSItem lvalue, OPSItem rvalue) {
    int lval, rval;
    if (lvalue.type == ITEM_TYPE::CONST && rvalue.type == CONST) {
        lval = lvalue.value;
        rval = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == CONST) {
        lval = vars.at(lvalue.word);
        rval = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::CONST && rvalue.type == VARIABLE) {
        lval = lvalue.value;
        rval = vars.at(rvalue.word);
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == CONST) {
        lval = arrs.at(lvalue.word)[lvalue.index];
        rval = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == VARIABLE) {
        lval = arrs.at(lvalue.word)[lvalue.index];
        rval = vars.at(rvalue.word);
    } else if (lvalue.type == ITEM_TYPE::CONST && rvalue.type == ARRAY_EL) {
        lval = lvalue.value;
        rval = arrs.at(rvalue.word)[rvalue.index];
    } else if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == ARRAY_EL) {
        lval = vars.at(lvalue.word);
        rval = arrs.at(rvalue.word)[rvalue.index];
    }
    return { lval, rval };
}

void g::do_compare(OPSItem lvalue, OPSItem rvalue, OPERATION_T operation) {
    OPSItem sum(0, ITEM_TYPE::CONST, TOKEN_T::INT_T);
    st.push(sum);
    int lval, rval;
    auto values = get_values(lvalue, rvalue);
    lval = std::get<0>(values);
    rval = std::get<1>(values);
    switch(operation){
        case OPERATION_T::GREATER_T:
            st.top().value = lval > rval ? 1 : 0;
            break;
        case OPERATION_T::LESS_T:
            st.top().value = lval < rval ? 1 : 0;
            break;
        case OPERATION_T::GREATER_OR_EQUAL_T:
            st.top().value = lval >= rval ? 1 : 0;
            break;
        case OPERATION_T::EQUAL_T:
            st.top().value = lval == rval ? 1 : 0;
            break;
        case OPERATION_T::NOT_EQUAL_T:
            st.top().value = lval != rval ? 1 : 0;
            break;
        case OPERATION_T::LESS_OR_EQUAL_T:
            st.top().value = lval <= rval ? 1 : 0;
            break;
        default:
            break;
    }
}

void g::mem_alloc(int size, std::string name) {
    arrs.insert(std::pair<std::string,std::vector<int>>(name,size));
    for (int i = 0; i < size; i++) {
        arrs.at(name).push_back(0);
    }
}

void g::do_assign(OPSItem lvalue, OPSItem rvalue) {
    if ((lvalue.type == ITEM_TYPE::VARIABLE) && (rvalue.type == ITEM_TYPE::VARIABLE))
        vars.at(lvalue.word) = vars.at(rvalue.word);
    else if((lvalue.type == ITEM_TYPE::VARIABLE) && (rvalue.type == ITEM_TYPE::CONST)) {
        vars.at(lvalue.word) = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == ITEM_TYPE::CONST) {
        arrs.at(lvalue.word)[lvalue.index] = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == ITEM_TYPE::VARIABLE) {
        arrs.at(lvalue.word)[lvalue.index] = vars.at(rvalue.word);
    } else if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == ITEM_TYPE::ARRAY_EL) {
        vars.at(lvalue.word) = arrs.at(lvalue.word)[lvalue.index];
    }
}

void g::do_arithm(OPSItem lvalue, OPSItem rvalue, OPERATION_T operation) {
    OPSItem sum(0, ITEM_TYPE::CONST, TOKEN_T::INT_T);
    st.push(sum);
    int lval, rval;
    auto values = get_values(lvalue, rvalue);
    lval = std::get<0>(values);
    rval = std::get<1>(values);

    if (lvalue.type == ITEM_TYPE::CONST && rvalue.type == CONST) {
        lval = lvalue.value;
        rval = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == CONST) {
        lval = vars.at(lvalue.word);
        rval = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::CONST && rvalue.type == VARIABLE) {
        lval = lvalue.value;
        rval = vars.at(rvalue.word);
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == CONST) {
        lval = arrs.at(lvalue.word)[lvalue.index];
        rval = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == VARIABLE) {
        lval = arrs.at(lvalue.word)[lvalue.index];
        rval = vars.at(rvalue.word);
    } else if (lvalue.type == ITEM_TYPE::CONST && rvalue.type == ARRAY_EL) {
        lval = lvalue.value;
        rval = arrs.at(rvalue.word)[rvalue.index];
    } else if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == ARRAY_EL) {
        lval = vars.at(lvalue.word);
        rval = arrs.at(rvalue.word)[rvalue.index];
    }
    switch(operation) {
        case OPERATION_T::MUL_T:
            st.top().value = lval * rval;
            break;
        case OPERATION_T::PLUS_T:
            st.top().value = lval + rval;
            break;
        case OPERATION_T::MINUS_T:
            st.top().value = lval - rval;
            break;
        case OPERATION_T::DIV_T:
            st.top().value = lval / rval;  //exception!
            break;
        }
}