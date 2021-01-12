// Alfa_Kostyuque.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include<stdio.h>
#include <ctype.h> 
using namespace std;

#define BSIZE	15						//������ ������
#define NONE	-1						//������ ������
#define EOS		'\0'					//����� ������
#define NUM		256						//�����
#define ID		257						//����������
#define ARRAY	258						//������
#define IF		259
#define THEN	260
#define ELSE	261
#define WHILE	262
#define DO		263
#define READ	264
#define WRITE	265
#define INT		266						//������������� ��� ����������
#define INTM	267  					//������������� ��� �������
#define INDEX	268						//����� ������� ��� ���
#define METKAJF	269						//����� �������� �� "����" ��� ���
#define METKAJ	270						//����� ������������ �������� ��� ���
#define DONE	271						//����� �����


#define STRMAX	999						/* ������ ������� ������ */
#define SYMMAX	100						/* ������ ������� �������� */
char lexemes[STRMAX];					//������ ������

//������� ������������ �����������, ������ ������������� ��������
int LexTable[3][22] = { { 0,  2, 18,  4,  5,  6,  7,  8,  9, 20, 17, 10, 11, 12, 13, 26, 27, 28, 19, 24, 14, 29 },
{ 1, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 23, 19, 25 ,15, 15 },
{ 21, 3, 16, 23, 16, 16, 16, 16, 16, 23, 16, 23, 16, 16, 16, 16, 23, 23, 19, 22 ,16, 23 } };

//������� ���������, �� ASCI-���� ������� �������� ����� ������� � LexTable
int T[126] = { 18, 18, 18, 18, 18, 18, 18, 18, 18,  2,		//9
			   19, 18, 18, 18, 18, 18, 18, 18, 18, 18,		//19
			   18, 18, 18, 18, 18, 18, 18, 18, 18, 18,		//29
			   18, 18,  2, 18, 18, 18,  3, 18, 20, 18,		//39
			   11, 12,  6,  7, 21,  8, 15,  5,  1,  1,		//49
				1,  1,  1,  1,  1,  1,  1,  1, 18, 18,		//59
			   13,  4, 14, 18, 18,  0,  0,  0,  0,  0,		//69
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,		//79
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,		//89
				0,  9, 18, 10, 18, 18, 18,  0,  0,  0,		//99
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,		//109
				0,	0,  0,  0,  0,  0,  0,  0,  0,  0,		//119
				0,  0,  0, 16, 18, 17 };					//125

//���� ��������� � ���
enum OPSType
{
	IDE, MAS,				/*���������� ��� ������*/
	NUMBER,					/*�����*/
	SIGN,					/*��������*/
	POINT,					/*����� ��������*/
	IND,					/*����������*/
	METJF,					/*����� ��� "����"*/
	METJ,					/*����� ��� ������������ ��������*/
	RE,						/*����� ������*/
	WR						/*����� ������*/
};

/*�������� �����*/
struct ProcElem
{
	int value; OPSType type;
};

//����� stack
const int SIZE = 500;
class stack
{
	ProcElem stck[SIZE];
	int tos;
public:
	stack();
	~stack();
	void push(ProcElem i);
	ProcElem pop();
};

stack::stack()
{
	tos = 0;
	cout << "Stack Initialized\n";
}

stack::~stack()
{
	cout << "Stack Destroyed\n";
}

void stack::push(ProcElem i)
{
	if (tos == SIZE) {
		cout << "Stack is full. \n";
		return;
	}
	stck[tos] = i;
	tos++;
}

ProcElem stack::pop()
{
	if (tos == 0) {
		cout << "Stack underflow.\n";
	}
	tos--;
	return stck[tos];
}

//����� ������������� ���������
int sp;

//������� ���
struct OPSStruct
{
	char* elem; OPSType type;
};

/* ������ � ������� �������� � ������� ���������� */
struct entry { char* lexptr; int token; };

/*������ � ������� ��������*/
struct entry1 { char* masptr; int* mas; };
struct ElMas { int mas; int elem; };

//������� �������� ����
entry keywords[] = {
	"if", IF,
	"then", THEN,
	"else", ELSE,
	"while", WHILE,
	"read", READ,
	"write", WRITE,
	"integ",  INT,
	"mass", INTM,
	"do", DO,
	0, 0 };

entry symtable[SYMMAX];					/* ������� �������� */
entry number[SYMMAX];					/*���������� � �� ��������*/
entry1 massiv[SYMMAX];					/*������� � �� ����������*/
ElMas passport[SYMMAX];
OPSStruct OPSmas[9999];					/*������������ ���*/
int OPScounter = 0;						/*������� ��������� � ���*/
int lastchar = -1;						/* ��������� �������������� ������� � lexemes */
int lastentry = 0;						/* ��������� �������������� ������� � ������� �������� */
int lookahead;							//��� �������
char * ProgText;						//����� ���������
int k = -1;								//����� ������������� �������
int ss = -1;							//����� ������ � ������ ���������
int es = -1;							//���������
char lexbuf[BSIZE];						//����� �������
int lineno = 1;							//����� ������
int tokenval = NONE;
int x = 10;								//���������� ����� �������� � ��� 

