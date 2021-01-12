// Alfa_Kostyuque.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include<stdio.h>
#include <ctype.h> 
#include "settings.h"
using namespace std;

//������� ������������ �����������, ������ ������������� ��������
//						  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  
//						  �   �   t   #   =   /   *   +   -   [   ]   (   )   <   >   .   {   }	  D   P   &   
int Lexeme_table[3][21] = { { 0,  2, 18,  4,  5,  6,  7,  8,  9, 20, 17, 10, 11, 12, 13, 26, 27, 28, 19, 24, 14 },
						{ 1, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 23, 19, 25 ,15 },
						{ 21, 3, 16, 23, 16, 16, 16, 16, 16, 23, 16, 23, 16, 16, 16, 16, 23, 23, 19, 22 ,16 } };
	
//������� ���������, �� ASCI-���� ������� �������� ����� ������� � Lexeme_table
int ASCII_table[126] = { 18, 18, 18, 18, 18, 18, 18, 18, 18,  2,		//9
			   19, 18, 18, 18, 18, 18, 18, 18, 18, 18,		//19
			   18, 18, 18, 18, 18, 18, 18, 18, 18, 18,		//29
			   18, 18,  2, 18, 18,  3, 18, 18, 20, 18,		//39
			   11, 12,  6,  7, 18,  8, 18,  5,  1,  1,		//49
				1,  1,  1,  1,  1,  1,  1,  1, 18, 15,		//59
			   13,  4, 14, 18, 18,  0,  0,  0,  0,  0,		//69
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,		//79
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,		//89
				0,  9, 18, 10, 18, 18, 18,  0,  0,  0,		//99
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,		//109
				0,	0,  0,  0,  0,  0,  0,  0,  0,  0,		//119
				0,  0,  0, 16, 18, 17 };					//125

//����� ������������� ���������
int semantic_program;

//���� ��������� � ���
enum type_OPS
{
	VAR, 
	MASSIVE,				/*���������� ��� ������*/
	NUMBER,					/*�����*/
	OPERATION,					/*��������*/
	JUMP_POINT,					/*����� ��������*/
	INDEXATOR,					/*����������*/
	JUMP_FALSE,					/*����� ��� "����"*/
	JUMP,					/*����� ��� ������������ ��������*/
	CREAD,						/*����� ������*/
	CWRITE						/*����� ������*/
};

/*�������� �����*/
struct ProcElem
{
	int value; type_OPS type;
};

//����� stack

class stack
{
	ProcElem stck[SIZE];
	int tos;
public:
	stack()
	{
		tos = 0;
		cout << "\nInitialized stack\n";
	}
	~stack()
	{
		cout << "\nDestroyed stack\n";
	}
	void push(ProcElem i)
	{
		if (tos == SIZE) {
			cout << "Stack is full. \n";
			return;
		}
		stck[tos] = i;
		tos++;
	}
	ProcElem pop()
	{
		if (tos == 0) {
			cout << "Stack underflow.\n";
		}
		tos--;
		return stck[tos];
	}
};

//������� ���
struct struct_OPS
{
	char* elem; type_OPS type;
};

/* ������ � ������� �������� � ������� ���������� */
struct entry { char* lexptr; int token; };

/*������ � ������� ��������*/
struct entry_mas { char* masptr; int* mas; };
struct entry_passport { int mas; int elem; };

//������� �������� ����
entry keywords[] = {
	"if", IF,
	"else", ELSE,
	"while", WHILE,
	"read", READ,
	"write", WRITE,
	"integer",  INT,
	"do", DO,
	0, 0 };

entry symbol_table[SYMMAX];					// ������� �������� 
entry number[SYMMAX];					// ���������� � �� ��������
entry_mas massiv[SYMMAX];					// ������� � �� ����������
entry_passport passport[SYMMAX];
struct_OPS generate_OPS[9999];				// ������������ ���
int cnt_OPS = 0;						// ������� ��������� � ���*
int lastchar = -1;						// ��������� �������������� ������� � lexemes 
int lastentry = 0;						// ��������� �������������� ������� � ������� �������� 
int current_lexeme;					//	��� �������
char * ProgText;						//	����� ���������
int k = -1;								//	����� ������������� �������
int ss = -1;							//	����� ������ � ������ ���������
int es = -1;							//	���������
char lexeme_buffer[BSIZE];				//	����� �������
int lineno = 1;							//	����� ������
int lexeme_val = NONE;					//	�������� �������
int x = 10;								//  ���������� ����� �������� � ��� 

