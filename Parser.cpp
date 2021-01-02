#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include "ENUMS.h"

const char Parser::nterm[] = {'A', 'S', 'U', 'T', 'V', 'F'};
const int Parser::term[] = {'+', '-', '*', '/', '(', ')', 1, 2, '=', 0};
const Parser::functionalArray Parser::funcArr[12] = {&Parser::f1, &Parser::f2, &Parser::f3, &Parser::f4,
                                                     &Parser::f5, &Parser::f6, &Parser::f7, &Parser::f8, &Parser::f9,
                                                     &Parser::f10, &Parser::f11, &Parser::f12};
const int Parser::M[6][10] =                 //Mатрица функций
        {{0, 0, 0, 0,  0,  0, 2,  0,  0, 0},
         {0, 0, 0, 0,  3,  0, 4,  4,  0, 0},                   //
         {5, 6, 1, 1,  1,  1, 1,  1,  1, 1},
         {0, 0, 0, 0,  7,  0, 8,  8,  0, 0},
         {1, 1, 9, 10, 1,  1, 1,  1,  1, 1},
         {0, 0, 0, 0,  11, 0, 12, 12, 0, 0},
        };

//43 - '+'
//42 - '*'
//40 - '('
//41 - ')'
//0 - концевой символ ';'
//1 - имя
Parser::Parser(Lexer l) {
    lex = l;
}


template<class T>
void Parser::clear_stack(stack<T> stack) {
    while (!stack.empty()) {
        stack.pop();
    }
}

template<class T>
void show_stack(stack<T> stack) {
    while (!stack.empty()) {
        cout << stack.top();
        stack.pop();
    }
    cout << endl;
}

void Parser::reset_parser() {
    sch = 'A';

    p_ops_tokens.clear();
    if (!stack1.empty()) clear_stack(stack1);
    if (!stack2.empty()) clear_stack(stack2);


    stack1.push(';');
    stack1.push('A');

    stack2.push(' ');
    stack2.push(' ');
}

bool Parser::push_ops() {
    int top1_ind = get_t_index(stack1.top());

    
    if (top1_ind >= 0 && term[top1_ind] != token_type) //stacks to string!!!
    {
        return false;
    }
    if (stack2.top() != ' ') {
        if (stack2.top() == 'a' && token_type <= 2 && token_type > 0)
            p_ops_tokens.push_back(token);
        else {
            string *temp_string = new string(1, stack2.top());
            auto temp_token = new Token(*temp_string, stack2.top());
            p_ops_tokens.push_back(*temp_token);
        }
    }
    stack2.pop();
    return true;
}

bool Parser::compare_stacks() {
    if (stack1.top() == ';')
        return false;
    if (lex.is_empty())
        return false;
    if (get_nt_index(stack1.top()) == -1) {
        token = lex.get_token();
        token_type = token.get_type();
        token_word = token.get_word();
        stack1.pop();
        sch = stack1.top();
    } else {
        int ns = get_nt_index(sch);
        if (ns >= 0)
            i = ns;

        int j = get_t_index(token_type);

        if (j >= 0 && i >= 0) {
            int k = M[i][j];
            k--;
            if (k >= 0) {
                (this->*funcArr[k])();
            } else {
                show_error("!Bad1 grammar");
                return false;
            }
        } else {
            show_error("!Bad2 nterm term arr error");
            return false;
        }
    }
    sch = stack1.top();
    return true;
}


OPS Parser::make_ops() {
    reset_parser();
    token = lex.get_token();
    token_word = token.get_word();
    token_type = token.get_type();

    while (!stack1.empty()) {
        if (!push_ops())
            break;

        if (!compare_stacks())
            break;
        show_stack(stack1);
    }
    auto items = make_ops_items();
    OPS cur_ops;




    return cur_ops;
}

vector<OPSItem> Parser::make_ops_items() {
    auto new_var_vector = new vector<OPSItem>();
    for (size_t pos = 0; pos < p_ops_tokens.size(); ++pos)
    {
        int type = p_ops_tokens[pos].get_type();
        auto temp_token = p_ops_tokens[pos];
        auto word = p_ops_tokens[pos].get_word();
        int value = std::stoi(word);
        switch(type)
        {
            case INT_T:
                new_var_vector->push_back(OPSItem(value, ITEM_TYPE::CONST));
                continue;
            case NAME_T:
                new_var_vector->push_back(OPSItem(word, ITEM_TYPE::VARIABLE));
                continue;
            default:
                new_var_vector->push_back(OPSItem(word, ITEM_TYPE::OPERATOR));
                continue;
        }
    }

}



void Parser::show_error(string error) {
    cout << error << endl;
}

int Parser::get_t_index(int num)
{
    int i = 0;
    while (i < sizeof(term))// '/sizeof(int)
    {
        if (num == term[i])
            return i;
        else
            i++;
    }
    return -1;
}

int Parser::get_nt_index(char ch) {
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


void Parser::f1() {
    stack1.pop();
}

void Parser::f2() {
    stack1.pop();
    stack1.push(' ');
    stack1.push('S');
    stack1.push('=');
    stack1.push('a');

    stack2.push('=');
    stack2.push(' ');
    stack2.push(' ');
    stack2.push('a');
}

void Parser::f3() {
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

void Parser::f4() {
    stack1.pop();
    stack1.push('U');
    stack1.push('V');
    stack1.push('a');

    stack2.push(' ');
    stack2.push(' ');
    stack2.push('a');
}

void Parser::f5() {
    stack1.pop();
    stack1.push('U');
    stack1.push('T');
    stack1.push('+');

    stack2.push('+');
    stack2.push(' ');
    stack2.push(' ');
}

void Parser::f6() {
    stack1.pop();
    stack1.push('U');
    stack1.push('T');
    stack1.push('-');

    stack2.push('-');
    stack2.push(' ');
    stack2.push(' ');
}

void Parser::f7() {
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

void Parser::f8() {
    stack1.pop();
    stack1.push('V');
    stack1.push('a');

    stack2.push(' ');
    stack2.push('a');
}

void Parser::f9() {
    stack1.pop();
    stack1.push('V');
    stack1.push('F');
    stack1.push('*');

    stack2.push('*');
    stack2.push(' ');
    stack2.push(' ');
}

void Parser::f10() {
    stack1.pop();
    stack1.push('V');
    stack1.push('F');
    stack1.push('/');

    stack2.push('/');
    stack2.push(' ');
    stack2.push(' ');
}

void Parser::f11() {
    stack1.pop();
    stack1.push(')');
    stack1.push('S');
    stack1.push('(');


    stack2.push(' ');
    stack2.push(' ');
    stack2.push(' ');
}

void Parser::f12() {
    stack1.pop();
    stack1.push('a');

    stack2.push('a');
}

