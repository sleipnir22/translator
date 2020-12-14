#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Token.h"
#include <stack>
using namespace std;
class Lexer
{
<<<<<<< Updated upstream
	typedef void (Lexer::*semf)(char);
	static const semf funcArr[16];
	static const string SW[];				//служебные слова;
	static const int M[6][9];				//Mатрица состояний
	static const char T[];					//Матрица символов
	static const int S[6][9];
	vector <Token> tokens;
	int pos = 0;							//– номер очередного символа входного текста;
	int num = 0;							//– распознанное целое число;
	string st;								//– накопленная строка символов или имя;
	int type;
	string text;
	int check_sw();
	void make_token();						//make_token() не во всех семантических функциях. Исправить!!!

public:
	void f1(char), f2(char), f3(char), f4(char), f5(char), f6(char), f7(char), f8(char), f9(char), f10(char), f11(char), f12(char), f13(char), f14(char), f15(char), f16(char);
	Lexer(string text);
	vector<Token> get_tokens();
};



=======
    typedef void (Lexer::* semf)(char);
    static const semf funcArr[16];
    static const string SW[];				//Г±Г«ГіГ¦ГҐГЎГ­Г»ГҐ Г±Г«Г®ГўГ ;
    static const int M[6][9];				//MГ ГІГ°ГЁГ¶Г  Г±Г®Г±ГІГ®ГїГ­ГЁГ©
    static const char T[];					//ГЊГ ГІГ°ГЁГ¶Г  Г±ГЁГ¬ГўГ®Г«Г®Гў
    static const int S[6][9];
    int j , s , k ;
    Token token;
    int pos = 0;							//вЂ“ Г­Г®Г¬ГҐГ° Г®Г·ГҐГ°ГҐГ¤Г­Г®ГЈГ® Г±ГЁГ¬ГўГ®Г«Г  ГўГµГ®Г¤Г­Г®ГЈГ® ГІГҐГЄГ±ГІГ ;
    int num = 0;							//вЂ“ Г°Г Г±ГЇГ®Г§Г­Г Г­Г­Г®ГҐ Г¶ГҐГ«Г®ГҐ Г·ГЁГ±Г«Г®;
    string st;								//вЂ“ Г­Г ГЄГ®ГЇГ«ГҐГ­Г­Г Гї Г±ГІГ°Г®ГЄГ  Г±ГЁГ¬ГўГ®Г«Г®Гў ГЁГ«ГЁ ГЁГ¬Гї;
    int type;
    string text;
    int check_sw();
    void make_token();						//make_token() Г­ГҐ ГўГ® ГўГ±ГҐГµ Г±ГҐГ¬Г Г­ГІГЁГ·ГҐГ±ГЄГЁГµ ГґГіГ­ГЄГ¶ГЁГїГµ. Г€Г±ГЇГ°Г ГўГЁГІГј!!!
    bool empty = true;
    bool token_ready = false;
    vector<int> varArr;
public:
    void f1(char), f2(char), f3(char), f4(char), f5(char), f6(char), f7(char), f8(char), f9(char), f10(char), f11(char), f12(char), f13(char), f14(char), f15(char), f16(char);
    Lexer();
    Lexer(string text);
    Token get_token();
    vector<int> get_varArr() { return varArr; };
    bool is_empty() { return empty; }
};
>>>>>>> Stashed changes
