#include "Parser.h"
#include "ENUMS.h"
#include "Errors.h"

#define  p Parser

const p::functionalArray p::funcArr[47] = {&p::f1, &p::f2, &p::f3, &p::f4, &p::f5, &p::f6, &p::f7, &p::f8, &p::f9,
                                           &p::f10, &p::f11,
                                           &p::f12, &p::f13, &p::f14, &p::f15, &p::f16, &p::f17, &p::f18, &p::f19,
                                           &p::f20, &p::f21,
                                           &p::f22, &p::f23, &p::f24, &p::f25, &p::f26, &p::f27, &p::f28, &p::f29,
                                           &p::f30, &p::f31,
                                           &p::f32, &p::f33, &p::f34, &p::f35, &p::f36, &p::f37, &p::f38, &p::f39,
                                           &p::f40, &p::f41, &p::f42, &p::f43, &p::f44, &p::f45, &p::f46, &p::f47};


const int Parser::M[17][28] =                 //M������ �������
        {   //  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z  AA AB AC
                /*2*/ {2,  0,  3,  4,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  0,  8,  0,  0,  0,  0,  0,  0,  46},
                /*3*/
                      {10, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
                /*4*/
                      {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
                /*5*/
                      {12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
                /*6*/
                      {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
                /*7*/
                      {14, 1,  1,  1,  15, 16, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  7,  1,  8,  1,  1,  1,  1,  1,  1,  1},
                /*8*/
                      {17, 1,  1,  1,  18, 19, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  20, 1,  21, 1,  1,  1,  1,  1,  1,  1},
                /*9*/
                      {1,  1,  1,  1,  1,  1,  1,  1,  47,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
                /*10*/
                      {22, 23, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  24, 0,  0},
                /*11*/
                      {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  25, 26, 27, 28, 29, 30, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
                /*12*/
                      {45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 31, 45, 45, 45, 45, 45, 45, 45, 45},
                /*13*/
                      {32, 33, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  34, 0,  0},
                /*14*/
                      {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  35, 36, 1,  1,  1,  1,  1},
                /*15*/
                      {37, 38, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  39, 0,  0},
                /*16*/
                      {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  40, 41, 1,  1,  1},
                /*17*/
                      {42, 43, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  44, 0,  0},
                /*18*/
                      {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1}
        };


Parser::Parser(Lexer l) {
    lex = l;
    reset_parser();
}

void Parser::execute_semantic(std::vector<OPSItem>& ops_items, std::stack<stack_item *>& stack2) {
    auto word = stack2.top()->get_word();
    auto m_size = marks.size();
    if (word == "<1>") {
        marks.push(k);
        cur_ops.items.emplace_back(OPSItem(std::string("m")+ std::to_string(m_size)));
        cur_ops.items.emplace_back(OPSItem("JF", OPERATION_T::JF_T));
        count();
        count();
    } else if (word == "<2>") {
        cur_ops.items[marks.top()].mark_pos = k + 2;
        marks.pop();
        marks.push(k);
        cur_ops.items.emplace_back(OPSItem(std::string("m")+ std::to_string(m_size)));
        cur_ops.items.emplace_back(OPSItem("J",OPERATION_T::J_T));
        count();
        count();
    } else if (word == "<3>") {
        cur_ops.items[marks.top()].mark_pos = k;
        marks.pop();
    } else if (word == "<4>") {
        marks.push(k);
    } else if (word == "<5>") {
        cur_ops.items[marks.top()].mark_pos = k + 2;
        marks.pop();
        cur_ops.items.emplace_back(OPSItem(std::string("m")+ std::to_string(m_size), marks.top()));
        marks.pop();
        cur_ops.items.emplace_back(OPSItem("J",OPERATION_T::J_T));
        count();
        count();
    } else if (word == "<11>") {
        is_filling_vars = true;
    } else if (word == "<12>") {
        is_filling_arr = true;
    } else if (word == "<16>") {
        if (is_filling_vars) {
            if (cur_ops.vars.find(token_word) == cur_ops.vars.end())
                cur_ops.vars.insert(make_pair(token_word, 0));
            else
                throw DeclarationError(token.col, token.row, token);
            //return;
        }
        if (is_filling_arr){
            cur_ops.items.push_back(*(new OPSItem(token_word, ITEM_TYPE::VARIABLE, TOKEN_T::NAME_T)));
            count();
            if (cur_ops.arr.find(token_word) == cur_ops.arr.end()) {
                cur_ops.arr.insert(make_pair(token_word, std::vector<int>()));
            } else
                throw DeclarationError(token.col, token.row, token);
            //return;
        }
    } else if (word == "<m1>") {
        cur_ops.items.emplace_back(OPSItem("DECLARE_ARR",OPERATION_T::DECLARE_ARR));
        count();
    } else if (word == "<e_declare>") {
        is_filling_vars = false;
        is_filling_arr = false;
    } else if (word == "<r>"){
        cur_ops.items.emplace_back(OPSItem("READ",OPERATION_T::READ_T));
        count();
    } else if (word == "<w>"){
        cur_ops.items.emplace_back(OPSItem("WRITE",OPERATION_T::WRITE_T));
        count();
    } else if (word == "<i>") {
        cur_ops.items.emplace_back(OPSItem("INDEX",OPERATION_T::I_T));
        count();
    }
}

bool Parser::is_semantic(std::stack<stack_item *>& stack2) {
    auto word = stack2.top()->get_word();
    if (word == "<1>" || word == "<2>" || word == "<3>" || word == "<4>"
        || word == "<5>" || word == "<m1>" || word == "<11>" ||word == "<e_declare>"
        || word == "<12>" || word == "<16>" ||
        word == "<w>" || word == "<r>" || word == "<i>"
            ) {
        return true;
    } else return false;
}

void Parser::count() {
    k++;
}

void Parser::reset_parser() {

    stack1.push(new stack_item(P));

    stack2.push(new stack_item());
    token = get_token();
}


Token Parser::get_token() {
    if (lex.is_empty()) {
        throw SyntaxError(token.col, token.row, token);
        //show_error("Lexer empty error!");
    }

    Token cur_token = lex.get_token();
    //std::cout << cur_token.get_word() << " ";
    token_word = cur_token.get_word();
    token_type = cur_token.get_type();
    if (token_type == TOKEN_T::ERROR_T) {
        throw IllegalCharacter(cur_token.col, token.row, token);
        //show_error("Lexeme error!");
    }

    return cur_token;
}


void Parser::step(STACK_ITEM_T top1_item_type, STACK_ITEM_T top2_item_type) {
    if (top2_item_type != STACK_ITEM_T::EMPTY_T) {
        TOKEN_T top2_type = stack2.top()->get_type();
        switch (top2_type) {
            case TOKEN_T::INT_T:
                if (token_type == TOKEN_T::INT_T) {
                    count();
                    cur_ops.items.push_back(*(new OPSItem(std::stoi(token_word), ITEM_TYPE::CONST, TOKEN_T::INT_T)));
                } else
                    throw SyntaxError(token.col, token.row, token);
                break;
            case TOKEN_T::NAME_T:
                if (token_type == TOKEN_T::NAME_T) {
                    count();
                    cur_ops.items.push_back(*(new OPSItem(token_word, ITEM_TYPE::VARIABLE, TOKEN_T::NAME_T)));
                } else
                    throw SyntaxError(token.col, token.row, token);
                break;
            default:
                if (is_semantic(stack2)) {
                    execute_semantic(cur_ops.items, stack2);
                } else {
                    cur_ops.items.push_back(
                            *(new OPSItem(stack2.top()->get_word(), ITEM_TYPE::OPERATOR, stack2.top()->get_type()))
                    );
                    count();
                }
        }
    }

    stack2.pop(); // Экстра важно!!! Без этой функции парсер ложится на лопатки (обычно)

    switch (top1_item_type) {
        default:
            stack1.pop();
            break;
        case STACK_ITEM_T::TERM_T:
            if (stack1.top()->get_type() == token_type) {
                if (!lex.is_empty())
                    token = get_token();
            } else
                throw SyntaxError(token.col, token.row, token);  //когда ожидалась другая лексема
            stack1.pop();
            break;
        case STACK_ITEM_T::STATE_T:
            STATE cur_state = stack1.top()->get_state();
            auto cur_type = (int)token.get_type();
            if (cur_state >= 0) {
                if (cur_type >= 0) {
                    int func_num = M[cur_state][cur_type];
                    if (func_num > 0) {
                        (this->*funcArr[func_num - 1])();
                        //std::cout << "func[" << func_num << "]" << std::endl;
                    } else
                        throw SyntaxError(token.col, token.row, token);  //грамматическая ошибка
                } else
                    throw SyntaxError(token.col, token.row, token);
            } else throw SyntaxError(token.col, token.row, token);
    }
}

OPS Parser::make_ops() {

    while (!lex.is_empty() || (!stack2.empty() && !stack1.empty())) // lex is empty error!?
    {
        STACK_ITEM_T top1_item_type;
        STACK_ITEM_T top2_item_type;
        try {
            if (!stack1.empty())
                top1_item_type = stack1.top()->get_stack_item_type();
            else throw SyntaxError(token.col, token.row, token);// stack1 empty error!
            if (!stack2.empty())
                top2_item_type = stack2.top()->get_stack_item_type();
            else throw SyntaxError(token.col, token.row, token); // stack2 empty error!
            step(top1_item_type, top2_item_type);
        }
        catch (Error& e) {
            std::cerr << e.what() << "\n";
            break;
        }
    }
    cur_ops.items.emplace_back(OPSItem("_|_", ITEM_TYPE::FINAL, TOKEN_T::END_T));
    return cur_ops;
}

void Parser::f1() {
    stack1.pop();
}

void Parser::f2() {
    stack1.pop();
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::ASSIGN_T));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::ASSIGN_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f3() {
    stack1.pop();
    stack1.push(new stack_item(P));
    stack1.push(new stack_item(I));
    stack1.push(new stack_item(TOKEN_T::NEWINT_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<11>", TOKEN_T::EMPTY_T));
}

void Parser::f4() {
    stack1.pop();
    stack1.push(new stack_item(P));
    stack1.push(new stack_item(A));
    stack1.push(new stack_item(TOKEN_T::NEWARRAY_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<12>",TOKEN_T::EMPTY_T));
}

void Parser::f5() {
    stack1.pop();
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::READ_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<r>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f6() {
    stack1.pop();
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::WRITE_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<w>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f7() {
    stack1.pop();
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(Z));
    stack1.push(new stack_item(K));
    stack1.push(new stack_item(TOKEN_T::R_BRACE_T));
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(S));
    stack1.push(new stack_item(TOKEN_T::L_BRACE_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(C));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::IF_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<1>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f8() {
    stack1.pop();
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(TOKEN_T::R_BRACE_T));
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(S));
    stack1.push(new stack_item(TOKEN_T::L_BRACE_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(C));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::WHILE_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item("<5>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<1>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<4>"));
}

void Parser::f9() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));

    stack2.push(new stack_item("<e_declare>"));

}

void Parser::f10() {
    stack1.pop();
    stack1.push(new stack_item(STATE::M));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item("<16>"));
}

void Parser::f11() {
    stack1.pop();
    stack1.push(new stack_item(STATE::M));
    stack1.push(new stack_item(TOKEN_T::NAME_T));
    stack1.push(new stack_item(TOKEN_T::COMMA_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item("<16>"));
    stack2.push(new stack_item());
}

void Parser::f12() {
    stack1.pop();
    stack1.push(new stack_item(N));
    stack1.push(new stack_item(TOKEN_T::R_SQUARE_T));
    stack1.push(new stack_item(TOKEN_T::INT_T));
    stack1.push(new stack_item(TOKEN_T::L_SQUARE_T));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item("<m1>"));
    stack2.push(new stack_item(TOKEN_T::INT_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item("<16>"));
}

void Parser::f13() {
    stack1.pop();
    stack1.push(new stack_item(N));
    stack1.push(new stack_item(TOKEN_T::R_SQUARE_T));
    stack1.push(new stack_item(TOKEN_T::INT_T));
    stack1.push(new stack_item(TOKEN_T::L_SQUARE_T));
    stack1.push(new stack_item(TOKEN_T::NAME_T));
    stack1.push(new stack_item(TOKEN_T::COMMA_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item("<m1>"));
    stack2.push(new stack_item(TOKEN_T::INT_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item("<16>"));
    stack2.push(new stack_item());
}

void Parser::f14() {
    stack1.pop();
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::ASSIGN_T));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::ASSIGN_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f15() {
    stack1.pop();
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::READ_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<r>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f16() {
    stack1.pop();
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::WRITE_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<w>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f17() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::ASSIGN_T));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));


    stack2.push(new stack_item(TOKEN_T::ASSIGN_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f18() {

    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::READ_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item("<r>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f19() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::WRITE_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item("<w>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());

}

void Parser::f20() {
    stack1.pop();
    stack1.push(new stack_item(Z));
    stack1.push(new stack_item(K));
    stack1.push(new stack_item(TOKEN_T::R_BRACE_T));
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(S));
    stack1.push(new stack_item(TOKEN_T::L_BRACE_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(C));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::IF_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<1>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f21() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::R_BRACE_T));
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(S));
    stack1.push(new stack_item(TOKEN_T::L_BRACE_T));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(C));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));
    stack1.push(new stack_item(TOKEN_T::WHILE_T));

    stack2.push(new stack_item("<5>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<1>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<4>"));
}

void Parser::f22() {
    stack1.pop();
    stack1.push(new stack_item(D));
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f23() {
    stack1.pop();
    stack1.push(new stack_item(D));
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::INT_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::INT_T));
}