int lexical_analyzer();					// ����������� ����������

void print_ops(int t, int tval);		// ����� ���
void next_lexeme(int t);				// ��������� � ��������� �������
void setSize();							// ������������� ������ �������
int search_symbol_table(char s[]);					// ���������� ��������� � ������� �������� ��� s 
int insert_symbol_table(char s[], int tok);			// ��������� ����� ������� � ���������� ��������� � ������� �������� ��� s

void terminal_a(int type);				// �������� �

void syntax_analyzer();					// A - ��������� ���������� - �������������� ����������
void name();							// B - ���
void program_line();					// S - ����������� ������
void value();							// Y - ��������
void term();							// U - ��������� 
void math_expression();					// Q - �������������� ���������
void residual_term();					// L - ���������� ��������� 
void multiplier();						// M - ��������� 
void conditional_expression();			// D - �������� ���������
void comparison();						// J - ���������
void OPS_Interpreter();					// �������������� ���


/* �������� �������� ���� � ������� �������� */
void load_keywords()
{
	entry *p;
	for (p = keywords; p->token; p++) insert_symbol_table(p->lexptr, p->token);
}

/* ���������� ��������� � ������� �������� ��� s */
int search_symbol_table(char s[])
{
	int p;
	for (p = lastentry; p > 0; p--) 
		if (strcmp(symbol_table[p].lexptr, s) == 0) return p;
	return 0;
}

/*��������� ����� ������� � ���������� ��������� � ������� �������� ��� s */
int insert_symbol_table(char s[], int tok)
{
	int len;
	len = strlen(s);											/*��������� ����� ������ */
	if (lastentry + 1 >= SYMMAX)								/*������ ����������*/
		{ cout << "symbol table full"; exit(0); }
	if (lastchar + len + 1 >= STRMAX)							/*������ ������ ����������*/
		{ cout << "lexemes array full"; exit(0); }
	lastentry++;												//��������� � ��������� ������ � ������� ��������
	symbol_table[lastentry].token = tok;							//������������� �����, ����������� �������� �����
	symbol_table[lastentry].lexptr = &lexemes[lastchar + 1];		//����� ������ ������� � ������� ������
	if (tok == ID) number[lastentry].lexptr = &lexemes[lastchar + 1];
	if (tok == ARRAY) massiv[lastentry].masptr = &lexemes[lastchar + 1];
	lastchar = lastchar + len + 1;								//��������� ��������� ������� � ������� ������
	strcpy(symbol_table[lastentry].lexptr, s);						//��������� ������ ������
	return lastentry;
}

/*������ ���������� ������� ������*/
char get_symbol() { ss++; k++; return ProgText[k]; }

/*����������� ����������
  ��������� �� ����� ��������� ��������:
  0 - ���������
  1, 2 - �������������
  3 - ���������� ��������
  4 - ��������� ��������	*/
