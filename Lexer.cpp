#include "Lexer.h"
#include "ENUMS.h"
#define  l Lexer

const l::semf l::funcArr[16] = {
    &l::f1,&l::f2,&l::f3,&l::f4,&l::f5,&l::f6,&l::f7,&l::f8,&l::f9,&l::f10,&l::f11,&l::f12,&l::f13,&l::f14,&l::f15,&l::f16 };			// Ìàññèâ ñåìàíòè÷åñêèõ ôóíêöèé

const int Lexer::M[6][9] =          //Màòðèöà ñîñòîÿíèé
{ {1,2,3,-1,4,0,-1,-2,-1},        //O - -2 (Îøèá. çàêëþ÷. ñîñòîÿíèå)
    {1,1,-1,-1,-1,-1,-1,-1,-1},     //F - -1 (Ïðàâèëü. çàêëþ÷. ñîñòîÿíèå)
    {5,2,-1,-1,-1,-1,-1,-1,-1},     //S -  0 (Íà÷. ñîñòîÿíèå)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1},   //I -  1
    {4,4,4,4,-1,4,4,4,-2},          //C -  2
    {5,5,-2,-2,-2,-2,-2,-2,-2}      //A -  3 , T - 4 , D - 5
};

const std::string Lexer::SW[]
{
    "for","while","if", "{","}" ,"then", "else"
};

const char Lexer::T[] =                    //Матрица символов
{ 0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,  //1 - буква 
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //2 - цифра
6,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,    //3 - двоеточие
2,2,2,2,2,2,2,2,2,2,3,9,7,4,7,7,    //4 - равно
7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    //5 - кавычка
1,1,1,1,1,1,1,1,1,1,1,7,7,7,7,7,    //6 - пробел
7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    //7 - с
1,1,1,1,1,1,1,1,1,1,1,7,7,7,7,7 };   //8 - др
                                    //9 - точка с запятой , 10 - перевод строки

const int Lexer::S[6][9] =                 
{
    {1,3,4,5,6,4,5,7,8},
    {2,2,9,9,9,9,9,9,9},
    {4,11,12,12,12,12,12,12,12},
    {13,13,13,14,13,13,13,13,13},
    {15,15,15,15,16,15,15,15,10},
    {4,4,10,10,10,10,10,10,10}
};

int Lexer::check_sw()
{
    int i = 0;
    while (i < sizeof(SW))
    {
        if (st == SW[i])
            return ++i;
        else
            i++;
    }
    return -1;
}

Lexer::Lexer()
{
    empty = true;
    j = 0;
    s = 0;
    k = 0;
    varArr.clear();
}

Lexer::Lexer(std::string stext)
{
    empty = false;
    text = stext;
    j = 0;
    s = 0;
    k = 0;
    varArr.clear();
}

void Lexer::make_token()
{   
    Token temp_token(st, type, M_type, col,row);
    token = temp_token;
    token_ready = true;
    std::cout << "lexema " << st << " type " << type << std::endl;
}

Token Lexer::get_token()
{
    j = 0;
    s = 0;
    k = 0;

    while (!token_ready && pos < text.size())
    {
        char ch = text[pos];

        if (ch == '\n')
        {
            row++;
            start_row = pos;
        }
        if (ch >= 0)
        {
            switch (T[ch])
            {
            case 0:
                    j = 7;
                break;
            default:
                    j = T[ch];
                break;
            }
        }

        if (s >= 0)
        {
            j--; //!!!! 
            k = S[s][j];
            k--;
            s = M[s][j];
        }

        switch (s)
        {
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
    col = pos - start_row;
    if (pos >= text.size()) 
        empty = true;

    token_ready = false;

    return token;
}
void Lexer::f1(char ch)
{
    st = ch;
    pos++;
    return;
}
void Lexer::f2(char ch)
{
    st += ch;
    pos++;
    return;
}
void Lexer::f3(char ch)
{
    num = ch - '0';
    pos++;
    return;
}
void Lexer::f4(char ch)
{
    pos++;
    return;
}
void Lexer::f5(char ch)
{
    switch (ch)
    {
    case '=' :
        type = TOKEN_T::EQUALS_T;
        M_type = TOKEN_T_M::EQUALS_T;
        break;
    case '+':
        type = TOKEN_T::PLUS_T;
        M_type = TOKEN_T_M::PLUS_T;
        break;
    case '-':
        type = TOKEN_T::MINUS_T;
        M_type = TOKEN_T_M::MINUS_T;
        break;
    case '(':
        type = TOKEN_T::L_PR_T;
        M_type = TOKEN_T_M::L_PR_T;
        break;
    case ')':
        type = TOKEN_T::R_PR_T;
        M_type = TOKEN_T_M::R_PR_T;
        break;
    case '*':
        type = TOKEN_T::MUL_T;
        M_type = TOKEN_T_M::MUL_T;
        break;
    case '/':
        type = TOKEN_T::DIV_T;
        M_type = TOKEN_T_M::DIV_T;
        break;
    default:
        type = TOKEN_T::ERROR_T;
        M_type = TOKEN_T_M::ERROR_T;
    }
    st = ch;
    make_token();
    st = "";
    pos++;
    return;
}
void Lexer::f6(char ch)
{
    st = "";
    pos++;
    return;
}
void Lexer::f7(char ch)
{
    type = TOKEN_T::ERROR_T;
    M_type = TOKEN_T_M::ERROR_T;
    pos++;
    return;
}
void Lexer::f8(char ch)
{
    type = TOKEN_T::END_T;
    M_type = TOKEN_T_M::END_T;
    st = ';';
    make_token();
    st = ' ';
    pos++;
    return;
}
void Lexer::f9(char ch)
{
    int check = check_sw();
    if (check < 0)
    {
        type = NAME_T;
        M_type = TOKEN_T_M::NAME_T;
        varArr.push_back(st);
    }
    else
    {
        //type = check + 100; / switch!!!
    }
    make_token();
    st = "";
    return;
}
void Lexer::f10(char ch)
{
    type = TOKEN_T::ERROR_T;
    M_type = TOKEN_T_M::ERROR_T;
    return;
}
void Lexer::f11(char ch)
{
    num = num * 10 + ch - '0';
    pos++;
    return;
}
void Lexer::f12(char ch)
{
    type = TOKEN_T::INT_T;
    M_type = TOKEN_T_M::INT_T;
    st = std::to_string(num);
    make_token();
    st = "";
    num = 0;
    return;
}
void Lexer::f13(char ch)
{
    type = TOKEN_T::ERROR_T;    // ':' - двоеточие
    M_type = TOKEN_T_M::ERROR_T;
    return;
}
void Lexer::f14(char ch) 
{
    type = TOKEN_T::ERROR_T;    // ':=' 
    M_type = TOKEN_T_M::ERROR_T;
    st = ":=";
    make_token();
    st = "";
    pos++;
}
void Lexer::f15(char ch)
{
    st += ch;
    pos++;
    return;
}
void Lexer::f16(char ch)
{
    type = TOKEN_T::ERROR_T;    // ':=' 
    M_type = TOKEN_T_M::ERROR_T;
    pos++;
    std::cout << st << std::endl;
    make_token();
    st = "";
    return;
}
