#include "Lexer.h"
#define  l Lexer

const l::semf l::funcArr[16] = { 
    &l::f1,&l::f2,&l::f3,&l::f4,&l::f5,&l::f6,&l::f7,&l::f8,&l::f9,&l::f10,&l::f11,&l::f12,&l::f13,&l::f14,&l::f15,&l::f16 };			// Массив семантических функций

const int Lexer::M[6][9] =          //Mатрица состояний
{   {1,2,3,-1,4,0,-1,-2,-1},        //O - -2 (Ошиб. заключ. состояние)
    {1,1,-1,-1,-1,-1,-1,-1,-1},     //F - -1 (Правиль. заключ. состояние)
    {5,2,-1,-1,-1,-1,-1,-1,-1},     //S -  0 (Нач. состояние)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1},   //I -  1
    {4,4,4,4,-1,4,4,4,-2},          //C -  2
    {5,5,-2,-2,-2,-2,-2,-2,-2}      //A -  3 , T - 4 , D - 5
};

const string Lexer::SW[]
{ 
    "for","while","if","end","begin","then", "else" 
};

const char Lexer::T[] =                    //Матрица символов
{ 0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,  //1 - буква 
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //2 - цифра
6,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,    //3 - двоеточие
2,2,2,2,2,2,2,2,2,2,3,9,7,4,7,7,    //4 - равно
7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    //5 - кавычка
1,1,1,1,1,1,1,1,1,1,1,7,7,7,7,7,    //6 - пробел
7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    //7 - с
1,1,1,1,1,1,1,1,1,1,1,7,7,7,7,7 };

const int Lexer::S[6][9] =                 //Матрица функций
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

Lexer::Lexer(string text)
{
    this->text = text;
}

void Lexer::make_token()
{
    Token* temp_token = new Token(st, type);
    tokens.push_back(*temp_token);
}

vector<Token> Lexer::get_tokens()
{
    int j = 0, s = 0, k = 0;
    while (pos < text.size())
    {
        char ch = text[pos];
        if (T[ch] && ch >= 0 && ch < 128)
            j = T[ch];
        else 
            j = 7;
        if (s >= 0)
        {
            j--;
            k = S[s][j];
            k--;
            s = M[s][j];
        }
        if (s >= -1 && k >= 0)
        {
            (this->*funcArr[k])(ch);
            if (s == -1)
                s = 0;
        }
    }

    
    return tokens;
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
    type = ch;
    cout << "Распознан символ языка '" << ch << "'" << endl;
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
    type = -1;
    cout << "Распознан ошибочный символ '" << ch << "'" << endl;
    pos++;
    return;
}
void Lexer::f8(char ch)
{
    type = 0;
    cout << "Распознан концевой символ входной строки\n";
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
        type = 1;

        cout << "Распознано имя " << st << endl;
    }
    else
    {
        type = check + 100;

        cout << "Распознано служебное слово " << st << endl;
    }
    make_token();
    st = "";
    return;
}
void Lexer::f10(char ch)
{
    type = -1;
    cout << "Ошибка во входной строке!" << endl;
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
    type = 2;
    st = to_string(num);
    cout << "Распознано число " << num << endl;
    make_token();
    st = "";
    num = 0;
    return;
}
void Lexer::f13(char ch)
{
    type = ch;
    cout << "Распознан символ ':'" << endl;
    return;
}
void Lexer::f14(char ch)
{
    type = 11;
    cout << "Распознан символ ':='" << endl;
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
    type = 3;
    pos++;
    cout << "Распознана строка " << st << endl;
    make_token();
    st = "";
    return;
}