int lexical_analyzer()
{
	int t, b, d;
	int state = 0;
	bool error = 0;
	while ((!error) || (state < 3))
	{
		t = get_symbol();
		semantic_program = Lexeme_table[state][ASCII_table[t]];
		switch (semantic_program) {
		case 0: //������ �������
			state = 1;
			b = 0;
			lexeme_buffer[b] = t;
			b++;
			break;

		case 1: //���������� �������
			state = 1;
			lexeme_buffer[b] = t;
			b++;
			break;

		case 2: //������ �����
			state = 2;
			lexeme_val = t - '0';
			break;

		case 3: //���������� �����
			state = 2;
			lexeme_val = lexeme_val * 10 + t - '0';
			break;

		case 4: //  #
		case 5: //  =
		case 6: //  /
		case 7: //  *
		case 8: //  +
		case 9: //  -
		case 10: //  (
		case 11: //  )
		case 12: //  <
		case 13: //  >
		case 17: //  ]
		case 20: // [
		case 26: //  ;
		case 27: //  {
		case 28: //  }
			state = 3;
			lexeme_val = NONE;
			return t;
			break;

		case 14: //����� �����
			state = 3;
			return DONE;
			break;

		case 25: //  ���, ������� �� ����� ������
			state = 3;
			lineno++;
			ss = -1;
		case 15: // ���
			state = 3; lexeme_buffer[b] = EOS;
			if (t != '&') { k--; ss--; }
			d = search_symbol_table(lexeme_buffer);					//����� ����� � ������� ��������
			if (d == 0) {
				if (t == '[') d = insert_symbol_table(lexeme_buffer, ARRAY);
				else d = insert_symbol_table(lexeme_buffer, ID);
			}
			lexeme_val = d;
			return symbol_table[d].token;
			break;
		
		case 16: // ���������
			state = 3; k--; ss--;
			return NUM;
			break;
			 
		case 18: //������� �������
			state = 0;
			break;
			 
		case 19: //�� ������ �����
			state = 4;
			error = 1;
			lexeme_val = NONE;
			return t;
			break;

		case 21: //�������� �������
			state = 4;
			cout << "Wrong lexem";
			error = 1;
			break;

		case 22: //���������, ������� �� ����� ������
			state = 3;
			return NUM;
			break;
			
		case 23: //������ ������
			state = 4;
			cout << "Wrong expr";
			error = 1;
			break;
			
		case 24: //������� �� ����� ������
			state = 0;
			lineno++;
			ss = -1;
			break;
		}
	}
}

//���������� � ����� ��� � �������
void print_ops(int t, int tval)
{
	generate_OPS[cnt_OPS].elem = new char[x];
	switch (t)
	{
	case '+':
		generate_OPS[cnt_OPS].elem = "+";
		generate_OPS[cnt_OPS].type = OPERATION;
		cnt_OPS++;
		cout << (char)t << '\n';
		break;
	case '-':
		generate_OPS[cnt_OPS].elem = "-";
		generate_OPS[cnt_OPS].type = OPERATION;
		cnt_OPS++;
		cout << (char)t << '\n';
		break;
	case '*':
		generate_OPS[cnt_OPS].elem = "*";
		generate_OPS[cnt_OPS].type = OPERATION;
		cnt_OPS++;
		cout << (char)t << '\n';
		break;
	case '/':
		generate_OPS[cnt_OPS].elem = "/";
		generate_OPS[cnt_OPS].type = OPERATION;
		cnt_OPS++;
		cout << (char)t << '\n';
		break;
	case '#':
		generate_OPS[cnt_OPS].elem = "#";
		generate_OPS[cnt_OPS].type = OPERATION;
		cnt_OPS++;
		cout << (char)t << '\n';
		break;
	case '>':
		generate_OPS[cnt_OPS].elem = ">";
		generate_OPS[cnt_OPS].type = OPERATION;
		cnt_OPS++;
		cout << (char)t << '\n';
		break;
	case '<':
		generate_OPS[cnt_OPS].elem = "<";
		generate_OPS[cnt_OPS].type = OPERATION;
		cnt_OPS++;
		cout << (char)t << '\n';
		break;
	case '=':
		generate_OPS[cnt_OPS].elem = "=";
		generate_OPS[cnt_OPS].type = OPERATION;
		cnt_OPS++;
		cout << (char)t << '\n';
		break;
	case NUM:
		itoa(tval, generate_OPS[cnt_OPS].elem, 10);
		generate_OPS[cnt_OPS].type = NUMBER;
		cnt_OPS++;
		cout << tval << '\n';
		break;
	case ARRAY:
		generate_OPS[cnt_OPS].elem = symbol_table[tval].lexptr;
		generate_OPS[cnt_OPS].type = MASSIVE;
		cnt_OPS++;
		cout << symbol_table[tval].lexptr << '\n';
		break;
	case ID:
		generate_OPS[cnt_OPS].elem = symbol_table[tval].lexptr;
		generate_OPS[cnt_OPS].type = VAR;
		cnt_OPS++;
		cout << symbol_table[tval].lexptr << '\n';
		break;
	case INDEX:
		generate_OPS[cnt_OPS].elem = "<i>";
		generate_OPS[cnt_OPS].type = INDEXATOR;
		cnt_OPS++;
		cout << "<i>" << '\n';
		break;
	case MARK_JF:
		generate_OPS[cnt_OPS].elem = "<jf>";
		generate_OPS[cnt_OPS].type = JUMP_FALSE;
		cnt_OPS++;
		cout << "<jf>" << '\n';
		break;
	case MARK_J:
		generate_OPS[cnt_OPS].elem = "<j>";
		generate_OPS[cnt_OPS].type = JUMP;
		cnt_OPS++;
		cout << "<j>" << '\n';
		break;
	case READ:
		generate_OPS[cnt_OPS].elem = "<r>";
		generate_OPS[cnt_OPS].type = CREAD;
		cnt_OPS++;
		cout << "<r>" << '\n';
		break;
	case WRITE:
		generate_OPS[cnt_OPS].elem = "<w>";
		generate_OPS[cnt_OPS].type = CWRITE;
		cnt_OPS++;
		cout << "<w>" << '\n';
		break;
	default:
		cout << '\n';
	}
}