int lexan();
void emit(int t, int tval);				//����� ���
void match(int t);						//��������� � ���������� ������
void factor();
void term();
void expr();
void megaexpr();
void name();
void expr1();
void prim();
void megafactor();
void cond();
void comp();
void parse();							//�������������� ����������
int lookup(char s[]);
int insert(char s[], int tok);
void setSize();							//������������� ������ �������
void OPSProc();							//������� ���


/* �������� �������� ���� � ������� �������� */
void init()
{
	entry *p;
	for (p = keywords; p->token; p++)
		insert(p->lexptr, p->token);
}

/* ���������� ��������� � ������� �������� ��� s */
int lookup(char s[])
{
	int p;
	for (p = lastentry; p > 0; p--)
		if (strcmp(symtable[p].lexptr, s) == 0)
			return p;
	return 0;
}

/*��������� ����� ������� � ���������� ��������� � ������� �������� ��� s */
int insert(char s[], int tok)
{
	int len;
	len = strlen(s);											/*��������� ����� ������ */
	if (lastentry + 1 >= SYMMAX)								/*������ ����������*/
	{
		cout << "symbol table full";
		exit(0);
	}
	if (lastchar + len + 1 >= STRMAX)							/*������ ������ ����������*/
	{
		cout << "lexemes array full";
		exit(0);
	}
	lastentry++;												//��������� � ��������� ������ � ������� ��������
	symtable[lastentry].token = tok;							//������������� �����, ����������� �������� �����
	symtable[lastentry].lexptr = &lexemes[lastchar + 1];		//����� ������ ������� � ������� ������
	if (tok == ID)
		number[lastentry].lexptr = &lexemes[lastchar + 1];
	if (tok == ARRAY)
		massiv[lastentry].masptr = &lexemes[lastchar + 1];
	lastchar = lastchar + len + 1;								//��������� ��������� ������� � ������� ������
	strcpy(symtable[lastentry].lexptr, s);						//��������� ������ ������
	return lastentry;
}

/*������ ���������� ������� ������*/
char getsym()
{
	ss++;
	k++;
	return ProgText[k];
}


/*����������� ����������*/
int lexan()
{
	int t, b, d;
	/*��������� �� ����� ��������� ��������:
	0 - ���������
	1, 2 - �������������
	3 - ���������� ��������
	4 - ��������� ��������	*/
	int state = 0;
	bool error = 0;
	while ((!error) || (state < 3))
	{
		t = getsym();
		sp = LexTable[state][T[t]];
		switch (sp) {
			//������ �������
		case 0:
			state = 1;
			b = 0;
			lexbuf[b] = t;
			b++;
			break;
			//���������� �������
		case 1:
			state = 1;
			lexbuf[b] = t;
			b++;
			break;
			//������ �����
		case 2:
			state = 2;
			tokenval = t - '0';
			break;
			//���������� �����
		case 3:
			state = 2;
			tokenval = tokenval * 10 + t - '0';
			break;
			//  ->
		case 4:
			//  =
		case 5:
			//  /
		case 6:
			//  *
		case 7:
			//  +
		case 8:
			//  -
		case 9:
			//  (
		case 10:
			//  )
		case 11:
			//  <
		case 12:
			//  >
		case 13:
			//  ]
		case 17:
			// [
		case 20:
			//  .
		case 26:
			//  {
		case 27:
			//  }
		case 28:
			// ,
		case 29:
			state = 3;
			tokenval = NONE;
			return t;
			break;
			//����� �����
		case 14:
			state = 3;
			return DONE;
			break;
			// ���
		case 15:
			state = 3;
			lexbuf[b] = EOS;
			if (t != '&')
			{
				k--;
				ss--;
			}
			d = lookup(lexbuf);					//����� ����� � ������� ��������
			if (d == 0)
			{
				if (t == '[')
					d = insert(lexbuf, ARRAY);
				else
					d = insert(lexbuf, ID);
			}
			tokenval = d;
			return symtable[d].token;
			break;
			// ���������
		case 16:
			state = 3;
			k--;
			ss--;
			return NUM;
			break;
			//������� �������
		case 18:
			state = 0;
			break;
			//�� ������ �����
		case 19:
			state = 4;
			error = 1;
			tokenval = NONE;
			return t;
			break;
			//�������� �������
		case 21:
			state = 4;
			cout << "Wrong lexem";
			error = 1;
			break;
			//���������, ������� �� ����� ������
		case 22:
			state = 3;
			return NUM;
			break;
			//������ ������
		case 23:
			state = 4;
			cout << "Wrong expr";
			error = 1;
			break;
			//������� �� ����� ������
		case 24:
			state = 0;
			lineno++;
			ss = -1;
			break;
			//  ���, ������� �� ����� ������
		case 25:
			state = 3;
			lineno++;
			ss = -1;
			lexbuf[b] = EOS;
			if (t != '&')
			{
				k--;
				ss--;
			}
			d = lookup(lexbuf);					//����� ����� � ������� ��������
			if (d == 0)
			{
				if (t == '[')
					d = insert(lexbuf, ARRAY);
				else
					d = insert(lexbuf, ID);
			}
			tokenval = d;
			return symtable[d].token;
			break;
		}
	}
}

