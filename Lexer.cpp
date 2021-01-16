#include "Lexer.h"
#include "ENUMS.h"

#define  l Lexer

const l::semf l::funcArr[19] = {
        &l::f1, &l::f2, &l::f3, &l::f4, &l::f5, &l::f6, &l::f7, &l::f8, &l::f9, &l::f10,
        &l::f11, &l::f12, &l::f13, &l::f14, &l::f15, &l::f16,& l::f17,& l::f18,& l::f19 };

const int Lexer::M[8][10] =
        {{1,  2,  3,  3,  4,  0,  -1, -2, -1, -2},
         {1,  1,  -3, -3, -1, -1, -3, -1, -1, -2},
         {5,  2,  -3, -3, -1, -1, -3, -1, -1, 6},
         {-3, -3, -3, -1, -3, -1, -3, -3, -3, -2},
         {4,  4,  4,  4,  -3, 4,  4,  4,  -2, -2},
         {5,  5,  -2, -2, -2, -2, -2, -2, -2, -2},
         {-2,  7,  -2, -2, -2, -2, -2, -2, -2, -2},
         {-2,  7,  -1, -3, -3, -3, -3, -2, -2, -2},
        };

const std::string Lexer::SW[]
        {
                "while", "if", "else", "read", "write", "int", "array","float"
        };

const char Lexer::T[] =                                     //Матрица символов
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0,    //1 - буква
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    //2 - цифра
         6, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0,10, 0,    //3 - двоеточие
         2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 9, 3, 4, 3, 7,    //4 - равно
         7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    //5 - кавычка
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 7, 7, 7,    //6 - пробел
         7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    //7 - с
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 7, 7, 7};   //8 - др
//9 - точка с запятой , 10 - точка

const int Lexer::S[8][10] =
        {
                {1,  3,  4,  4,  6,  4,  5,  7,  8,  10},
                {2,  2,  9,  9,  9,  9,  9,  9,  9,  9},
                {4,  11, 12, 12, 12, 12, 12, 12, 12,  17},
                {13, 13, 13, 14, 13, 13, 13, 13, 13,  13},
                {15, 15, 15, 15, 16, 15, 15, 15, 10,  15},
                {4,  4,  10, 10, 10, 10, 10, 10, 10,  10},
                {10,  18,  10, 10, 10, 10, 10, 10, 10,  10},
                {10,  18,  19, 19, 19, 19, 19, 19, 19,  10}
        };

int Lexer::check_sw() {
    int i = 0;
    while (i < sizeof(SW)) {
        if (st == SW[i])
            return i++;
        else
            i++;
    }
    return -1;
}

Lexer::Lexer() {
    empty = true;
    j = 0;
    s = 0;
    k = 0;
    varArr.clear();
}

Lexer::Lexer(std::string stext) {
    empty = false;
    text = stext;
    j = 0;
    s = 0;
    k = 0;
    varArr.clear();
}

void Lexer::make_token() {
    Token temp_token(st, type, lex_col, row);
    token = temp_token;
    token_ready = true;
}

Token Lexer::get_token() {
    j = 0;
    s = 0;
    k = 0;

    while (!token_ready && pos <= text.size()) {
        char ch = text[pos];

        if (ch == '\n') {
            row++;
            col = 1;            
        }

        if (ch >= 0) {
            switch (T[ch]) {
                case 0:
                    j = 7;
                    break;
                default:
                    j = T[ch];
                    break;
            }
        }

        if (s >= 0) {
            j--; //!!!! 
            k = S[s][j];
            k--;
            s = M[s][j];
        }
        switch (s) {
            case -1:
                if (k >= 0)
                    (this->*funcArr[k])(ch);
                s = 0;
                break;
            default:
                if (k >= 0)
                    (this->*funcArr[k])(ch);
                break;
        }
    }
    //col = pos - start_row;
    if (pos >= text.size())
        empty = true;

    token_ready = false;

    return token;
}

void Lexer::f1(char ch) {
    st = ch;
    pos++;
    col++;
    return;
}

void Lexer::f2(char ch) {
    st += ch;
    pos++;
    col++;
    return;
}

void Lexer::f3(char ch) {
    num = ch - '0';
    pos++;
    col++;
    return;
}

void Lexer::f4(char ch) {
    st = ch;
    pos++;
    col++;
    return;
}