//������� � ��������� ������� 
void next_lexeme(int t)
{
	if (current_lexeme == t) current_lexeme = lexical_analyzer();
	else cout << "ERROR next_lexeme " << "line: " << lineno << "  symbol: " << ss << '\n'; 
}


void setSize()
{
	if (current_lexeme == NUM) massiv[lastentry].mas = new int[lexeme_val];
}

void terminal_a(int type) 
{
	switch (type) 
	{
		case NUM:
			print_ops(NUM, lexeme_val);
			next_lexeme(NUM);
			break;
		case ID:
			print_ops(ID, lexeme_val);
			next_lexeme(ID);
			break;
		case ARRAY:
			print_ops(ARRAY, lexeme_val);
			next_lexeme(ARRAY);
			next_lexeme('[');
			math_expression();
			next_lexeme(']');
			print_ops(INDEX, 0);
			break;
	}
}
//; ���������� J
void comparison()
{
	int t;
	switch (current_lexeme)
	{
	case '=':case '>':case'<':
		t = current_lexeme;
		next_lexeme(t);
		math_expression();
		print_ops(t, NONE);
		break;
	default:
		cout << "syntax ERROR J" << '\n' << "Error comparison";
	}
}
//; ���������� D
void conditional_expression()
{
	switch (current_lexeme)
	{
	case NUM:
	case ID:
	case ARRAY:
		terminal_a(current_lexeme);
		residual_term();
		term();
		comparison();
		break;
	case '(':
		next_lexeme('(');
		math_expression();
		next_lexeme(')');
		residual_term();
		term();
		comparison();
		break;
	default:
		cout << "syntax ERROR D" << '\n'  << "line = " << lineno << "  symbol = " << es;
	}
}
//; ���������� Y 
void value()
{
	switch (current_lexeme)
	{
	case NUM:
	case ID:
	case ARRAY:
		terminal_a(current_lexeme);
		break;
	case '(':
		next_lexeme('(');
		math_expression();
		next_lexeme(')');
		break;
	default:
		cout << "syntax ERROR Y" << '\n' << "line = " << lineno << "  symbol = " << es;
	}
}
//; ���������� L
void residual_term()
{
	int t;
	switch (current_lexeme)
	{
	case '*':case '/':
		t = current_lexeme;
		next_lexeme(current_lexeme);
		value();
		residual_term();
		print_ops(t, NONE);
		break;
	default:
		break;
	}
}
//; ���������� M
void multiplier()
{
	switch (current_lexeme)
	{
	case NUM:
	case ID:
	case ARRAY:
		terminal_a(current_lexeme);
		residual_term();
		break;
	case '(':
		next_lexeme('(');
		math_expression();
		next_lexeme(')');
		residual_term();
		break;
	default:
		cout << "syntax ERROR M" << '\n' << "line = " << lineno << "  symbol = " << es;
	}
}
//; ���������� U
void term()
{
	int t;
	switch (current_lexeme)
	{
	case '+': case '-':
		t = current_lexeme;
		next_lexeme(t);
		multiplier();
		term();
		print_ops(t, NONE);
		break;
	default:
		return;
	}
}
//; ���������� Q
void math_expression()
{
	switch (current_lexeme)
	{
	case NUM:
	case ID:
	case ARRAY:
		terminal_a(current_lexeme);
		residual_term();
		term();
		break;
	case '(':
		next_lexeme('(');
		math_expression();
		next_lexeme(')');
		residual_term();
		term();
		break;
	default:
		cout << "syntax ERROR Q" << '\n'  << "line = " << lineno << "  symbol = " << es;
		int w;
		cin >> w;
	}
}
//; ���������� S
void program_line()
{
	int pointJF, pointJ;
	switch (current_lexeme)
	{
	case ID:
		print_ops(ID, lexeme_val);
		next_lexeme(ID);
		next_lexeme('#');
		math_expression();
		print_ops('#', NONE);
		next_lexeme(';');
		program_line();
		break;
	case ARRAY:
		print_ops(ARRAY, lexeme_val);
		next_lexeme(ARRAY);
		next_lexeme('[');
		math_expression();
		next_lexeme(']');
		print_ops(INDEX, 0);
		next_lexeme('#');
		math_expression();
		print_ops('#', NONE);
		next_lexeme(';');
		program_line();
		break;
	case IF:
		next_lexeme(IF);
		next_lexeme('(');
		conditional_expression();
		next_lexeme(')');
		pointJF = cnt_OPS;									//����� ��� ������� ������ � ���
		cnt_OPS++;
		print_ops(MARK_JF, 0);
		program_line();
		switch (current_lexeme)
		{
		case ELSE:
			next_lexeme(ELSE);
			pointJ = cnt_OPS;								//����� ��� ������� ������ � ���
			cnt_OPS++;										//� ���������� �������� � ���
			print_ops(MARK_J, 0);									//������� <j> � ��� 
			generate_OPS[pointJF].elem = new char[x];
			itoa(cnt_OPS, generate_OPS[pointJF].elem, 10);			//����� �������� ��� <jf>
			generate_OPS[pointJ].type = generate_OPS[pointJF].type = JUMP_POINT;
			program_line();
			generate_OPS[pointJ].elem = new char[x];
			itoa(cnt_OPS, generate_OPS[pointJ].elem, 10);
			break;
		default:
			generate_OPS[pointJF].elem = new char[x];
			itoa(cnt_OPS, generate_OPS[pointJF].elem, 10);
			generate_OPS[pointJF].type = JUMP_POINT;
		}
		next_lexeme(';');
		program_line();
		break;
	case WHILE:
		next_lexeme(WHILE);
		next_lexeme('(');
		pointJ = cnt_OPS;									//����� �������� ��� <j>
		conditional_expression();													//�������
		next_lexeme(')');
		pointJF = cnt_OPS;									//����� ��� ������� ������ � ���
		cnt_OPS++;											//� ���������� �������� � ���
		next_lexeme(DO);
		print_ops(MARK_JF, 0);										//������� <jf> � ��� 
		program_line();
		generate_OPS[cnt_OPS].elem = new char[x];
		itoa(pointJ, generate_OPS[cnt_OPS].elem, 10);
		generate_OPS[cnt_OPS].type = generate_OPS[pointJF].type = JUMP_POINT;
		cnt_OPS++;
		print_ops(MARK_J, 0);										//������� <j> � ��� 
		generate_OPS[pointJF].elem = new char[x];
		itoa(cnt_OPS, generate_OPS[pointJF].elem, 10);
		next_lexeme(';');
		program_line();
		break;
	case '{':
		next_lexeme('{');
		program_line();
		next_lexeme('}');
		break;
	case READ:
		next_lexeme(READ);
		next_lexeme('(');
		switch (current_lexeme)
		{
		case ID:
			print_ops(ID, lexeme_val);
			next_lexeme(ID);
			break;
		case ARRAY:
			print_ops(ARRAY, lexeme_val);
			next_lexeme(ARRAY);
			next_lexeme('[');
			math_expression();
			next_lexeme(']');
			print_ops(INDEX, 0);
			break;
		default:
			cout << "error read(?) 6";
		}
		next_lexeme(')');
		print_ops(READ, 0);
		next_lexeme(';');
		program_line();
		break;
	case WRITE:
		next_lexeme(WRITE);
		next_lexeme('(');
		math_expression();
		next_lexeme(')');
		print_ops(WRITE, 0);
		next_lexeme(';');
		program_line();
		break;
	default:
		return;
	}
}
//; ���������� B
void name()
{
	switch (current_lexeme)
	{
	case ID:
		next_lexeme(ID);
		if (current_lexeme != ';') cout << "syntax ERROR. ������ � �������� ����������." << '\n'; 
		break;
	case ARRAY:
		next_lexeme(ARRAY);
		next_lexeme('[');
		setSize();
		next_lexeme(NUM);
		next_lexeme(']');
		if (current_lexeme != ';') cout << "syntax ERROR. ������ � �������� ����������." << '\n'; 
		break;
	default:
		cout << "syntax ERROR. ������ � �������� ����������." << '\n';
		return;
	}
}

