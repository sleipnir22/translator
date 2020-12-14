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

<<<<<<< Updated upstream
const int Lexer::S[6][9] =                 //Матрица функций
=======
//1. st:=C[i]; i:=i+1; //РќР°С‡Р°Р»Рѕ РёРјРµРЅРё РёР»Рё СЃР»СѓР¶РµР±РЅРѕРіРѕ СЃР»РѕРІР°.
//2. st:=st+C[i]; i:=i+1; //РџСЂРѕРґРѕР»Р¶РµРЅРёРµ РёРјРµРЅРё РёР»Рё СЃР»СѓР¶РµР±РЅРѕРіРѕ СЃР»РѕРІР°.
//3. x:=ord(C[i])-ord(вЂ™0вЂ™); i:=i+1; //РќР°С‡Р°Р»Рѕ С‡РёСЃР»Р°.
//4. i:=i+1;            //РџСЂРѕРїСѓСЃРє СЃРёРјРІРѕР»Р° РІС…РѕРґРЅРѕР№ СЃС‚СЂРѕРєРё.
//5. typ:=ord(C[i]); i:=i+1; //Р Р°СЃРїРѕР·РЅР°РЅ СЃРёРјРІРѕР» СЏР·С‹РєР°.
//6. st:=вЂ™вЂ™; i:=i+1; //РќР°С‡Р°Р»Рѕ СЃС‚СЂРѕРєРё СЃРёРјРІРѕР»РѕРІ.
//7. typ:=-1; i:=i+1; //РћС€РёР±РѕС‡РЅС‹Р№ СЃРёРјРІРѕР» РІС…РѕРґРЅРѕР№ СЃС‚СЂРѕРєРё.
//8. typ:=0;          //РљРѕРЅС†РµРІРѕР№ СЃРёРјРІРѕР» РІС…РѕРґРЅРѕР№ СЃС‚СЂРѕРєРё.
//9. . . .  //РЎСЂР°РІРЅРµРЅРёРµ st СЃ С‚Р°Р±Р»РёС†РµР№ СЃР»СѓР¶РµР±РЅС‹С… СЃР»РѕРІ. РџСЂРё СЃРѕРІРїР°РґРµРЅРёРё typ СЃРѕРґРµСЂР¶РёС‚ РЅРѕРјРµСЂ СЃР»СѓР¶РµР±РЅРѕРіРѕ СЃР»РѕРІР° +100, РїСЂРё РЅРµСЃРѕРІРїР°РґРµРЅРёРё вЂ“ С‡РёСЃР»Рѕ 1.
//10. typ:=-1;        //РћС€РёР±РєР° РІРѕ РІС…РѕРґРЅРѕР№ СЃС‚СЂРѕРєРµ.
//11. x:=x*10+ord(C[i])-ord(вЂ™0вЂ™); i:=i+1; //РџСЂРѕРґРѕР»Р¶РµРЅРёРµ С‡РёСЃР»Р°.
//12. typ:=2;          //Р Р°СЃРїРѕР·РЅР°РЅРѕ С‡РёСЃР»Рѕ.
//13. typ:=ord(вЂ™:вЂ™);   //Р Р°СЃРїРѕР·РЅР°РЅ СЃРёРјРІРѕР» В«:В».
//14. typ:=11; i:=i+1; //Р Р°СЃРїРѕР·РЅР°РЅ СЃРёРјРІРѕР» В«:=В».
//15. st:=st+C[i]; i:=i+1; //РџСЂРѕРґРѕР»Р¶РµРЅРёРµ СЃС‚СЂРѕРєРё СЃРёРјРІРѕР»РѕРІ.
//16. typ:=3; i:=i+1;  //Р Р°СЃРїРѕР·РЅР°РЅР° СЃС‚СЂРѕРєР° СЃРёРјРІРѕР»РѕРІ.


const int Lexer::S[6][9] =                 //ГЊГ ГІГ°ГЁГ¶Г  ГґГіГ­ГЄГ¶ГЁГ©
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
<<<<<<< Updated upstream

        cout << "Распознано имя " << st << endl;
=======
        //varArr.push_back(st);
        cout <<  st << endl;
>>>>>>> Stashed changes
    }
    else
    {
        type = check + 100;

<<<<<<< Updated upstream
        cout << "Распознано служебное слово " << st << endl;
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
    varArr.push_back(num);
    st = to_string(num);
<<<<<<< Updated upstream
    cout << "Распознано число " << num << endl;
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
    cout << "Распознан символ ':'" << endl;
=======
    cout << "':' ";
>>>>>>> Stashed changes
    return;
}
void Lexer::f14(char ch)
{
    type = 11;
<<<<<<< Updated upstream
    cout << "Распознан символ ':='" << endl;
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
    cout << "Распознана строка " << st << endl;
    make_token();
    st = "";
    return;
}