//���������� � ����� ��� � �������
void emit(int t, int tval)
{
	OPSmas[OPScounter].elem = new char[x];
	switch (t)
	{
	case '+':
		OPSmas[OPScounter].elem = "+";
		OPSmas[OPScounter].type = SIGN;
		OPScounter++;
		cout << (char)t << '\n';
		break;
	case '-':
		OPSmas[OPScounter].elem = "-";
		OPSmas[OPScounter].type = SIGN;
		OPScounter++;
		cout << (char)t << '\n';
		break;
	case '*':
		OPSmas[OPScounter].elem = "*";
		OPSmas[OPScounter].type = SIGN;
		OPScounter++;
		cout << (char)t << '\n';
		break;
	case '/':
		OPSmas[OPScounter].elem = "/";
		OPSmas[OPScounter].type = SIGN;
		OPScounter++;
		cout << (char)t << '\n';
		break;
	case '$':
		OPSmas[OPScounter].elem = "$";
		OPSmas[OPScounter].type = SIGN;
		OPScounter++;
		cout << (char)t << '\n';
		break;
	case '>':
		OPSmas[OPScounter].elem = ">";
		OPSmas[OPScounter].type = SIGN;
		OPScounter++;
		cout << (char)t << '\n';
		break;
	case '<':
		OPSmas[OPScounter].elem = "<";
		OPSmas[OPScounter].type = SIGN;
		OPScounter++;
		cout << (char)t << '\n';
		break;
	case '=':
		OPSmas[OPScounter].elem = "=";
		OPSmas[OPScounter].type = SIGN;
		OPScounter++;
		cout << (char)t << '\n';
		break;
	case NUM:
		itoa(tval, OPSmas[OPScounter].elem, 10);
		OPSmas[OPScounter].type = NUMBER;
		OPScounter++;
		cout << tval << '\n';
		break;
	case ARRAY:
		OPSmas[OPScounter].elem = symtable[tval].lexptr;
		OPSmas[OPScounter].type = MAS;
		OPScounter++;
		cout << symtable[tval].lexptr << '\n';
		break;
	case ID:
		OPSmas[OPScounter].elem = symtable[tval].lexptr;
		OPSmas[OPScounter].type = IDE;
		OPScounter++;
		cout << symtable[tval].lexptr << '\n';
		break;
	case INDEX:
		OPSmas[OPScounter].elem = "<i>";
		OPSmas[OPScounter].type = IND;
		OPScounter++;
		cout << "<i>" << '\n';
		break;
	case METKAJF:
		OPSmas[OPScounter].elem = "<jf>";
		OPSmas[OPScounter].type = METJF;
		OPScounter++;
		cout << "<jf>" << '\n';
		break;
	case METKAJ:
		OPSmas[OPScounter].elem = "<j>";
		OPSmas[OPScounter].type = METJ;
		OPScounter++;
		cout << "<j>" << '\n';
		break;
	case READ:
		OPSmas[OPScounter].elem = "<r>";
		OPSmas[OPScounter].type = RE;
		OPScounter++;
		cout << "<r>" << '\n';
		break;
	case WRITE:
		OPSmas[OPScounter].elem = "<w>";
		OPSmas[OPScounter].type = WR;
		OPScounter++;
		cout << "<w>" << '\n';
		break;
	default:
		cout << '\n';
	}
}

//������� � ��������� ������� 
void match(int t)
{
	if (lookahead == t)
		lookahead = lexan();
	else
	{
		cout << "ERROR match 1 " << "line: " << lineno << "  symbol: " << ss << '\n';
	}
}
//���� ������


void setSize()
{
	if (lookahead == NUM)
		massiv[lastentry].mas = new int[tokenval];
}

//��������� chista
void comp()
{
	switch (lookahead)
	{
		int t;
	case '=':case '>':case'<':
		t = lookahead;
		match(t);
		expr();
		emit(t, NONE);
		break;
	default:
		cout << "error comp";
	}
}

