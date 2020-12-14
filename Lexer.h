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
	static const string SW[];				//��������� �����;
	static const int M[6][9];				//M������ ���������
	static const char T[];					//������� ��������
	static const int S[6][9];
	vector <Token> tokens;
	int pos = 0;							//� ����� ���������� ������� �������� ������;
	int num = 0;							//� ������������ ����� �����;
	string st;								//� ����������� ������ �������� ��� ���;
	int type;
	string text;
	int check_sw();
	void make_token();						//make_token() �� �� ���� ������������� ��������. ���������!!!

public:
	void f1(char), f2(char), f3(char), f4(char), f5(char), f6(char), f7(char), f8(char), f9(char), f10(char), f11(char), f12(char), f13(char), f14(char), f15(char), f16(char);
	Lexer(string text);
	vector<Token> get_tokens();
};



=======
    typedef void (Lexer::* semf)(char);
    static const semf funcArr[16];
    static const string SW[];				//ñëóæåáíûå ñëîâà;
    static const int M[6][9];				//Màòðèöà ñîñòîÿíèé
    static const char T[];					//Ìàòðèöà ñèìâîëîâ
    static const int S[6][9];
    int j , s , k ;
    Token token;
    int pos = 0;							//– íîìåð î÷åðåäíîãî ñèìâîëà âõîäíîãî òåêñòà;
    int num = 0;							//– ðàñïîçíàííîå öåëîå ÷èñëî;
    string st;								//– íàêîïëåííàÿ ñòðîêà ñèìâîëîâ èëè èìÿ;
    int type;
    string text;
    int check_sw();
    void make_token();						//make_token() íå âî âñåõ ñåìàíòè÷åñêèõ ôóíêöèÿõ. Èñïðàâèòü!!!
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
