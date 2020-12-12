#include "Parser.h"
#include "Lexer.h"

const char Parser::nterm[] = { 'S','U','T','V','F' };
const int Parser::term[] = { '+','-', '*','/','(', ')', 2, 1, 0 };
const Parser::functionalArray Parser::funcArr[11] = { &Parser::f1, &Parser::f2, &Parser::f3, &Parser::f4,
                                                    &Parser::f5, &Parser::f6, &Parser::f7, &Parser::f8, &Parser::f9, &Parser::f10,& Parser::f11 };
const int Parser::M[5][9] =                 //Mатрица функций
{   {0,0,0,0,2,0,3,3,0},         //
    {4,5,1,1,1,1,1,1,1},
    {0,0,0,0,6,0,7,7,0},
    {1,1,8,9,1,1,1,1,1},
    {0,0,0,0,10,0,11,11,0},
};
//43 - '+'
//42 - '*'
//40 - '('
//41 - ')'
//0 - концевой символ ';'
//1 - имя
Parser::Parser(Lexer l)
{
    lex = l;
}


template <class T> void Parser::clear_stack(stack<T> stack)
{
    while (!stack.empty())
    {
        stack.pop();
    }
}

void Parser::reset_parser()
{
    pos = 0;
    i = 0;
    sch = 'S';
    cnt = 0;
    x = 0;
    
    p_ops_tokens.clear();
    if (!stack1.empty()) clear_stack(stack1);
    if (!stack2.empty()) clear_stack(stack2);


    stack1.push(';');
    stack1.push('S');

    stack2.push(' ');
    stack2.push(' ');
}

bool Parser::push_ops()
{

    token_word = token.get_word();
    token_type = token.get_type();

    if (get_nt_index(stack1.top()) == -1 && sch == ';')
    {
        return false;
    }
    if (stack2.top() != ' ')
    {
        if (stack2.top() == 'a' && token.get_type() <= 2)
            p_ops_tokens.push_back(token);
        else
        {
            string* temp_string = new string(1, stack2.top());
            auto temp_token = new Token(*temp_string, token_type);
            p_ops_tokens.push_back(*temp_token);
        }
    }
    stack2.pop();
    return true;
}

bool Parser::compare_stacks()
{
    if (get_nt_index(stack1.top()) == -1)
    {
        pos++;
        token = lex.get_token();
        stack1.pop();
        sch = stack1.top();
    }
    else
    {
        int ns = get_nt_index(sch);
        if (ns >= 0)
            i = ns;

        int j = get_t_index(token_type);

        if (j >= 0 && i >= 0)
        {
            int k = M[i][j];
            k--;
            if (k >= 0)
            {
                (this->*funcArr[k])();
            }
            else
            {
                show_error("!Bad1");
                return false;
            }
        }
        else
        {
            show_error("!Bad2");
            return false;
        }
    }
    sch = stack1.top();
    return true;
}



OPS Parser::make_ops()
{
    reset_parser();
    token = lex.get_token();
    while (!lex.is_empty())
    {
        if (!push_ops()) break;

        if (!compare_stacks()) break;
    }
    OPS cur_ops;
    cur_ops.ops_tokens = p_ops_tokens;
    cur_ops.ops_varArr = lex.get_varArr();
    return cur_ops;
}

void Parser::show_error(string error)
{
    cout << error << endl;
}

int Parser::get_t_index(int num)
{
    int i = 0;
    while (i < sizeof(term))
    {
        if (num == term[i])// '/sizeof(int)
            return i;
        else
            i++;
    }
    return -1;
}
int Parser::get_nt_index(char ch)
{
    int i = 0;
    while (i < sizeof(nterm))// '/sizeof(int)
    {
        if (ch == nterm[i])
            return i;
        else
            ++i;
    }
    return -1;
}


void Parser::f1()
{
    stack1.pop();
}
void Parser::f2()
{
    stack1.pop();
    stack1.push('U');
    stack1.push('V');
    stack1.push(')');
    stack1.push('S');
    stack1.push('(');

    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f3()
{
    stack1.pop();
    stack1.push('U');
    stack1.push('V');
    stack1.push('a');

    stack2.push(' ');
    stack2.push(' ');
    stack2.push('a');
}
void Parser::f4()
{
    stack1.pop();
    stack1.push('U');
    stack1.push('T');
    stack1.push('+');

    stack2.push('+');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f5()
{
    stack1.pop();
    stack1.push('U');
    stack1.push('T');
    stack1.push('+');

    stack2.push('-');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f6()
{
    stack1.pop();
    stack1.push('V');
    stack1.push(')');
    stack1.push('S');
    stack1.push('(');

    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f7()
{
    stack1.pop();
    stack1.push('V');
    stack1.push('a');

    stack2.push(' ');
    stack2.push('a');
}
void Parser::f8()
{
    stack1.pop();
    stack1.push('V');
    stack1.push('F');
    stack1.push('*');

    stack2.push('*');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f9()
{
    stack1.pop();
    stack1.push('V');
    stack1.push('F');
    stack1.push('/');

    stack2.push('/');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f10()
{
    stack1.pop();
    stack1.push(')');
    stack1.push('S');
    stack1.push('(');


    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f11()
{
    stack1.pop();
    stack1.push('a');

    stack2.push('a');
}