//
void cond()
{
	switch (lookahead)
	{
	case NUM:
		emit(NUM, tokenval);
		match(NUM);
		prim();
		term();
		comp();
		break;
	case ID:
		emit(ID, tokenval);
		match(ID);
		prim();
		term();
		comp();
		break;
	case ARRAY:
		emit(ARRAY, tokenval);
		match(ARRAY);
		match('[');
		expr();
		match(']');
		emit(INDEX, 0);
		prim();
		term();
		comp();
		break;
	case '(':
		match('(');
		expr();
		match(')');
		prim();
		term();
		comp();
		break;
	default:
		cout << "syntax ERROR cond 2" << '\n';
		cout << "line = " << lineno << "  symbol = " << es;
		//	int w;
		//	cin >> w;
	}
}

void factor()
{
	switch (lookahead)
	{
	case NUM:
		emit(NUM, tokenval);
		match(NUM);
		break;
	case ID:
		emit(ID, tokenval);
		match(ID);
		break;
	case ARRAY:
		emit(ARRAY, tokenval);
		match(ARRAY);
		match('[');
		expr();
		match(']');
		emit(INDEX, 0);
		break;
	case '(':
		match('(');
		expr();
		match(')');
		break;
	default:
		cout << "syntax ERROR factor 3" << '\n';
		cout << "line = " << lineno << "  symbol = " << es;
		int w;
		cin >> w;
	}
}

void prim()
{
	switch (lookahead)
	{
		int t;
	case '*':case '/':
		t = lookahead;
		match(lookahead);
		factor();
		prim();
		emit(t, NONE);
		break;
	default:
		return;
	}
}

void megafactor() //ne vhodit
{
	switch (lookahead)
	{
	case NUM:
		emit(NUM, tokenval);
		match(NUM);
		prim();
		break;
	case ID:
		emit(ID, tokenval);
		match(ID);
		prim();
		break;
	case ARRAY:
		emit(ARRAY, tokenval);
		match(ARRAY);
		match('[');
		expr();
		match(']');
		emit(INDEX, 0);
		prim();
		break;
	case '(':
		match('(');
		expr();
		match(')');
		prim();
		break;
	default:
		cout << "syntax ERROR mega factor 4" << '\n';
		cout << "line = " << lineno << "  symbol = " << es;
		int w;
		cin >> w;
	}
}

void term()
{
	switch (lookahead)
	{
		int t;
	case '+': case '-':
		t = lookahead;
		match(t);
		megafactor();
		term();
		emit(t, NONE);
		break;
	default:
		return;
	}
}


void expr()
{
	switch (lookahead)
	{
	case NUM:
		emit(NUM, tokenval);
		match(NUM);
		prim();
		term();
		break;
	case ID:
		emit(ID, tokenval);
		match(ID);
		prim();
		term();
		break;
	case ARRAY:
		emit(ARRAY, tokenval);
		match(ARRAY);
		match('[');
		expr();
		match(']');
		emit(INDEX, 0);
		prim();
		term();
		break;
	case '(':
		match('(');
		expr();
		match(')');
		prim();
		term();
		break;
	default:
		cout << "syntax ERROR 5" << '\n';
		cout << "line = " << lineno << "  symbol = " << es;
		int w;
		cin >> w;
	}
}

void expr1()
{
	int pointJF, pointJ;
	switch (lookahead)
	{
	case ID:
		emit(ID, tokenval);
		match(ID);
		match('$');
		expr();
		emit('$', NONE);
		break;
	case ARRAY:
		emit(ARRAY, tokenval);
		match(ARRAY);
		match('[');
		expr();
		match(']');
		emit(INDEX, 0);
		match('$');
		expr();
		emit('$', NONE);
		break;
	case IF:
		match(IF);
		match('(');
		cond();
		match(')');
		pointJF = OPScounter;									//����� ��� ������� ������ � ���
		OPScounter++;
		match(THEN);
		emit(METKAJF, 0);
		expr1();
		switch (lookahead)
		{
		case ELSE:
			match(ELSE);
			pointJ = OPScounter;								//����� ��� ������� ������ � ���
			OPScounter++;										//� ���������� �������� � ���
			emit(METKAJ, 0);									//������� <j> � ��� 
			OPSmas[pointJF].elem = new char[x];
			itoa(OPScounter, OPSmas[pointJF].elem, 10);			//����� �������� ��� <jf>
			OPSmas[pointJ].type = OPSmas[pointJF].type = POINT;
			expr1();
			OPSmas[pointJ].elem = new char[x];
			itoa(OPScounter, OPSmas[pointJ].elem, 10);
			break;
		default:
			OPSmas[pointJF].elem = new char[x];
			itoa(OPScounter, OPSmas[pointJF].elem, 10);
			OPSmas[pointJF].type = POINT;
		}
		break;
	case WHILE:
		match(WHILE);
		match('(');
		pointJ = OPScounter;									//����� �������� ��� <j>
		cond();													//�������
		match(')');
		pointJF = OPScounter;									//����� ��� ������� ������ � ���
		OPScounter++;											//� ���������� �������� � ���
		match(DO);
		emit(METKAJF, 0);										//������� <jf> � ��� 
		expr1();
		OPSmas[OPScounter].elem = new char[x];
		itoa(pointJ, OPSmas[OPScounter].elem, 10);
		OPSmas[OPScounter].type = OPSmas[pointJF].type = POINT;
		OPScounter++;
		emit(METKAJ, 0);										//������� <j> � ��� 
		OPSmas[pointJF].elem = new char[x];
		itoa(OPScounter, OPSmas[pointJF].elem, 10);
		break;
	case '{':
		match('{');
		megaexpr();
		match('}');
		break;
	case READ:
		match(READ);
		match('(');
		switch (lookahead)
		{
		case ID:
			emit(ID, tokenval);
			match(ID);
			break;
		case ARRAY:
			emit(ARRAY, tokenval);
			match(ARRAY);
			match('[');
			expr();
			match(']');
			emit(INDEX, 0);
			break;
		default:
			cout << "error read(?)";
		}
		match(')');
		emit(READ, 0);
		break;
	case WRITE:
		match(WRITE);
		match('(');
		expr();
		match(')');
		emit(WRITE, 0);
		break;
	default:
		cout << "syntax ERROR uu" << '\n';
		cout << "line = " << lineno << "  symbol = " << es;
		int w;
		cin >> w;
	}
}

