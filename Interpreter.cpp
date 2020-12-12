#include "Interpreter.h"
#define  g  Interpreter

const g::gf g::funcArr[6] = {
    &g::f1,&g::f2,&g::f3,&g::f4,&g::f5,& g::f6 }; // f1-ADD f2-SUB f3-MUL f4-DIV f5-Load f6-St
const char g::opArr[5] = { '+','-','*','/',':=' };


void Interpreter::get_commands(OPS tops)
{
    i = 0;
    ops = tops;
       

}

void Interpreter::push_token()
{
    stack.push(ops.ops_tokens[i]);
}

void Interpreter::fill_iter_stack()
{
    //while ()
}


void Interpreter::f1()
{
    sum += a;
}

void Interpreter::f2()
{
    sum -= a;
}

void Interpreter::f3()
{
    sum *= a;
}

void Interpreter::f4()
{
    sum /= a;
}

void Interpreter::f5()
{
    sum = a;
}

void Interpreter::f6()
{
    a = sum;
}