void Parser::f24() {
    stack1.pop();
    stack1.push(new stack_item(D));
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f25() {
    stack1.pop();
    stack1.push(new stack_item(Z));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::LESS_T));

    stack2.push(new stack_item(TOKEN_T::LESS_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f26() {
    stack1.pop();
    stack1.push(new stack_item(Z));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::GREATER_T));

    stack2.push(new stack_item(TOKEN_T::GREATER_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f27() {
    stack1.pop();
    stack1.push(new stack_item(Z));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::LOREQUAL_T));

    stack2.push(new stack_item(TOKEN_T::LOREQUAL_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f28() {
    stack1.pop();
    stack1.push(new stack_item(Z));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::GOREQUAL_T));

    stack2.push(new stack_item(TOKEN_T::GOREQUAL_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f29() {
    stack1.pop();
    stack1.push(new stack_item(Z));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::EQUAL_T));

    stack2.push(new stack_item(TOKEN_T::EQUAL_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f30() {
    stack1.pop();
    stack1.push(new stack_item(Z));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::NOTEQUAL_T));

    stack2.push(new stack_item(TOKEN_T::NOTEQUAL_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f31() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::R_BRACE_T));
    stack1.push(new stack_item(Q));
    stack1.push(new stack_item(S));
    stack1.push(new stack_item(TOKEN_T::L_BRACE_T));
    stack1.push(new stack_item(TOKEN_T::ELSE_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item("<3>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item("<2>"));
}

void Parser::f32() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f33() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::INT_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::INT_T));
}

void Parser::f34() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f35() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(T));
    stack1.push(new stack_item(TOKEN_T::PLUS_T));

    stack2.push(new stack_item(TOKEN_T::PLUS_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f36() {
    stack1.pop();
    stack1.push(new stack_item(U));
    stack1.push(new stack_item(T));
    stack1.push(new stack_item(TOKEN_T::MINUS_T));

    stack2.push(new stack_item(TOKEN_T::MINUS_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f37() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(H));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));

}

void Parser::f38() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::INT_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::INT_T));
}

void Parser::f39() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f40() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(F));
    stack1.push(new stack_item(TOKEN_T::MUL_T));

    stack2.push(new stack_item(TOKEN_T::MUL_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f41() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(F));
    stack1.push(new stack_item(TOKEN_T::DIV_T));

    stack2.push(new stack_item(TOKEN_T::DIV_T));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f42() {
    stack1.pop();
    stack1.push(new stack_item(V));
    stack1.push(new stack_item(TOKEN_T::NAME_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item(TOKEN_T::NAME_T));
}

void Parser::f43() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::INT_T));

    stack2.push(new stack_item(TOKEN_T::INT_T));
}

void Parser::f44() {
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::R_PR_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::L_PR_T));

    stack2.push(new stack_item());
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}

void Parser::f45()
{
    stack1.pop();
    stack1.push(new stack_item());

    stack2.push(new stack_item("<3>"));
}

void Parser::f46()
{
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));

    stack2.push(new stack_item());
}

void Parser::f47()
{
    stack1.pop();
    stack1.push(new stack_item(TOKEN_T::R_SQUARE_T));
    stack1.push(new stack_item(E));
    stack1.push(new stack_item(TOKEN_T::L_SQUARE_T));

    stack2.push(new stack_item("<i>"));
    stack2.push(new stack_item());
    stack2.push(new stack_item());
}