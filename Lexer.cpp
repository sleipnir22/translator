#include "Lexer.h"
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

const string Lexer::SW[]
{
    "for","while","if","end","begin","then", "else"
};

const char Lexer::T[] =                    //Ìàòðèöà ñèìâîëîâ
{ 0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,  //1 - áóêâà 
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //2 - öèôðà
6,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,    //3 - äâîåòî÷èå
2,2,2,2,2,2,2,2,2,2,3,9,7,4,7,7,    //4 - ðàâíî
7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    //5 - êàâû÷êà
1,1,1,1,1,1,1,1,1,1,1,7,7,7,7,7,    //6 - ïðîáåë
7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    //7 - ñ
1,1,1,1,1,1,1,1,1,1,1,7,7,7,7,7 };

const int Lexer::S[6][9] =                 //Ìàòðèöà ôóíêöèé
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

Lexer::Lexer(string stext)
{
    empty = false;
    this->text = stext;
    j = 0;
    s = 0;
    k = 0;
    varArr.clear();
}

void Lexer::make_token()
{
    Token temp_token(st, type);
    token = temp_token;
    token_ready = true;
}

Token Lexer::get_token()
{
    while (!token_ready && pos < text.size())
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
    if (pos+10 == text.size()) empty = true;

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
    type = ch;
    cout << "'" <<  ch << "'" << endl;
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
    cout << "'" <<  ch << "'" << endl;
    pos++;
    return;
}
void Lexer::f8(char ch)
{
    type = 0;
    //cout << "Ðàñïîçíàí êîíöåâîé ñèìâîë âõîäíîé ñòðîêè\n";
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
        varArr.push_back(st);
        cout <<  st << endl;
    }
    else
    {
        type = check + 100;

        cout <<  st << endl;
    }
    make_token();
    st = "";
    return;
}
void Lexer::f10(char ch)
{
    type = -1;
    //cout << "Îøèáêà âî âõîäíîé ñòðîêå!" << endl;
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
    cout <<  num << endl;
    make_token();
    st = "";
    num = 0;
    return;
}
void Lexer::f13(char ch)
{
    type = ch;
    cout << "':'" << endl;
    return;
}
void Lexer::f14(char ch)
{
    type = 11;
    cout << "':='" << endl;
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
    cout << st << endl;
    make_token();
    st = "";
    return;
}