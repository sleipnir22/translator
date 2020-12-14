#include "Interpreter.h"
#define  g  Interpreter

g::gf g::funcArr[6] = {
    &g::ADD,&g::SUB,&g::MUL,&g::DIV,&g::Load,& g::St }; // f1-ADD f2-SUB f3-MUL f4-DIV f5-Load f6-St
const char g::opArr[5] = { '+','-','*','/','=' };


void Interpreter::get_commands(OPS tops)
{
    i = 0;
    ops = tops;
       
    set_mem_var();
}

void Interpreter::set_mem_var()
{
    for (int i = 0; i < ops.varArr.size(); i++)
    {
        varMap[ops.varArr[i]] = 0;
    }

    cout << endl;
    for (int i = 0; i < varMap.size(); i++)
    {
        cout << ops.varArr[i] << " " << varMap[ops.varArr[i]] << endl;
    }
}

void Interpreter::push_token()
{
    com_stack.push(ops.tokens[i]);
}

int  Interpreter::get_op_index(int type)
{
    int i = 0;
    while (i < sizeof(opArr))
    {
        if (opArr[i] == type)
            return i;
        else
            ++i;
    }
    return -1;
}

int Interpreter::fill_until_op()
{
    int type, i = 0;
    do
    {
        type = ops.tokens[i].get_type();
        inter_stack.push(ops.tokens[i]);
        i++;
    } 
    while (!get_op_index(type));

    inter_stack.push(ops.tokens[i]);
    int op = ops.tokens[i].get_type();
    inter_stack.pop();
    return op;
}

void Interpreter::fill_com_stack()
{

    for (int i = 0; !ops.tokens.empty(); i++)
    {
        int type = fill_until_op();

        load_two_top();

        com(type);

    }
}

void Interpreter::load_two_top()
{
    string word;
    word = inter_stack.top().get_word();
    b = word;
    inter_stack.pop();
    bool b_zero = false;

    word = inter_stack.top().get_word();
    a = word;
    bool a_zero = false;
    inter_stack.pop();
}

void Interpreter::com(int type)
{
    string val;
    if (type == '=')
    {
        if (k_zero)
        {
            Load(b);
            St(a);
        }
        else 
        {
            if (b_zero)
            {

                St(t);
                Load(b);
                St(a);
            }
            else
            {

                St(a);
            }
        }
    }
    else
    {
        if (k_zero)
        {
            Load(a);
            val = b;
            op_exe(type, val);
        }
        else
        {
            if (a_zero)
            {
                val = b;
                k = inter_stack.size();
                op_exe(type, val);
            }
            else
            {
                if (b_zero)
                {

                }
                else
                {

                }
            }
        }
    }
}

void Interpreter::op_exe(int type, string val)
{
    switch (type)
    {
    case '+':
        ADD(val);
        break;
    case '-':
        SUB(val);
        break;
    case '*':
        MUL(val);
        break;
    case '/':
        DIV(val);
        break;
    default:
        cout << "\ncom error!\n";
        break;

    }
}

void Interpreter::ADD(string str)
{
    int val = varMap[str];
    sum += val;
}

void Interpreter::SUB(string str)
{
    int val = varMap[str];
    sum -= val;
}

void Interpreter::MUL(string str)
{
    int val = varMap[str];
    sum *= val;
}

void Interpreter::DIV(string str)
{
    int val = varMap[str];
    sum /= val;
}

void Interpreter::Load(string str)
{
    int val = varMap[str];
    sum = val;
}

void Interpreter::St(string str)
{
    int val = varMap[str];
    val = sum;
}