void Lexer::f5(char ch) {
    switch (ch) {
        case '+':
            type = TOKEN_T::PLUS_T;
            break;
        case '-':
            type = TOKEN_T::MINUS_T;
            break;
        case '(':
            type = TOKEN_T::L_PR_T;
            break;
        case ')':
            type = TOKEN_T::R_PR_T;
            break;
        case '*':
            type = TOKEN_T::MUL_T;
            break;
        case '/':
            type = TOKEN_T::DIV_T;
            break;
        case '{':
            type = TOKEN_T::L_BRACE_T;
            break;
        case '}':
            type = TOKEN_T::R_BRACE_T;
            break;
        case '[':
            type = TOKEN_T::L_SQUARE_T;
            break;
        case ']':
            type = TOKEN_T::R_SQUARE_T;
            break;
        case ',':
            type = TOKEN_T::COMMA_T;
            break;
        case '\0':
            type = TOKEN_T::END_T;
            break;
        default:
            type = TOKEN_T::ERROR_T;
    }
    st = ch;
    lex_col = col;
    make_token();
    st = "";
    pos++;
    col++;
    return;
}

void Lexer::f6(char ch) {
    st = "";
    pos++;
    col++;
    return;
}

void Lexer::f7(char ch) {
    type = TOKEN_T::ERROR_T;
    pos++;
    col++;
    return;
}

void Lexer::f8(char ch) {
    type = TOKEN_T::END_T;
    st = ';';
    lex_col = col;
    make_token();
    st = "";
    pos++;
    col++;
    return;
}

void Lexer::f9(char ch) {
    int check = check_sw();
    if (check < 0) {
        type = TOKEN_T::NAME_T;
        varArr.push_back(st);
    } else {
        // 0 - "while", 1 - "if", 2 - "else", 3 - "read", 4 - "write", 5 - "int", 6 - "array"
        switch (check) {
            case 0:
                type = TOKEN_T::WHILE_T;
                break;
            case 1:
                type = TOKEN_T::IF_T;
                break;
            case 2:
                type = TOKEN_T::ELSE_T;
                break;
            case 3:
                type = TOKEN_T::READ_T;
                break;
            case 4:
                type = TOKEN_T::WRITE_T;
                break;
            case 5:
                type = TOKEN_T::NEWINT_T;
                break;
            case 6:
                type = TOKEN_T::NEWARRAY_T;
                break;
            case 7:
                type = TOKEN_T::NEWFLOAT_T;
                break;
            default:
                type = TOKEN_T::ERROR_T;
        }
    }
    lex_col = col - 1;
    make_token();
    st = "";
    return;
}

void Lexer::f10(char ch) {
    type = TOKEN_T::ERROR_T;
    return;
}

void Lexer::f11(char ch) {
    num = num * 10 + ch - '0';
    pos++;
    col++;
    return;
}

void Lexer::f12(char ch) {
    type = TOKEN_T::INT_T;
    st = std::to_string(num);
    lex_col = col - 1;
    make_token();
    st = "";
    num = 0;
    return;
}

void Lexer::f13(char ch) {
    switch (st[0]) {
        case '>':
            type = TOKEN_T::GREATER_T;
            break;
        case '<':
            type = TOKEN_T::LESS_T;
            break;
        case '=':
            type = TOKEN_T::ASSIGN_T;
            break;
        case '!':
            type = TOKEN_T::ERROR_T;
            break;
        default:
            type = TOKEN_T::ERROR_T;
    }
    lex_col = col-1;
    make_token();
    return;
}

void Lexer::f14(char ch) {
    switch (st[0]) {
        case '>':
            type = TOKEN_T::GOREQUAL_T;
            st = ">=";
            break;
        case '<':
            type = TOKEN_T::LOREQUAL_T;
            st = "<=";
            break;
        case '=':
            type = TOKEN_T::EQUAL_T;
            st = "==";
            break;
        case '!':
            type = TOKEN_T::NOTEQUAL_T;
            st = "!=";
            break;
        default:
            type = TOKEN_T::ERROR_T;
    }
    lex_col = col;
    make_token();
    st = "";
    pos++;
    col++;
}

void Lexer::f15(char ch) {
    st += ch;
    pos++;
    return;
}

void Lexer::f16(char ch) {
    type = TOKEN_T::ERROR_T;    // ':='
    //std::cout << st << std::endl;
    lex_col = col;
    make_token();
    pos++;
    col++;
    st = "";
    return;
}

void Lexer::f17(char ch) {
    d = 1;
    x = num;
    pos++;
    col++;
    return;
}
void Lexer::f18(char ch) {
    d *= 0.1; 
    x += (ch - '0')*d;
    pos++;
    col++;
    return;
}
void Lexer::f19(char ch) {
    type = TOKEN_T::FLOAT_T;
    st = std::to_string(x);
    lex_col = col - 1;
    make_token();
    st = "";
    num = 0; d = 0; x = 0;
    return;
}