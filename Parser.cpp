#include "Parser.h"
#include "ENUMS.h"

const Parser::functionalArray Parser::funcArr[15] = { &Parser::f1, &Parser::f2, &Parser::f3, &Parser::f4,
                                                     &Parser::f5, &Parser::f6, &Parser::f7, &Parser::f8, &Parser::f9,
                                                     &Parser::f10, &Parser::f11, &Parser::f12,& Parser::f13,& Parser::f14,& Parser::f15 };
const int Parser::M[6][10] =                 //Mатрица функций
{ {0, 0, 0, 0,  0,  0, 2,  0,  0, 0},
 {0, 0, 0, 0,  3,  0, 4,  5,  0, 0},                   
 {6, 7, 1, 1,  1,  1, 1,  1,  1, 1},
 {0, 0, 0, 0,  8,  0, 9,  10,  0, 0},
 {1, 1, 11, 12, 1,  1, 1,  1,  1, 1},
 {0, 0, 0, 0,  13, 0, 14, 15, 0, 0},
};


Parser::Parser(Lexer l) {
    lex = l;
    reset_parser();

}
void Parser::reset_parser() {
    token = get_token();
    st_item = new stack_item(A);

    stack1.push(new stack_item(TOKEN_T::END_T));
    stack1.push(new stack_item(A));

    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
}


Token Parser::get_token(){
    Token cur_token = lex.get_token();
    token_word = cur_token.get_word();
    token_type = cur_token.get_type();
    return cur_token;
}



void Parser::step(STACK_ITEM_T top1_type, TOKEN_T top2_type)
{

    if (top2_type != TOKEN_T::EMPTY_T)
    {
        switch (top2_type)
        {
        case TOKEN_T::INT_T:
            if (token_type == TOKEN_T::INT_T)
            {
                cur_ops.items.push_back(*(new OPSItem(stoi(token_word), ITEM_TYPE::CONST, TOKEN_T::INT_T)));
            }
            else
                show_error("Int matching error!");
            break;
        case TOKEN_T::NAME_T:
            if (token_type == TOKEN_T::NAME_T)
            {
                cur_ops.items.push_back(*(new OPSItem(token_word, ITEM_TYPE::VARIABLE, TOKEN_T::NAME_T)));
                cur_ops.variables.push_back(*(new OPSItem(token_word, ITEM_TYPE::VARIABLE, TOKEN_T::NAME_T)));
            }
            else
                show_error("Name matching error!");
            break;
        default:
            cur_ops.items.push_back(*(new OPSItem(ITEM_TYPE::OPERATOR, stack2.top()->get_type())));
        }
    }
    stack2.pop();
    if (top1_type == STACK_ITEM_T::TERM_T)
    {
        token = get_token();
        stack1.pop();
    }
    else
    {
        STATE cur_state = stack1.top()->get_state();

        int cur_type = (int) token.get_type();

        if (cur_type >= 0)
        {
            int func_num = M[cur_state][cur_type];
            (this->*funcArr[func_num-1])();
            std::cout << "func[" << func_num << "]" << std::endl;
        }
    }
}

void Parser::show_error(std::string error) {
    std::cout << error << std::endl;
}


OPS Parser::make_ops() {
    while (!stack2.empty()) // lex is empty error!?
    {
        STACK_ITEM_T top1_type = stack1.top()->get_stack_item_type();
        TOKEN_T top2_type = stack2.top()->get_type();
        step(top1_type, top2_type);

        if (!lex.is_empty() && stack2.empty())
            reset_parser();
    }

    return cur_ops;
}




void Parser::f1() {
    stack1.pop();
}

void Parser::f2() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::EMPTY_T));
    stack1.push(new stack_item(S));
    stack1.push(new stack_item(TOKEN_T::ASSIGN_T));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item(TOKEN_T::ASSIGN_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f3() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(S));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));

    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
}

void Parser::f4() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f5() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::INT_T));

    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::INT_T));
}

void Parser::f6() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(T));
    stack1.push(new stack_item(TOKEN_T::PLUS_T));

    stack2.push(new stack_item(TOKEN_T::PLUS_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
}

void Parser::f7() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(T));
    stack1.push(new stack_item(TOKEN_T::MINUS_T));

    stack2.push(new stack_item(TOKEN_T::MINUS_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));;
}

void Parser::f8() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(S));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));

    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
}

void Parser::f9() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f10() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::INT_T));

    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::INT_T));
}

void Parser::f11() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(F));
    stack1.push(new stack_item(TOKEN_T::MUL_T));

    stack2.push(new stack_item(TOKEN_T::MUL_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
}

void Parser::f12() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(F));
    stack1.push(new stack_item(TOKEN_T::DIV_T));

    stack2.push(new stack_item(TOKEN_T::DIV_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
}

void Parser::f13() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(S));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));

    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
    stack2.push(new stack_item(TOKEN_T::EMPTY_T));
}

void Parser::f14() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f15() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::INT_T));

    stack2.push(new stack_item(TOKEN_T::INT_T));
}