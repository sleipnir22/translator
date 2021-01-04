#include "Interpreter.h"

#define g Interpreter

void g::next() {
    pos++;
}

void g::show_variables() {
    std::cout << std::endl;
    for (auto& item : ops.vars )
    {
        std::cout << item.first << " : " << item.second << std::endl;
    }
}
g::Interpreter(OPS ops) {
    this->ops.items = ops.items;
    pos = 0;
}

void g::push_token(OPSItem item) {
    st.push(item);
}


//стек заполняем до тех пор, пока не встретится оператор
void g::generate_commands() {
//исправить (?)
    for(; pos < ops.items.size(); pos++)
    {
        if (ops.items[pos].type != ITEM_TYPE::OPERATOR) {
            push_token(ops.items[pos]);
        } else {
            auto b = st.top();
            st.pop();
            auto a = st.top();
            a_zero = a.value == 0;
            b_zero = b.value == 0;
            execute_command(a,b);
        }
    }
}


void g::execute_command(OPSItem a, OPSItem b) {
    if(ops.items[pos].word != "=") {
        if (k_zero) {
            LOAD(a);
            OP(b);
            st.top().value = 0;
            k = &st.top();
            k_zero = false;
        } else if (!k_zero && a_zero) {
            OP(b);
            st.top().value = 0;
            k = &st.top();
            k_zero = false;
        } else if (!k_zero && b_zero) {
            if (ops.items[pos].word == "+" || ops.items[pos].word == "*")
                OP(b);
            else {
                OPSItem t;
                ST(t);
                LOAD(a);
                OP(t);
                k = &t;
                k_zero = false;
            }
        }
    } else if (k_zero) {
            LOAD(b);
            ST(a);
        } else if (!k_zero && !b_zero) {
            OPSItem t;
            ST(t);
            LOAD(b);
            ST(a);
            k = &t;
            k_zero = false;
        } else if (!k_zero && b_zero) {
            ST(a);
            k_zero = true;
        }
}

void g::OP(OPSItem operand) {
    auto word = ops.items[pos].word;
    if(word == "+") {
        ADD(operand);
    } else if (word == "-") {
        SUB(operand);
    } else if (word == "*") {
        MUL(operand);
    } else if (word == "/") {
        DIV(operand);
    }
//    switch(op_type) {
//        case (PLUS_T):
//            ADD(operand);
//            return;
//        case (MINUS_T):
//            SUB(operand);
//            return;
//        case (MUL_T):
//            MUL(operand);
//            return;
//        case (DIV_T):
//            DIV(operand);
//            return;
//        default:
//            return;
//    }
}

void g::ADD(OPSItem item) {
    sum += item.value;
}

void g::SUB(OPSItem item) {
    sum -= item.value;
}

void g::DIV(OPSItem item) {
    try {
        if (item.value == 0)
            throw "Error! Division to 0"; //переписать обработчик ошибок
        sum /= item.value;
    }
    catch (std:: string& error) {
        std::cout << error << " ";
    }
}

void g::MUL(OPSItem item) {
    sum *= item.value;
}

void g::ST(OPSItem& item) {
    item.value = sum;
    ops.vars[item.word] = sum;
}

void g::LOAD(OPSItem item) {
    sum = item.value;
}