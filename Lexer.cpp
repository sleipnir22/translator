#include "Lexer.h"
#define  l Lexer

const l::semf l::funcArr[16] = { 
    &l::f1,&l::f2,&l::f3,&l::f4,&l::f5,&l::f6,&l::f7,&l::f8,&l::f9,&l::f10,&l::f11,&l::f12,&l::f13,&l::f14,&l::f15,&l::f16 };			// ������ ������������� �������

const int Lexer::M[6][9] =          //M������ ���������
{   {1,2,3,-1,4,0,-1,-2,-1},        //O - -2 (����. ������. ���������)
    {1,1,-1,-1,-1,-1,-1,-1,-1},     //F - -1 (�������. ������. ���������)
    {5,2,-1,-1,-1,-1,-1,-1,-1},     //S -  0 (���. ���������)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1},   //I -  1
    {4,4,4,4,-1,4,4,4,-2},          //C -  2
    {5,5,-2,-2,-2,-2,-2,-2,-2}      //A -  3 , T - 4 , D - 5
};

const string Lexer::SW[]
{ 
    "for","while","if","end","begin","then", "else" 
};

const char Lexer::T[] =                    //������� ��������
{ 0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,  //1 - ����� 
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //2 - �����
6,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,    //3 - ���������
2,2,2,2,2,2,2,2,2,2,3,9,7,4,7,7,    //4 - �����
7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    //5 - �������
1,1,1,1,1,1,1,1,1,1,1,7,7,7,7,7,    //6 - ������
7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    //7 - �
1,1,1,1,1,1,1,1,1,1,1,7,7,7,7,7 };

<<<<<<< Updated upstream
const int Lexer::S[6][9] =                 //������� �������
=======
//1. st:=C[i]; i:=i+1; //Начало имени или служебного слова.
//2. st:=st+C[i]; i:=i+1; //Продолжение имени или служебного слова.
//3. x:=ord(C[i])-ord(’0’); i:=i+1; //Начало числа.
//4. i:=i+1;            //Пропуск символа входной строки.
//5. typ:=ord(C[i]); i:=i+1; //Распознан символ языка.
//6. st:=’’; i:=i+1; //Начало строки символов.
//7. typ:=-1; i:=i+1; //Ошибочный символ входной строки.
//8. typ:=0;          //Концевой символ входной строки.
//9. . . .  //Сравнение st с таблицей служебных слов. При совпадении typ содержит номер служебного слова +100, при несовпадении – число 1.
//10. typ:=-1;        //Ошибка во входной строке.
//11. x:=x*10+ord(C[i])-ord(’0’); i:=i+1; //Продолжение числа.
//12. typ:=2;          //Распознано число.
//13. typ:=ord(’:’);   //Распознан символ «:».
//14. typ:=11; i:=i+1; //Распознан символ «:=».
//15. st:=st+C[i]; i:=i+1; //Продолжение строки символов.
//16. typ:=3; i:=i+1;  //Распознана строка символов.


const int Lexer::S[6][9] =                 //Ìàòðèöà ôóíêöèé
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
    if (pos == text.size() + 1) empty = true;
>>>>>>> Stashed changes

    
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
    cout << "��������� ������ ����� '" << ch << "'" << endl;
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
    cout << "��������� ��������� ������ '" << ch << "'" << endl;
    pos++;
    return;
}
void Lexer::f8(char ch)
{
    type = 0;
    cout << "��������� �������� ������ ������� ������\n";
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
<<<<<<< Updated upstream

        cout << "���������� ��� " << st << endl;
=======
        //varArr.push_back(st);
        cout <<  st << endl;
>>>>>>> Stashed changes
    }
    else
    {
        type = check + 100;

<<<<<<< Updated upstream
        cout << "���������� ��������� ����� " << st << endl;
=======
        cout <<  st << " ";
>>>>>>> Stashed changes
    }
    make_token();
    st = "";
    return;
}
void Lexer::f10(char ch)
{
    type = -1;
    cout << "������ �� ������� ������!" << endl;
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
    varArr.push_back(num);
    st = to_string(num);
<<<<<<< Updated upstream
    cout << "���������� ����� " << num << endl;
=======
    cout <<  num << " ";
>>>>>>> Stashed changes
    make_token();
    st = "";
    num = 0;
    return;
}
void Lexer::f13(char ch)
{
    type = ch;
<<<<<<< Updated upstream
    cout << "��������� ������ ':'" << endl;
=======
    cout << "':' ";
>>>>>>> Stashed changes
    return;
}
void Lexer::f14(char ch)
{
    type = 11;
<<<<<<< Updated upstream
    cout << "��������� ������ ':='" << endl;
=======
    cout << "':=' ";
>>>>>>> Stashed changes
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
    cout << "���������� ������ " << st << endl;
    make_token();
    st = "";
    return;
}
