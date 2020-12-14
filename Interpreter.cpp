#include "Interpreter.h"
#define g Interpreter


const string g::opArr[] {"-", "*", "/", "+", "*"};
const g::gf g::funcArr[] {&g::SUB, &g::MUL, &g::DIV, &g::ADD};
//int g::get_function_number()
//{
//    for (size_t i = 0; i < opArr->size(); i++)
//    {
//        ;//
//    }
//    return;
//}

bool g::is_operator(string word)
{
    for (size_t i = 0; i < opArr->size(); i++)
    {
        if (word == opArr[i])
            return true;
        else
            return false;
    }
}

g::Interpreter(OPS ops)
{
    this->ops.ops_tokens = ops.ops_tokens;
    this->ops.ops_varArr = ops.ops_varArr;      //здесь должен быть массив констант, который создается во время семантического анализа
}                                               //нужно поправить

void g::push_token(Token token)
{
    st.push(token);
}

void g::fill_stack()
{
    i = 0;
    string temp = ops.ops_tokens[i].get_word();
    while (!is_operator(temp) && i < ops.ops_tokens.size())                 //стек заполняем до тех пор, пока не встретится оператор
    {
        push_token(ops.ops_tokens[i]);
        temp = ops.ops_tokens[i++].get_word();
    }
    i++;
}


void g::generate_commands()
{
    fill_stack();
    if (k == 0)
    {
        ;
    }
}

void g::ADD(int operand)
{
    sum += operand;
}
void g::SUB(int operand)
{
    sum -= operand;
}

void g::MUL(int operand)
{
    sum *= operand;
}

void g::DIV(int operand)
{
    sum /= operand;
}

void g::LOAD(int operand)
{
    sum = operand;
}

void g::ST(int& operand)
{
    operand = sum;
}