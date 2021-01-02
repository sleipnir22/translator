#include "Interpreter.h"
#include "ENUMS.h"

#define g Interpreter


void g::get_two_operands() {
    auto temp = st;
    b = temp.top();
    temp.pop();
    a = temp.top();
}

g::Interpreter(OPS ops) {
    i = 0;
    this->ops.ops_tokens = ops.ops_tokens;
    this->ops.ops_varArr = ops.ops_varArr;
    a = Token();
    b = Token();
    t = Token();
    k = nullptr;
    //здесь должен быть массив констант, который создается во время семантического анализа
}                                               //нужно поправить

void g::push_token(Token token) {
    st.push(token);
}


//стек заполняем до тех пор, пока не встретится оператор
void g::fill_stack() {
    if ((i < ops.ops_tokens.size() - 1) && (ops.ops_tokens[i].is_op())) {
        i++;
    }
    while (i < ops.ops_tokens.size() && (!ops.ops_tokens[i].is_op())) {
        push_token(ops.ops_tokens[i]);
        i++;
    }
}
void g::generate_commands() {
    fill_stack();
    while (!st.empty()) {
        get_two_operands();
        a_zero = (variables.find(a) == variables.end()) || a.get_type() == INT_T;
        b_zero = (variables.find(b) == variables.end()) || b.get_type() == INT_T;

        execute_command();
        fill_stack();
    }
}



void g::execute_command() {
    Token null = Token();
    if (st.size() > 1) {
        if (ops.ops_tokens[i].get_type() != EQUALS_T && st.size() > 1) {

            if (k_zero) {
                LOAD(a);
                OP(a);

                //st.pop();
                st.top() = null;
                k = &st.top();
                k_zero = false;
            } else if (!k_zero && a_zero) {
                OP(b);
                //st.pop();
                st.top() = null;

                k = &st.top();
                k_zero = false;
            } else if (!k_zero && b_zero) {
                OP(b);
                ST(t);
                LOAD(a);
                OP(t);

                //st.pop();
                st.top() = null;
                k = &st.top();
                k_zero = false;

            } else if (!k_zero && !b_zero && !a_zero) {
                ST(t);
                LOAD(a);
                OP(b);

                //st.pop();
                st.top() = null;

                t = *k;
                k = &st.top();
                k_zero = false;
            }
        } else {
            if (k_zero) {
                LOAD(b);
                ST(a);

                //st.pop();
                st.top() = null;
                k = &st.top();
            } else if (!k_zero && !b_zero) {
                ST(t);
                LOAD(b);
                ST(a);
                k = &t;
            } else if (!k_zero && b_zero) {
                ST(a);
                k = nullptr;
                k_zero = true;
            }
        }
    }
}

void g::OP(Token operand)
{
    auto op_type = ops.ops_tokens[i].get_type();
    switch(op_type) {
        case (PLUS_T):
            ADD(operand);
            return;
        case (MINUS_T):
            SUB(operand);
            return;
        case (MUL_T):
            MUL(operand);
            return;
        case (DIV_T):
            DIV(operand);
            return;
        default:
            return;
    }
}

void g::show_variables()
{
    cout << "\n";
    for(auto it = variables.begin(); it != variables.end(); ++it)
    {
        cout << it->first.get_word() << " : " << it->second << endl;
    }
}

void g::ADD(Token operand) {
    sum += stoi(operand.get_word());
}

void g::SUB(Token operand) {
    sum -= stoi(operand.get_word());
}

void g::MUL(Token operand) {
    sum *= stoi(operand.get_word());
}

void g::DIV(Token operand) {
    sum /= stoi(operand.get_word());
}

void g::LOAD(Token operand) {
    sum = stoi(operand.get_word());
}

void g::ST(Token& operand) {
    if (variables.find(operand) == variables.end())
    {
        variables.insert(make_pair(operand, sum));
    } else {
        variables[operand] = sum;
    }
}