//�������������� ����������; ���������� A
void syntax_analyzer()
{
	if (current_lexeme != DONE)
		switch (current_lexeme)
		{
		case INT:
			next_lexeme(INT);
			name();
			next_lexeme(';');
			syntax_analyzer();
			break;
		default:
			program_line();
		}
	return;
}

void OPS_Interpreter()
{
	int len = cnt_OPS;
	int z = 0, d = 0, res = 0, ps = 0;
	char t;
	stack st;
	ProcElem operand;
	ProcElem operand1;

	int *left_operand = 0;
	int right_operand = 0;

	while (z < len)
	{
		switch (generate_OPS[z].type)
		{
		case VAR:
			d = search_symbol_table(generate_OPS[z].elem);			//�� ����� ������� � ������� ���������� �������� ����������
			operand.value = d;						//�������
			operand.type = VAR;						//���
			st.push(operand);						//�������� � ����
			z++;									//��������� � c��������� ��������
			break;

		case NUMBER:
			operand.value = atoi(generate_OPS[z].elem);
			operand.type = NUMBER;
			st.push(operand);						//�������� � ����
			z++;									//��������� � c��������� ��������
			break;

		case MASSIVE:
			d = search_symbol_table(generate_OPS[z].elem);				//�� ����� ������� � ������� �������� �������� ������
			operand.value = d;						//�������
			operand.type = MASSIVE;						//���
			st.push(operand);						//�������� � ����
			z++;									//��������� � ��������� ��������
			break;

		case INDEXATOR:
			operand = st.pop();						//������ ��������
			operand1 = st.pop();					//������
			switch (operand.type)
			{
			case VAR:
				passport[ps].elem = number[operand.value].token;
				break;
			case NUMBER:
				passport[ps].elem = operand.value;
				break;
			default:
				break;
			};
			passport[ps].mas = operand1.value;
			operand.value = ps;
			ps++;
			operand.type = MASSIVE;
			st.push(operand);
			z++;
			break;

		case OPERATION:
			t = generate_OPS[z].elem[0];

			operand = st.pop();					//������ ��������
			operand1 = st.pop();				//����� ��������

			switch (operand.type) 
			{
			case VAR:
				right_operand = number[operand.value].token;
				break;
			case MASSIVE:
				right_operand = massiv[passport[operand.value].mas].mas[passport[operand.value].elem];
				break;
			case NUMBER:
				right_operand = operand.value;
				break;
			}
			switch (operand1.type)
			{
			case VAR:
				left_operand = &(number[operand1.value].token);
				break;
			case MASSIVE:
				left_operand = &(massiv[passport[operand1.value].mas].mas[passport[operand1.value].elem]);
				break;
			case NUMBER:
				left_operand = &operand1.value;
				break;
			default:
				break;
			}


			switch (t)
			{
			case '#':
				*left_operand = right_operand;
				break;
			case '+':
				res = *left_operand + right_operand;
				operand.value = res; operand.type = NUMBER;
				st.push(operand);
				break;
			case '-':
				res = *left_operand - right_operand;
				operand.value = res; operand.type = NUMBER;
				st.push(operand);
				break;
			case'*':
				res = *left_operand * right_operand;
				operand.value = res; operand.type = NUMBER;
				st.push(operand);
				break;
			case '/':
				res = *left_operand / right_operand;
				operand.value = res; operand.type = NUMBER;
				st.push(operand);
				break;
			case '>':
				res = 0; if (*left_operand > right_operand) res = 1;
				operand.value = res; operand.type = NUMBER;
				st.push(operand);
				break;
			case '<':
				res = 0; if (*left_operand < right_operand) res = 1;
				operand.value = res; operand.type = NUMBER;
				st.push(operand);
				break;
			case '=':
				res = 0; if (*left_operand == right_operand) res = 1;
				operand.value = res; operand.type = NUMBER;
				st.push(operand);
				break;
			default:
				z--; break;
			}
			z++;
			break;

		case JUMP_POINT:
			d = atoi(generate_OPS[z].elem); z++;
			if (generate_OPS[z].type == JUMP_FALSE)
			{
				operand = st.pop();
				if (operand.value == 1) z++;
				else z = d;
			};
			if (generate_OPS[z].type == JUMP) z = d;
			break;

		case CWRITE:
			operand = st.pop();
			switch (operand.type)
			{
			case VAR:
				z--;
				d = search_symbol_table(generate_OPS[z].elem);
				cout << number[d].token << ' ';
				z = z + 2;
				break;
			case NUMBER:
				cout << operand.value << ' '; z++;
				break;
			case MASSIVE:
				cout << massiv[passport[operand.value].mas].mas[passport[operand.value].elem] << ' ';
				z++;
				break;
			default:
				break;
			}
			break;
		case CREAD:
			operand = st.pop();
			switch (operand.type)
			{
			case VAR:
				z--;
				d = search_symbol_table(generate_OPS[z].elem);
				cin >> number[d].token;
				z = z + 2;
				break;
			case MASSIVE:
				cin >> massiv[passport[operand.value].mas].mas[passport[operand.value].elem];
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
	char * fileName = "program5.txt";			//��� ��������� �����, ���������������� ���������
	FILE *fp;								//����
	int fileSize;							//������ �����
	fp = fopen(fileName, "rt");				//�������� �����
	fseek(fp, 0, SEEK_END);					//����� ����� �����
	fileSize = ftell(fp);					//������ �����
	ProgText = new char[fileSize];			//�������� ������� ��� ������ ���������
	fseek(fp, 0, SEEK_SET);					//��������� ��������� �� ������ �����
	int i = 0;
	for(;!feof(fp); i++) ProgText[i] = getc(fp); //���� �� �������� ����� �����, ��������� ������
	i--;
	ProgText[i] = '&';						//�������� ������ - ������������
	fclose(fp);								//�������� �����

	//����������  ������� ��������� �������
	load_keywords();									
	//����������� ���������� - ������ �������
	current_lexeme = lexical_analyzer();
	//������������� ����������
	syntax_analyzer();
	
	//������������� �������� ������;
	generate_OPS[cnt_OPS].elem = new char[2];
	generate_OPS[cnt_OPS].elem = "&";
	generate_OPS[cnt_OPS].type = OPERATION;

	// ������� ��������������� ���
	cout << "Generate OPS: ";
	for (int f = 0; f < cnt_OPS + 1; f++) cout << generate_OPS[f].elem << "  ";
	
	//�������������� ���
	cout << "\n\n\nStart interpreter";
	OPS_Interpreter();
	cout << "End interpreter\n";
	system("PAUSE");
	return 0;
}