void megaexpr()
{
	int pointJF, pointJ;
	switch (lookahead)
	{
	case ID:
		emit(ID, tokenval);
		match(ID);
		match('$');
		expr();
		emit('$', NONE);
		match('.');
		megaexpr();
		break;
	case ARRAY:
		emit(ARRAY, tokenval);
		match(ARRAY);
		match('[');
		expr();
		match(']');
		emit(INDEX, 0);
		match('$');
		expr();
		emit('$', NONE);
		match('.');
		megaexpr();
		break;
	case IF:
		match(IF);
		match('(');
		cond();
		match(')');
		pointJF = OPScounter;									//����� ��� ������� ������ � ���
		OPScounter++;
		match(THEN);
		emit(METKAJF, 0);
		expr1();
		switch (lookahead)
		{
		case ELSE:
			match(ELSE);
			pointJ = OPScounter;								//����� ��� ������� ������ � ���
			OPScounter++;										//� ���������� �������� � ���
			emit(METKAJ, 0);									//������� <j> � ��� 
			OPSmas[pointJF].elem = new char[x];
			itoa(OPScounter, OPSmas[pointJF].elem, 10);			//����� �������� ��� <jf>
			OPSmas[pointJ].type = OPSmas[pointJF].type = POINT;
			expr1();
			OPSmas[pointJ].elem = new char[x];
			itoa(OPScounter, OPSmas[pointJ].elem, 10);
			break;
		default:
			OPSmas[pointJF].elem = new char[x];
			itoa(OPScounter, OPSmas[pointJF].elem, 10);
			OPSmas[pointJF].type = POINT;
		}
		match('.');
		megaexpr();
		break;
	case WHILE:
		match(WHILE);
		match('(');
		pointJ = OPScounter;									//����� �������� ��� <j>
		cond();													//�������
		match(')');
		pointJF = OPScounter;									//����� ��� ������� ������ � ���
		OPScounter++;											//� ���������� �������� � ���
		match(DO);
		emit(METKAJF, 0);										//������� <jf> � ��� 
		expr1();
		OPSmas[OPScounter].elem = new char[x];
		itoa(pointJ, OPSmas[OPScounter].elem, 10);
		OPSmas[OPScounter].type = OPSmas[pointJF].type = POINT;
		OPScounter++;
		emit(METKAJ, 0);										//������� <j> � ��� 
		OPSmas[pointJF].elem = new char[x];
		itoa(OPScounter, OPSmas[pointJF].elem, 10);
		match('.');
		megaexpr();
		break;
	case READ:
		match(READ);
		match('(');
		switch (lookahead)
		{
		case ID:
			emit(ID, tokenval);
			match(ID);
			break;
		case ARRAY:
			emit(ARRAY, tokenval);
			match(ARRAY);
			match('[');
			expr();
			match(']');
			emit(INDEX, 0);
			break;
		default:
			cout << "error read(?) 6";
		}
		match(')');
		emit(READ, 0);
		match('.');
		megaexpr();
		break;
	case WRITE:
		match(WRITE);
		match('(');
		expr();
		match(')');
		emit(WRITE, 0);
		match('.');
		megaexpr();
		break;
	default:
		return;
	}
}

void name()
{
	switch (lookahead)
	{
	case ID:
		match(ID);
		while (lookahead != '.')
		{
			match(',');
			match(ID);
		}
		break;
	case ARRAY:
		match(ARRAY);
		match('[');
		setSize();
		match(NUM);
		match(']');
		while (lookahead != '.')
		{
			match(',');
			match(ARRAY);
			match('[');
			setSize();
			match(NUM);
			match(']');
		}
		break;
	default:
		cout << "syntax ERROR. ������ � �������� ����������." << '\n';
		return;
	}
}

