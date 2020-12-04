#include "Parser.h"

const char Parser::nterm[] = {'S','U','T','V','F'};
const int Parser::term[]   = {43, 42, 40, 41, 1, 0};
const Parser::functionalArray Parser::funcArr[9] = {&Parser::f1, &Parser::f2, &Parser::f3, &Parser::f4,
                                                    &Parser::f5, &Parser::f6, &Parser::f7, &Parser::f8, &Parser::f9  };
const int Parser::M[5][6] =                 //Mатрица функций
        {   {0,0,1,0,2,0},         //
            {3,4,4,4,4,4},
            {0,0,5,0,6,0},
            {4,7,4,4,4,4},
            {0,0,8,0,9,0},
        };
//0 - концевой символ ';'
//1 - имя
//43 - '+'
//45 - '-'
//40 - '('
//41 - ')'
//42 - '*'
Parser::Parser(const vector<Token>& tokens)
{
    this->tokens = tokens;
}

vector<Token> Parser::make_ops()
{
    int i = 0;
    vector<Token> OPS;
    char sch = 'S';
    int cnt = 0;
    int x = 0;
    queue <Token> buffer;
    stack1.push(';');
    stack1.push('S');

    stack2.push(' ');
    stack2.push(' ');
    while (pos < tokens.size())
    {
        string token_word = tokens[pos].get_word();
        int token_type = tokens[pos].get_type();

        if (get_nt_index(stack1.top()) == -1 && sch == ';')
        {
            break;
        }
        if (stack2.top() != ' ')
        {
            if (stack2.top() == 'a')
            {
                for (int j = x; j < tokens.size(); j++)
                {
                    if (tokens[j].get_type() == 1)
                    {
                        OPS.push_back(tokens[j]);
                        x = ++j;
                        break;
                    }
                }
            }
            else
            {
                string* temp_string = new string(1, stack2.top());
                auto temp_token = new Token(*temp_string,0);
                OPS.push_back(*temp_token);
            }
        }

        stack2.pop();

        if (get_nt_index(stack1.top()) == -1)
        {
            pos++;
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
                    break;
            }
            else
                break;
        }
        sch = stack1.top();
    }
    return OPS;
}



int Parser::get_t_index(int num)
{
    int i = 0;
    while (i < 6)
    {
        if (num == term[i])
            return i;
        else
            i++;
    }
    return -1;
}
int Parser::get_nt_index(char ch)
{
    int i = 0;
    while (i < 5)
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
void Parser::f2()
{
    stack1.pop();
    stack1.push('U');
    stack1.push('V');
    stack1.push('a');

    stack2.push(' ');
    stack2.push(' ');
    stack2.push('a');
}
void Parser::f3()
{
    stack1.pop();
    stack1.push('U');
    stack1.push('T');
    stack1.push('+');

    stack2.push('+');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f4()
{
    stack1.pop();
}
void Parser::f5()
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
void Parser::f6()
{
    stack1.pop();
    stack1.push('V');
    stack1.push('a');

    stack2.push(' ');
    stack2.push('a');
}
void Parser::f7()
{
    stack1.pop();
    stack1.push('V');
    stack1.push('F');
    stack1.push('*');

    stack2.push('*');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f8()
{
    stack1.pop();
    stack1.push(')');
    stack1.push('S');
    stack1.push('(');


    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
}
void Parser::f9()
{
    stack1.pop();
    stack1.push('a');

    stack2.push('a');
}


