// translator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream f;
	string path = "text.txt";
	f.open(path);
	string textToBeTranslated;
	cout << textToBeTranslated;
	if (!f.is_open())
	{
		cout << "Vive la France!" << endl;
	}
	else
	{
		char ch;
		while (f.get(ch))
		{
			textToBeTranslated.push_back(ch);
		}
	}

	Lexer lexer(textToBeTranslated);
	Parser* parser = new Parser(lexer);
	auto ops = parser->make_ops();
	Interpreter* ipt = new Interpreter();

	cout << endl;

	for (int i = 0; i < ops.tokens.size(); i++)
	{
		ops.tokens[i].get_info();
	}
	cout << endl;

	for (int i = 0; i < ops.varArr.size(); i++)
	{
		cout << ops.varArr[i] << " ";
	}
	cout << endl;
	ipt->get_commands(ops);

	return 0;
}