//�������������� ����������
void parse()
{
	if (lookahead != DONE)
		switch (lookahead)
		{
		case INT:
			match(INT);
			name();
			match('.');
			parse();
			break;
		case INTM:
			match(INTM);
			name();
			match('.');
			parse();
			break;
		default:
			megaexpr();
		}
	return;
}

void OPSProc()
{
	int len = OPScounter;
	int z = 0, d, res, ps = 0;
	char t;
	stack st;
	ProcElem element;
	ProcElem element1;
	while (z < len)
	{
		switch (OPSmas[z].type)
		{
		case IDE:
			d = lookup(OPSmas[z].elem);				//�� ����� ������� � ������� ���������� �������� ����������
			element.value = d;						//�������
			element.type = IDE;						//���
			st.push(element);						//�������� � ����
			z++;									//��������� � ��������� ��������
			break;

		case NUMBER:
			element.value = atoi(OPSmas[z].elem);
			element.type = NUMBER;
			st.push(element);						//�������� � ����
			z++;									//��������� � c��������� ��������
			break;

		case MAS:
			d = lookup(OPSmas[z].elem);				//�� ����� ������� � ������� �������� �������� ������
			element.value = d;						//�������
			element.type = MAS;						//���
			st.push(element);						//�������� � ����
			z++;									//��������� � ��������� ��������
			break;

		case IND:
			element = st.pop();						//������ ��������
			element1 = st.pop();					//������
			switch (element.type)
			{
			case IDE:
				passport[ps].elem = number[element.value].token;
				break;
			case NUMBER:
				passport[ps].elem = element.value;
				break;
			default:
				break;
			};
			passport[ps].mas = element1.value;
			element.value = ps;
			ps++;
			element.type = MAS;
			st.push(element);
			z++;
			break;

		case SIGN:
			t = OPSmas[z].elem[0];
			switch (t)
			{
			case '$':
				element = st.pop();					//������ ��������
				element1 = st.pop();				//����� ��������
				switch (element1.type)
				{
				case IDE:
					switch (element.type)
					{
					case IDE:
						number[element1.value].token = number[element.value].token;
						break;
					case MAS:
						number[element1.value].token = massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						number[element1.value].token = element.value;
						break;
					default:
						break;
					}
					break;
				case MAS:
					switch (element.type)
					{
					case IDE:
						massiv[passport[element1.value].mas].mas[passport[element1.value].elem] = number[element.value].token;
						break;
					case MAS:
						massiv[passport[element1.value].mas].mas[passport[element1.value].elem] = massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						massiv[passport[element1.value].mas].mas[passport[element1.value].elem] = element.value;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				z++;
				break;
			case '+':
				element = st.pop();					//������ ��������
				element1 = st.pop();				//����� ��������
				switch (element1.type)
				{
				case IDE:
					switch (element.type)
					{
					case IDE:
						res = number[element1.value].token + number[element.value].token;
						break;
					case MAS:
						res = number[element1.value].token + massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						res = number[element1.value].token + element.value;
						break;
					default:
						break;
					}
					break;
				case MAS:
					switch (element.type)
					{
					case IDE:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] + number[element.value].token;
						break;
					case MAS:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] + massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] + element.value;
						break;
					default:
						break;
					}
					break;
				case NUMBER:
					switch (element.type)
					{
					case IDE:
						res = element1.value + number[element.value].token;
						break;
					case NUMBER:
						res = element1.value + element.value;
						break;
					case MAS:
						res = massiv[passport[element.value].mas].mas[passport[element.value].elem] + element1.value;
						break;
					default:
						break;
					}
					break;
				}
				element.value = res;
				element.type = NUMBER;
				st.push(element);
				z++;
				break;
			case '-':
				element = st.pop();					//������ ��������
				element1 = st.pop();				//����� ��������
				switch (element1.type)
				{
				case IDE:
					switch (element.type)
					{
					case IDE:
						res = number[element1.value].token - number[element.value].token;
						break;
					case MAS:
						res = number[element1.value].token - massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						res = number[element1.value].token - element.value;
						break;
					default:
						break;
					}
					break;
				case MAS:
					switch (element.type)
					{
					case IDE:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] - number[element.value].token;
						break;
					case MAS:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] - massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] - element.value;
						break;
					default:
						break;
					}
					break;
				case NUMBER:
					switch (element.type)
					{
					case IDE:
						res = element1.value - number[element.value].token;
						break;
					case NUMBER:
						res = element1.value - element.value;
						break;
					case MAS:
						res = massiv[passport[element.value].mas].mas[passport[element.value].elem] - element1.value;
						break;
					default:
						break;
					}
					break;
				}
				element.value = res;
				element.type = NUMBER;
				st.push(element);
				z++;
				break;
			case'*':
				element = st.pop();					//������ ��������
				element1 = st.pop();				//����� ��������
				switch (element1.type)
				{
				case IDE:
					switch (element.type)
					{
					case IDE:
						res = number[element1.value].token * number[element.value].token;
						break;
					case MAS:
						res = number[element1.value].token * massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						res = number[element1.value].token * element.value;
						break;
					default:
						break;
					}
					break;
				case MAS:
					switch (element.type)
					{
					case IDE:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] * number[element.value].token;
						break;
					case MAS:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] * massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] * element.value;
						break;
					default:
						break;
					}
					break;
				case NUMBER:
					switch (element.type)
					{
					case IDE:
						res = element1.value * number[element.value].token;
						break;
					case NUMBER:
						res = element1.value * element.value;
						break;
					case MAS:
						res = massiv[passport[element.value].mas].mas[passport[element.value].elem] * element1.value;
						break;
					default:
						break;
					}
					break;
				}

				element.value = res;
				element.type = NUMBER;
				st.push(element);
				z++;
				break;
			case '/':
				element = st.pop();						//������ ��������
				element1 = st.pop();					//����� ��������
				switch (element1.type)
				{
				case IDE:
					switch (element.type)
					{
					case IDE:
						res = number[element1.value].token / number[element.value].token;
						break;
					case MAS:
						res = number[element1.value].token / massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						res = number[element1.value].token / element.value;
						break;
					default:
						break;
					}
					break;
				case MAS:
					switch (element.type)
					{
					case IDE:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] / number[element.value].token;
						break;
					case MAS:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] / massiv[passport[element.value].mas].mas[passport[element.value].elem];
						break;
					case NUMBER:
						res = massiv[passport[element1.value].mas].mas[passport[element1.value].elem] / element.value;
						break;
					default:
						break;
					}
					break;
				case NUMBER:
					switch (element.type)
					{
					case IDE:
						res = element1.value / number[element.value].token;
						break;
					case NUMBER:
						res = element1.value / element.value;
						break;
					case MAS:
						res = massiv[passport[element.value].mas].mas[passport[element.value].elem] / element1.value;
						break;
					default:
						break;
					}
					break;
				}
				element.value = res;
				element.type = NUMBER;
				st.push(element);
				z++;
				break;
			case '>':
				element = st.pop();					//������ ��������
				element1 = st.pop();				//����� ��������
				res = 0;
				switch (element1.type)
				{
				case IDE:
					switch (element.type)
					{
					case IDE:
						if (number[element1.value].token > number[element.value].token)
							res = 1;
						break;
					case MAS:
						if (number[element1.value].token > massiv[passport[element.value].mas].mas[passport[element.value].elem])
							res = 1;
						break;
					case NUMBER:
						if (number[element1.value].token > element.value)
							res = 1;
						break;
					default:
						break;
					}
					break;
				case MAS:
					switch (element.type)
					{
					case IDE:
						if (massiv[passport[element1.value].mas].mas[passport[element1.value].elem] > number[element.value].token)
							res = 1;
						break;
					case MAS:
						if (massiv[passport[element1.value].mas].mas[passport[element1.value].elem] > massiv[passport[element.value].mas].mas[passport[element.value].elem])
							res = 1;
						break;
					case NUMBER:
						if (massiv[passport[element1.value].mas].mas[passport[element1.value].elem] > element.value)
							res = 1;
						break;
					default:
						break;
					}
					break;
				case NUMBER:
					switch (element.type)
					{
					case IDE:
						if (element1.value > number[element.value].token)
							res = 1;
						break;
					case NUMBER:
						if (element1.value > element.value)
							res = 1;
						break;
					case MAS:
						if (massiv[passport[element.value].mas].mas[passport[element.value].elem] < element1.value)
							res = 1;
						break;
					default:
						break;
					}
					break;
				}
				element.value = res;
				element.type = NUMBER;
				st.push(element);
				z++;
				break;
			case '<':
				element = st.pop();				//������ ��������
				element1 = st.pop();			//����� ��������
				res = 0;
				switch (element1.type)
				{
				case IDE:
					switch (element.type)
					{
					case IDE:
						if (number[element1.value].token < number[element.value].token)
							res = 1;
						break;
					case MAS:
						if (number[element1.value].token < massiv[passport[element.value].mas].mas[passport[element.value].elem])
							res = 1;
						break;
					case NUMBER:
						if (number[element1.value].token < element.value)
							res = 1;
						break;
					default:
						break;
					}
					break;
				case MAS:
					switch (element.type)
					{
					case IDE:
						if (massiv[passport[element1.value].mas].mas[passport[element1.value].elem] < number[element.value].token)
							res = 1;
						break;
					case MAS:
						if (massiv[passport[element1.value].mas].mas[passport[element1.value].elem] < massiv[passport[element.value].mas].mas[passport[element.value].elem])
							res = 1;
						break;
					case NUMBER:
						if (massiv[passport[element1.value].mas].mas[passport[element1.value].elem] < element.value)
							res = 1;
						break;
					default:
						break;
					}
					break;
				case NUMBER:
					switch (element.type)
					{
					case IDE:
						if (element1.value < number[element.value].token)
							res = 1;
						break;
					case NUMBER:
						if (element1.value < element.value)
							res = 1;
						break;
					case MAS:
						if (massiv[passport[element.value].mas].mas[passport[element.value].elem] > element1.value)
							res = 1;
						break;
					default:
						break;
					}
					break;
				}
				element.value = res;
				element.type = NUMBER;
				st.push(element);
				z++;
				break;
			case '=':
				element = st.pop();				//������ ��������
				element1 = st.pop();			//����� ��������
				res = 0;
				switch (element1.type)
				{
				case IDE:
					switch (element.type)
					{
					case IDE:
						if (number[element1.value].token == number[element.value].token)
							res = 1;
						break;
					case MAS:
						if (number[element1.value].token == massiv[passport[element.value].mas].mas[passport[element.value].elem])
							res = 1;
						break;
					case NUMBER:
						if (number[element1.value].token == element.value)
							res = 1;
						break;
					default:
						break;
					}
					break;
				case MAS:
					switch (element.type)
					{
					case IDE:
						if (massiv[passport[element1.value].mas].mas[passport[element1.value].elem] == number[element.value].token)
							res = 1;
						break;
					case MAS:
						if (massiv[passport[element1.value].mas].mas[passport[element1.value].elem] == massiv[passport[element.value].mas].mas[passport[element.value].elem])
							res = 1;
						break;
					case NUMBER:
						if (massiv[passport[element1.value].mas].mas[passport[element1.value].elem] == element.value)
							res = 1;
						break;
					default:
						break;
					}
					break;
				case NUMBER:
					switch (element.type)
					{
					case IDE:
						if (element1.value == number[element.value].token)
							res = 1;
						break;
					case NUMBER:
						if (element1.value == element.value)
							res = 1;
						break;
					case MAS:
						if (massiv[passport[element.value].mas].mas[passport[element.value].elem] == element1.value)
							res = 1;
						break;
					default:
						break;
					}
					break;
				}
				element.value = res;
				element.type = NUMBER;
				st.push(element);
				z++;
				break;
			default:
				break;
			}
			break;

		case POINT:
			d = atoi(OPSmas[z].elem);
			z++;
			if (OPSmas[z].type == METJF)
			{
				element = st.pop();
				if (element.value == 1)
					z++;
				else z = d;
			};
			if (OPSmas[z].type == METJ)
				z = d;
			break;

		case WR:
			element = st.pop();
			switch (element.type)
			{
			case IDE:
				z--;
				d = lookup(OPSmas[z].elem);
				cout << number[d].token << '\n';
				z = z + 2;
				break;
			case NUMBER:
				cout << element.value << '\n';
				z++;
				break;
			case MAS:
				cout << massiv[passport[element.value].mas].mas[passport[element.value].elem] << '\n';
				z++;
				break;
			default:
				break;
			}
			break;
		case RE:
			element = st.pop();
			switch (element.type)
			{
			case IDE:
				z--;
				d = lookup(OPSmas[z].elem);
				cout << "??";
				cin >> number[d].token;
				cout << '\n';
				z = z + 2;
				break;
			case MAS:
				cout << "??";
				cin >> massiv[passport[element.value].mas].mas[passport[element.value].elem];
				cout << '\n';
				z++;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])

{
	char * fileName = "target1.txt";			//��� ��������� �����, ���������������� ���������
	FILE *fp;								//����
	int fileSize;							//������ �����
	fp = fopen(fileName, "rt");				//�������� �����
	fseek(fp, 0, SEEK_END);					//����� ����� �����
	fileSize = ftell(fp);					//������ �����
	ProgText = new char[fileSize];			//�������� ������� ��� ������ ���������
	fseek(fp, 0, SEEK_SET);					//��������� ��������� �� ������ �����
	int i = 0;
	while (!feof(fp))						//���� �� �������� ����� �����
	{
		ProgText[i] = getc(fp);				//��������� ������
		i++;
	}
	i--;
	ProgText[i] = '&';						//�������� ������ - ������������
	fclose(fp);								//�������� �����
	init();									//����������  ������� ��������� �������
	lookahead = lexan();
	parse();
	OPSmas[OPScounter].elem = new char[2];
	OPSmas[OPScounter].elem = "&";
	OPSmas[OPScounter].type = SIGN;
	int f;
	for (f = 0; f < OPScounter + 1; f++)
		cout << OPSmas[f].elem << "  ";
	OPSProc();
	cin >> f;
	system("PAUSE");
	return 0;
}